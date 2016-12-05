#include "PostProcess.h"

namespace NNY{
    namespace Render{

        PostProcess::PostProcess(){
            GLfloat quadVertices[] = {
                // Positions        // Texture Coords
                -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            };
            // Setup plane VAO
            glGenVertexArrays(1, &this->vao);
            glGenBuffers(1, &this->vbo);
            glBindVertexArray(this->vao);
            glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        }

        PostProcess::~PostProcess(){
            glDeleteBuffers(1,&this->vbo);
            glDeleteVertexArrays(1,&this->vao);
        }

        void PostProcess::draw(){
            glBindVertexArray(this->vao);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glBindVertexArray(0);
        }
    }}
