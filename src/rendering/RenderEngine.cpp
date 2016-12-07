#include "RenderEngine.h"

#include <GL/glew.h>

#include "../Engine.h"
#include "../util/Log.h" 
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "RenderQueue.h" 
#include "../util/Log.h" 
#include "../util/Profile.h"

namespace NNY{
    namespace Render{ RenderEngine::RenderEngine(unsigned width, unsigned height){ //request opengl version 3.2

            //create window and context
            glewExperimental = true;
            //init glew
            GLenum glewerr = glewInit(); 
            if(glewerr != GLEW_OK){
                M_LOGLVL("[error] glew init failed",Log::Level::RENDERING)
                    if(glewerr == GLEW_ERROR_NO_GL_VERSION){ 
                        M_LOGLVL("    No OGL version found",Log::Level::RENDERING) 
                    }else { 
                        M_LOGLVL("    OGL version not supported",Log::Level::RENDERING)
                    }
                glew_inited = false;
            }else{
                glew_inited = true;
            }

            //check the actual version of ogl
            GLint oglVersionMajor,oglVersionMinor;

            glGetIntegerv(GL_MAJOR_VERSION,&oglVersionMajor);
            glGetIntegerv(GL_MINOR_VERSION,&oglVersionMinor);

            M_LOGLVL_VALUES(Log::Level::RENDERING,"[Message] Ogl version found",oglVersionMajor,",",oglVersionMinor)
                if( oglVersionMajor < OGL_VERSION_MAJOR_REQUIRED){
                    M_LOGLVL("    OGL version not supported",Log::Level::RENDERING)
                        ogl_version_supported = false;
                }else if(oglVersionMajor == OGL_VERSION_MAJOR_REQUIRED){
                    if( oglVersionMinor < OGL_VERSION_MINOR_REQUIRED){
                        M_LOGLVL("    OGL version not supported",Log::Level::RENDERING)
                            ogl_version_supported = false;
                    }else{
                        ogl_version_supported = true;
                    }
                }else{
                    ogl_version_supported = true;
                    M_LOGLVL("    OGL version supported",Log::Level::RENDERING)
                }

            //set the clear color
            glClearColor(0.0f,0.0f,0.0f,1.0f);

            //enable back face culling    
            glFrontFace(GL_CCW);
            glCullFace(GL_BACK);
            glEnable(GL_CULL_FACE);

            //set depth testing
            glDepthRange(0,1);
            glEnable(GL_DEPTH_TEST);

            //clamp depth values 
            //glEnable(GL_DEPTH_CLAMP);

            //load default values for rescources
            this->geometry_shader = new Shader(); 
            this->geometry_shader->load_shader("res/shader/geomv.glsl","res/shader/geom.glsl");
            this->post_shader = new Shader();
            this->post_shader->load_shader("res/shader/postv.glsl","res/shader/post.glsl");
            this->pos_shader = new Shader();
            this->pos_shader->load_shader("res/shader/postv.glsl","res/shader/pos.glsl");
            this->point_shader = new Shader();
            this->point_shader->load_shader("res/shader/p_lightv.glsl","res/shader/p_light.glsl");
            this->dir_shader = new Shader();
            this->dir_shader->load_shader("res/shader/d_lightv.glsl","res/shader/d_light.glsl");
            this->post = new PostProcess();
            this->g_buffer = new GBuffer(width,height);
            this->exposure = 1.0;
            this->which = RenderOut::FULL;
            this->shadow_map = new ShadowMap();
            this->width = width;
            this->height = height;
        }

        RenderEngine::~RenderEngine(){
            delete(this->geometry_shader);
        }

