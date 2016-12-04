#include "Scene.h"
#include "../util/Log.h"
#include "../util/Math3D.h"

#include <cassert>
#include <algorithm>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/texture.h>
#include <assimp/postprocess.h>
#include <SOIL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

namespace NNY{
namespace Render{

void Scene::load_from_file(std::string path){
    Assimp::Importer importer;

    const aiScene * scene = importer.ReadFile(path.c_str()
            , aiProcess_Triangulate
            | aiProcess_GenSmoothNormals
            | aiProcess_FlipUVs
            | aiProcess_OptimizeMeshes
            | aiProcess_OptimizeGraph
            | aiProcess_CalcTangentSpace);

    if(scene == nullptr){
        M_LOG("[Error] Could not load scene!");
        assert(false);
    }

    this->dir = path.substr(0, path.find_last_of('/'));
    this->dir.push_back('/');

    M_LOG("[info] Processing meshes");

    this->meshes.reserve(scene->mNumMeshes);

    for (unsigned i = 0;i < scene->mNumMeshes;i+=1){
        const aiMesh * mesh = scene->mMeshes[i];

        assert(mesh->HasTangentsAndBitangents());

        std::vector<Vector3f> vertex;
        vertex.reserve(mesh->mNumVertices);
        std::vector<Vector3f> tangent;
        tangent.reserve(mesh->mNumVertices);
        std::vector<Vector3f> normals;
        normals.reserve(mesh->mNumVertices);
        std::vector<Vector2f> texcoords;
        texcoords.reserve(mesh->mNumVertices);
        std::vector<unsigned int> indices;
        indices.reserve(mesh->mNumFaces * 3);

        for(unsigned j = 0;j < mesh->mNumVertices;j+=1){
            const aiVector3D pos = mesh->mVertices[j];
            const aiVector3D norm = mesh->mNormals[j];
            const aiVector3D texCoord = mesh->HasTextureCoords(0) ?  mesh->mTextureCoords[0][j] : aiVector3D(0.0,0.0,0.0);
            const aiVector3D tang = mesh->mTangents[j];

            vertex.push_back(Vector3f(pos.x,pos.y,pos.z));
            normals.push_back(Vector3f(norm.x,norm.y,norm.z));
            tangent.push_back(Vector3f(tang.x,tang.y,tang.z));
            texcoords.push_back(Vector2f(texCoord.x,texCoord.y));
        }

        for (unsigned j = 0;j < mesh->mNumFaces; j+=1){
            const aiFace & face = mesh->mFaces[j];
            assert(face.mNumIndices == 3);
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }


        this->meshes.emplace_back(Mesh(vertex,tangent,normals,texcoords,indices,mesh->mMaterialIndex));
    }

    M_LOG("[info] Processing meshes finished.");
    M_LOG_VALUES("[info] found ", this->meshes.size(), "Meshes!")

    M_LOG("[info] Processing materials.");

    for(unsigned i = 0;i < scene->mNumMaterials;i+=1){
        const aiMaterial * mat = scene->mMaterials[i];

        Material res;

        float shininess;
        if(AI_SUCCESS == mat->Get<float>(AI_MATKEY_SHININESS,shininess)){
            //res.roughness = sqrt(2.0/(shininess + 2));
            res.roughness = 0.1;
        }else{
            res.roughness = 0.1;
        }

        Vector3f color;
        if(AI_SUCCESS == mat->Get<Vector3f>(AI_MATKEY_COLOR_DIFFUSE,color)){
            res.color = color;
        }else{
            res.color = Vector3f(0.5,0.5,0.0);
        }

        res.albedo_texture_index = this->load_textures(res,*mat,aiTextureType_DIFFUSE);
        res.normal_texture_index = this->load_textures(res,*mat,aiTextureType_HEIGHT);
        res.roughness_texture_index = this->load_textures(res,*mat,aiTextureType_SHININESS);
        this->materials.push_back(res);
    }
    M_LOG("[info] Processing materials finished.");
    M_LOG_VALUES("[info] finished loading scene, found ", this->materials.size(), "Materials!")

}

unsigned int Scene::load_textures(Material & res,const aiMaterial & mat, aiTextureType type){
    if(0 != mat.GetTextureCount(type)){
        M_LOG("[debug] texture");
        aiString str;
        if(AI_SUCCESS == mat.GetTexture(type, 0, &str))
            return this->load_texture_from_file(std::string(str.C_Str()));
    }
    M_LOG("[debug] found material without texture");
    return NO_TEXTURE;
}

unsigned int Scene::load_texture_from_file(std::string path){
    // check if texture already exists.
    
    std::replace(path.begin(),path.end(),'\\','/');

    path = this->dir + path;

    auto f = this->text_path_index.find(path);
    if(f != this->text_path_index.end()){
        return f->second;
    }

    M_LOG_VALUES("[info] loading texture at: ",path);

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    int width,height,components;
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &components, SOIL_LOAD_RGB);
    if(image == nullptr){
        M_LOG("[warning] failed to load image");
        return NO_TEXTURE;
    }
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);	

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);

    unsigned int res = this->textures.size();
    this->textures.push_back(Texture{ texture_id });
    this->text_path_index.insert(std::pair<std::string,unsigned int>(path,res));
    return res;
}

void Scene::load(){
    for(Mesh & mesh : this->meshes){
        mesh.load();
    }
}

void Scene::unload(){
    for(Mesh & mesh : this->meshes){
        mesh.unload();
    }
}

}}
