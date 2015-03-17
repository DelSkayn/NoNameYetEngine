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

        struct Mesh {
            GLuint ibo;
            GLuint nbo;
            GLuint vbo;
            GLuint tbo;
            GLuint vao;
            unsigned int index_size;
        };



        struct MeshRescource {
            std::vector<Vector3f/*,MemAllocator<Vector3f>*/> vertex;
            std::vector<Vector3f/*,MemAllocator<Vector3f>*/> normals;
            std::vector<Vector2f/*,MemAllocator<Vector2f>*/> texcoords;
            std::vector<unsigned int/*,MemAllocator<unsigned int>*/> index;
            std::vector<int/*,MemAllocator<int>*/> material_ids;

            unsigned int indexsize;

            //TODO add Textures
        };

        struct Shape{
            MeshRescource mr;
            Mesh m;
            bool loaded;
        };

        class AbstractMeshFormatLoader{ public:
            /*
             * Abstract function 
             * args:
             * mr: the mesh rescource to load the mesh in
             * in: an open filestream to the file containig the mesh
             */
            virtual void loadMesh(MeshRescource & mr, std::ifstream & in) = 0;
        };

        class ObjMeshFormatLoader : public AbstractMeshFormatLoader{
            public:
                /*
                 * Loads Obj Format
                 * args:
                 * mr: the mesh rescource to load the mesh in
                 * in: an open filestream to the file containig the mesh
                 */
                virtual void loadMesh(MeshRescource & mr, std::ifstream & in) override;
        };

        class MeshManager {
            public:
                static void init();

                /*
                 * Loads Mesh into memory
                 * TODO this is not spelled correctly
                 * Determins format from file extension
                 * args:
                 * filename: name of the file in the mesh folder 
                 * MeshName: the name of the mesh in the rescource map
                 */
                static void loadMeshRescource(std::string fileName, std::string MeshName);

                /*
                 * Loads Mesh into memory and graphics memory
                 * Determins format from file extension
                 * args:
                 * filename: name of the file in the mesh folder 
                 * MeshName: the name of the mesh in the rescource map
                 */
                static void loadMesh(std::string fileName, std::string MeshName);

                /*
                 * Loads Mesh into memory and graphics memory using provided loader
                 * args:
                 * filename: name of the file in the mesh folder 
                 * MeshName: the name of the mesh in the rescource map
                 */
                static void loadMeshRescource(std::string filename, std::string MeshName, AbstractMeshFormatLoader & loader);

                /*
                 * Loads Rescource into graphics memory
                 * args:
                 * MeshName: the name of the mesh to be loaded
                 */
                static void loadMesh(std::string MeshName);

                /*
                 * Unloads Rescource from graphics memory
                 * args:
                 * MeshName: the name of the mesh to be loaded
                 */
                static void unloadMesh(std::string MeshName);

                static Mesh * getMesh(std::string name);

                static void clean();
            private:
                static Shape default_shape;
                static void unloadMesh(Mesh & m);
                static void loadMesh(Mesh & m,MeshRescource mr);

                static std::map<HName, Shape> mesh_map;
        };
    }
}



#endif	/* MESH_H */