        void RenderEngine::render(Scene * scene) {
            Vector3f view_position = Vector3f(this->camera.position);
            this->g_buffer->bind();
                this->geometry_shader->bind();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                Matrix4f camMatrix = Matrix4f(this->camera.getViewProjection());
                Matrix4f projection = Matrix4f(this->camera.getProjection());
                Matrix4f viewMatrix = Matrix4f(this->camera.getView());


                this->geometry_shader->get_uniform("projection")->set_matrix4f(projection);
                this->geometry_shader->get_uniform("view")->set_matrix4f(viewMatrix);
                this->geometry_shader->get_uniform("model")->set_matrix4f(Matrix4f().toIdentity());
                this->geometry_shader->get_uniform("view_position")->set_vector3f(view_position);

                Uniform * roughness = this->geometry_shader->get_uniform("roughness");
                Uniform * metalness = this->geometry_shader->get_uniform("metalness");
                Uniform * diffuse = this->geometry_shader->get_uniform("diffuse");
                Uniform * albedo_texture = this->geometry_shader->get_uniform("albedo_texture");
                Uniform * roughness_texture = this->geometry_shader->get_uniform("roughness_texture");
                Uniform * normal_texture = this->geometry_shader->get_uniform("normal_texture");
                Uniform * has_normal_texture = this->geometry_shader->get_uniform("has_normal_texture");

                // make sure the last material is not the material of the first mesh
                unsigned int last_material = scene->meshes[0].material_id + 1;
                for(Mesh & m : scene->meshes){
                    if(m.material_id != last_material){
                        last_material = m.material_id;
                        Material & mat = scene->materials[m.material_id];
                        roughness->set_float(mat.roughness);
                        metalness->set_float(mat.metalness);

                        // set texture 
                        if(mat.albedo_texture_index != NO_TEXTURE){
                            albedo_texture->set_texture(scene->textures[mat.albedo_texture_index],0);
                        }else{
                            glActiveTexture(GL_TEXTURE0);
                            glBindTexture(GL_TEXTURE_2D, 0);
                        }

                        if(mat.roughness_texture_index != NO_TEXTURE){
                            roughness_texture->set_texture(scene->textures[mat.roughness_texture_index],1);
                        }else{
                            glActiveTexture(GL_TEXTURE1);
                            glBindTexture(GL_TEXTURE_2D, 0);
                        }

                        if(mat.normal_texture_index != NO_TEXTURE){
                            has_normal_texture->set_bool(true);
                            normal_texture->set_texture(scene->textures[mat.normal_texture_index],2);
                        }else{
                            has_normal_texture->set_bool(false);
                            glActiveTexture(GL_TEXTURE2);
                            glBindTexture(GL_TEXTURE_2D, 0);
                        }
                    }

                    glBindVertexArray(m.vao);
                    glDrawElements(GL_TRIANGLES,m.indexsize,GL_UNSIGNED_INT,0);
                }
                glBindVertexArray(0);
                Shader::unbind();
            FrameBuffer::unbind();

            /*
            this->shadow_map->bind(this->camera,scene->d_light);

                for(Mesh & m : scene->meshes){
                    glBindVertexArray(m.vao);
                    glDrawElements(GL_TRIANGLES,m.indexsize,GL_UNSIGNED_INT,0);
                }
                glBindVertexArray(0);

            ShadowMap::unbind(this->width,this->height);
            */
                

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            if(this->which == RenderOut::FULL){

                glEnable(GL_BLEND);
                glDisable(GL_DEPTH_TEST);
                glBlendFunc(GL_ONE, GL_ONE);
                auto position = this->g_buffer->get_position_texture();
                auto normal = this->g_buffer->get_normal_texture();
                auto albedo = this->g_buffer->get_albedo_texture();

                this->dir_shader->bind();
                this->dir_shader->get_uniform("in_position")->set_texture(position,0);
                this->dir_shader->get_uniform("in_normal")->set_texture(normal,1);
                this->dir_shader->get_uniform("in_albedo")->set_texture(albedo,2);
                this->dir_shader->get_uniform("exposure")->set_float(this->exposure);
                this->dir_shader->get_uniform("view_pos")->set_vector3f(view_position);
                this->dir_shader->get_uniform("light_direction")->set_vector3f(scene->d_light.direction);
                this->dir_shader->get_uniform("light_intensity")->set_float(scene->d_light.intensity);
                this->dir_shader->get_uniform("light_color")->set_vector3f(scene->d_light.color);
                this->post->draw();

                this->point_shader->bind();
                this->point_shader->get_uniform("in_position")->set_texture(position,0);
                this->point_shader->get_uniform("in_normal")->set_texture(normal,1);
                this->point_shader->get_uniform("in_albedo")->set_texture(albedo,2);
                this->point_shader->get_uniform("exposure")->set_float(this->exposure);
                this->point_shader->get_uniform("view_pos")->set_vector3f(view_position);
                    
                Uniform * l_position = this->point_shader->get_uniform("light_position");
                Uniform * l_intensity = this->point_shader->get_uniform("light_intensity");
                Uniform * l_color = this->point_shader->get_uniform("light_color");

                this->point_shader->bind();
                for (PointLight & l : scene->p_lights){
                    l_position->set_vector3f(l.position);
                    l_intensity->set_float(1/l.intensity);
                    l_color->set_vector3f(l.color);
                    this->post->draw();
                }
                glDisable(GL_BLEND);
                glEnable(GL_DEPTH_TEST);


            }else if(this->which == RenderOut::NORMALS){
                this->post_shader->bind();
                auto input = this->g_buffer->get_normal_texture();
                this->post_shader->get_uniform("input")->set_texture(input,0);
                this->post->draw();
            }else if(this->which == RenderOut::POSITIONS){
                this->pos_shader->bind();
                auto input = this->g_buffer->get_position_texture();
                this->pos_shader->get_uniform("input")->set_texture(input,0);
                this->post->draw();
            }else if(this->which == RenderOut::ALBEDO){
                this->post_shader->bind();
                auto input = this->g_buffer->get_albedo_texture();
                this->post_shader->get_uniform("input")->set_texture(input,0);
                this->post->draw();
            }
            Shader::unbind();
        }

        bool RenderEngine::ready() const {
            return glew_inited && ogl_version_supported;
        }

    }
}
