#ifndef MESH_H
#define	MESH_H

#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <map>

#include "../util/Math3D.h"
#include "../util/HName.h"
#define MESH_FOLDER "res/mesh/"

namespace NNY{
    namespace Render{

        class Mesh {
            public:

            Mesh();

            Mesh( std::vector<Vector3f> vertex
                , std::vector<Vector3f> tangent
                , std::vector<Vector3f> normals
                , std::vector<Vector2f> texcoords
                , std::vector<unsigned int> index
                , unsigned int material_id);

            virtual ~Mesh();

            void load();
            void unload();

                std::vector<Vector3f> vertex;
                std::vector<Vector3f> tangent;
                std::vector<Vector3f> normals;
                std::vector<Vector2f> texcoords;
                std::vector<unsigned int> index;
                unsigned int material_id;

                GLuint ibo;
                GLuint nbo;
                GLuint vbo;
                GLuint tbo;
                GLuint tabo;
                GLuint vao;
                unsigned int indexsize;

                bool loaded;
        };
    }
}



#endif	/* MESH_H */
