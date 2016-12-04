#include "Mesh.h"
#include <fstream> 
#include <vector>
#include <map>

#include "../util/Math3D.h" 
#include "../util/Log.h"

namespace NNY{
    namespace Render{

        Mesh::Mesh(){
            this->vbo = 0;
            this->nbo = 0;
            this->tabo = 0;
            this->ibo = 0;
            this->tbo = 0;
            this->vao = 0;
        }

        Mesh::Mesh( std::vector<Vector3f> vertex
                , std::vector<Vector3f> tangent
                , std::vector<Vector3f> normals
                , std::vector<Vector2f> texcoords
                , std::vector<unsigned int> index
                , unsigned int material_id){

            this->vertex = vertex;
            this->tangent = tangent;
            this->normals = normals;
            this->texcoords = texcoords;
            this->index = index;
            this->material_id = material_id;

            this->vbo = 0;
            this->nbo = 0;
            this->tabo = 0;
            this->ibo = 0;
            this->tbo = 0;
            this->vao = 0;
        }

        Mesh::~Mesh(){
            this->unload();
        }

        void Mesh::load(){
            //TODO i can probebly generate all buffers at the same time
            glGenBuffers(1,&this->vbo);
            glBindBuffer(GL_ARRAY_BUFFER,this->vbo);
            glBufferData(GL_ARRAY_BUFFER,this->vertex.size() * sizeof(Vector3f),&this->vertex[0],GL_STATIC_DRAW);

            glGenBuffers(1,&this->nbo);
            glBindBuffer(GL_ARRAY_BUFFER,this->nbo);
            glBufferData(GL_ARRAY_BUFFER,this->normals.size() * sizeof(Vector3f),&this->normals[0],GL_STATIC_DRAW);

            glGenBuffers(1,&this->tabo);
            glBindBuffer(GL_ARRAY_BUFFER,this->tabo);
            glBufferData(GL_ARRAY_BUFFER,this->tangent.size() * sizeof(Vector3f),&this->tangent[0],GL_STATIC_DRAW);

            glGenBuffers(1,&this->tbo);
            glBindBuffer(GL_ARRAY_BUFFER,this->tbo);
            glBufferData(GL_ARRAY_BUFFER,this->texcoords.size() * sizeof(Vector2f),&this->texcoords[0],GL_STATIC_DRAW);

            glGenBuffers(1,&this->ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->ibo);
            //This is a memorial
            //to the time wasted on
            //finding the small v which needed
            //to be changed to a i
            //May he forever be hated
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,this->index.size() * sizeof(unsigned int),&this->index[0],GL_STATIC_DRAW);


            glGenVertexArrays(1, &this->vao);
            glBindVertexArray(this->vao);

            glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
            glEnableVertexAttribArray(0); // vertex on location 0
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER, this->nbo);
            glEnableVertexAttribArray(1); // normals on loaction 1
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER, this->tbo);
            glEnableVertexAttribArray(2); // texture coords on loaction 1
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER, this->tabo);
            glEnableVertexAttribArray(3); // texture coords on loaction 1
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);


            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);

            glBindVertexArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            this->indexsize = this->index.size();
        }

        void Mesh::unload(){
            if(this->vbo){
                glDeleteBuffers(1,&this->vbo);
                this->vbo = 0;
            }
            if(this->nbo){
                glDeleteBuffers(1,&this->nbo);
                this->nbo = 0;
            }
            if(this->tbo){
                glDeleteBuffers(1,&this->tbo);
                this->tbo = 0;
            }
            if(this->ibo){
                glDeleteBuffers(1,&this->ibo);
                this->ibo = 0;
            }
            if(this->vao){
                glDeleteVertexArrays(1,&this->vao);
                this->vao = 0;
            }
        }
    }
}
