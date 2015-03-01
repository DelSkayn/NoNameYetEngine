#include "Mesh.h"
#include <fstream> 
#include <vector>
#include <map>

#include "../util/Math3D.h" 
#include "../util/Log.h"

namespace NNY{
    namespace Render{

        std::map<HName,Shape> MeshManager::mesh_map;
        Shape MeshManager::default_shape;

        void MeshManager::init(){
            /*
               default_shape.mr.vertex = {
               Vector3f(0,0,0),
               Vector3f(0,0,1),
               Vector3f(0,1,0),
               Vector3f(0,1,1),
               Vector3f(1,0,0),
               Vector3f(1,0,1),
               Vector3f(1,1,0),
               Vector3f(1,1,1)
               };

               default_shape.mr.normals = {
            //TODO add normals
            };

            default_shape.mr.index = {
            1,7,5,
            1,3,7,
            1,4,3,
            1,2,4,
            3,8,7,
            3,4,8,
            5,7,8,
            5,8,6,
            1,5,6,
            1,6,2,
            2,6,8,
            2,8,4
            };
            */

            default_shape.mr.vertex = {
                Vector3f(0.7,0,0),
                Vector3f(0.7,0.7,0),
                Vector3f(0,0.7,0)
            };

            default_shape.mr.normals = {
                //TODO add normals
            };

            default_shape.mr.index = {
                0,1,2
            };

            default_shape.mr.indexsize = 3;

            loadMesh(default_shape.m,default_shape.mr);
        }

        void MeshManager::loadMeshRescource(std::string filename, std::string meshname){

            //open stream
            std::ifstream in;
            in.open((MESH_FOLDER + filename).c_str(), std::fstream::in);

            //test if file could be opened
            if(!in.is_open()){
                M_LOGLVL("[Warning] Mesh file could not be opened: " MESH_FOLDER + filename,Log::Level::RENDERING) 
                    return;
            }

            //get everting after the first "." including the "."
            std::string extension = filename.substr(filename.find('.'));
            //trim "."
            extension.erase(0,1);

            Shape s;
            //load the actual meshrescource
            if(extension == "obj"){
                ObjMeshFormatLoader loader;
                loader.loadMesh(s.mr,in);
            }else{
                M_LOGLVL("[Warning] Could not find mesh extension. Mesh not loaded",Log::Level::RENDERING)
            }

            s.loaded = false;;

            M_LOGLVL("[message] Loaded Mesh into memory: " + filename,Log::Level::RENDERING);

            mesh_map.insert(std::pair<HName,Shape>(meshname,s));


        }

        void MeshManager::loadMesh(std::string filename, std::string meshname){
            //open stream
            std::ifstream in;
            in.open((MESH_FOLDER + filename).c_str(), std::fstream::in);

            //test if file could be opened
            if(!in.is_open()){
                M_LOGLVL("[Warning] Mesh file could not be opened: " MESH_FOLDER + filename,Log::Level::RENDERING) 
                    return;
            }

            //get everting after the first "." including the "."
            std::string extension = filename.substr(filename.find('.'));
            //trim "."
            extension.erase(0,1);

            Shape s;
            //load the actual meshrescource
            if(extension == "obj"){
                ObjMeshFormatLoader loader;
                loader.loadMesh(s.mr,in);
            }else{
                M_LOGLVL("[Warning] Could not find mesh extension. Mesh not loaded",Log::Level::RENDERING)
            }

            s.loaded = true;

            loadMesh(s.m,s.mr);

            M_LOGLVL("[message] Loaded Mesh into memory: " + filename,Log::Level::RENDERING);


            mesh_map.insert(std::pair<HName,Shape>(meshname,s));

        }

        void ObjMeshFormatLoader::loadMesh(MeshRescource & mr,std::ifstream & in){
            std::string line;
            std::getline(in,line);

            bool normalIndexSeperate = false;
            bool textureIndexSeperate = false;
            bool indexTestDone = false;

            std::vector<unsigned int> normalIndecies;
            std::vector<unsigned int> textureIndecies;

            std::vector<std::string> weirdIderntifiers;

            //clean mr
            mr.indexsize = 0;
            mr.index.clear();
            mr.texcoords.clear();
            mr.material_ids.clear();
            mr.normals.clear();

            if(line.empty()){
                M_LOGLVL("[Warning] Obj file empty",Log::Level::RENDERING)
                    return;
            }

            while(!in.eof()){
                std::vector<std::string> words = Misc::splitString(line, ' ');
                if(words[0] == "#"){
                    //comment do nothing
                }else if(words[0] == "v"){
                    //position, add to vertex
                    mr.vertex.push_back(Vector3f(Misc::float_value_of(words[1])
                                ,Misc::float_value_of(words[2])
                                ,Misc::float_value_of(words[3])));

                }else if(words[0] == "vn"){
                    //normal, add to normal
                    mr.normals.push_back(Vector3f(Misc::float_value_of(words[1])
                                ,Misc::float_value_of(words[2])
                                ,Misc::float_value_of(words[3])));

                }else if(words[0] == "f"){
                    //index
                    //first find out wether the indecies are seperated
                    if(!indexTestDone){
                        indexTestDone = true;
                        std::vector<std::string> split = Misc::splitString(words[1],'/');
                        if(words[0] != split[0]){
                            //spliting has happend, indecies are separate
                            //format = #1/#2/#3
                            //where #1,#2,#3 are indecies
                            //lets find out which indecies are written
                            // #//# is possible and so is #/#/ (i think)
                            if(split.size() < 3){
                                if(words[1].at(words[1].find('/'))== '/'){
                                    //if after the first "/" the next char is also "/" the texture indecies are not separate
                                    //or do not exist, also a possiblity
                                    normalIndexSeperate = true;
                                }else{
                                    textureIndexSeperate = true;
                                }
                            }else{
                                //index split into 3 words thus all indecies are separete
                                textureIndexSeperate = true;
                                normalIndexSeperate = true;
                            }
                        }
                    }
                    //okay test done
                    if(!(textureIndexSeperate || normalIndexSeperate)){
                        //if texture nor normal then just take the output
                        //and subtract 1
                        //obj indecies are base 1 not base 0
                        mr.index.push_back(Misc::uint_value_of(words[1])-1);
                        mr.index.push_back(Misc::uint_value_of(words[2])-1);
                        mr.index.push_back(Misc::uint_value_of(words[3])-1);

                        mr.indexsize += 3;
                    }else if(textureIndexSeperate){
                        //only the vertex indecies are separate 
                        std::vector<std::string> split = Misc::splitString(words[1],'/');
                        mr.index.push_back(Misc::uint_value_of(split[0])-1);
                        textureIndecies.push_back(Misc::uint_value_of(split[1])-1);

                        split = Misc::splitString(words[2],'/');
                        mr.index.push_back(Misc::uint_value_of(split[0])-1);
                        textureIndecies.push_back(Misc::uint_value_of(split[1])-1);

                        split = Misc::splitString(words[3],'/');
                        mr.index.push_back(Misc::uint_value_of(split[0])-1);
                        textureIndecies.push_back(Misc::uint_value_of(split[1])-1);

                        //not forget to update the indexsize
                        mr.indexsize += 3;
                    }else if(normalIndexSeperate){
                        //only the normals are separate
                        std::vector<std::string> split = Misc::splitString(words[1],'/');
                        mr.index.push_back(Misc::uint_value_of(split[0])-1);
                        normalIndecies.push_back(Misc::uint_value_of(split[1])-1);

                        split = Misc::splitString(words[2],'/');
                        mr.index.push_back(Misc::uint_value_of(split[0])-1);
                        normalIndecies.push_back(Misc::uint_value_of(split[1])-1);

                        split = Misc::splitString(words[3],'/');
                        mr.index.push_back(Misc::uint_value_of(split[0])-1);
                        normalIndecies.push_back(Misc::uint_value_of(split[1])-1);

                        mr.indexsize += 3;
                    }else{
                        //all are seperate
                        std::vector<std::string> split = Misc::splitString(words[1],'/');
                        mr.index.push_back(Misc::uint_value_of(split[0])-1);
                        normalIndecies.push_back(Misc::uint_value_of(split[1])-1);
                        textureIndecies.push_back(Misc::uint_value_of(split[2])-1);

                        split = Misc::splitString(words[2],'/');
                        mr.index.push_back(Misc::uint_value_of(split[0])-1);
                        normalIndecies.push_back(Misc::uint_value_of(split[1])-1);
                        textureIndecies.push_back(Misc::uint_value_of(split[2])-1);

                        split = Misc::splitString(words[3],'/');
                        mr.index.push_back(Misc::uint_value_of(split[0])-1);
                        normalIndecies.push_back(Misc::uint_value_of(split[1])-1);
                        textureIndecies.push_back(Misc::uint_value_of(split[2])-1);

                        mr.indexsize += 3;
                    }
                    //And that is the indecies done
                }else{
                    bool found = false;
                    for(unsigned int i = 0;i < weirdIderntifiers.size();i++){
                        if(weirdIderntifiers[i] == words[0]){
                            found = true;
                            break;
                        }
                    }
                    if(!found){
                        M_LOGLVL("[Warning] found not supported identifier: " + words[0],Log::Level::RENDERING)
                            weirdIderntifiers.push_back(words[0]);
                    }
                }
                std::getline(in,line);
            }

            //Soo all the data is loaded.
            //Now to put it in the right place.
            if(textureIndexSeperate){
                std::vector<Vector2f/*,MemAllocator<Vector2f>*/> tempCoords = mr.texcoords;
                mr.texcoords.reserve(mr.indexsize);
                for(unsigned int i = 0;i < mr.indexsize;i++){
                    mr.texcoords[mr.index[i]] = tempCoords[textureIndecies[i]];
                }
            }
            if(normalIndexSeperate){
                std::vector<Vector3f/*,MemAllocator<Vector3f>*/> tempNormals = mr.normals;
                mr.normals.reserve(mr.indexsize);
                for(unsigned int i = 0;i < mr.indexsize;i++){
                    mr.normals[mr.index[i]] = tempNormals[normalIndecies[i]];
                }
            }
            //and done!
        }

        void MeshManager::unloadMesh(std::string meshName){
            auto it = mesh_map.find(meshName);
            if(it == mesh_map.end()){
                M_LOGLVL("[warning] deletion of mesh requested which was not loaded" + meshName,Log::Level::RENDERING);
                return;
            }
            if(!it->second.loaded){
                M_LOGLVL("[warning] deletion of mesh requested which was not loaded" + meshName,Log::Level::RENDERING);
                return;
            }
            unloadMesh(it->second.m);
            it->second.loaded = false;
        }

        void MeshManager::loadMesh(Mesh & m,MeshRescource mr){

            //TODO i can probebly generate all buffers at the same time
            glGenBuffers(1,&m.vbo);
            glBindBuffer(GL_ARRAY_BUFFER,m.vbo);
            glBufferData(GL_ARRAY_BUFFER,mr.vertex.size() * sizeof(Vector3f),&mr.vertex[0],GL_STATIC_DRAW);

            glGenBuffers(1,&m.nbo);
            glBindBuffer(GL_ARRAY_BUFFER,m.nbo);
            glBufferData(GL_ARRAY_BUFFER,mr.normals.size() * sizeof(Vector3f),&mr.normals[0],GL_STATIC_DRAW);

            glGenBuffers(1,&m.tbo);
            glBindBuffer(GL_ARRAY_BUFFER,m.tbo);
            glBufferData(GL_ARRAY_BUFFER,mr.texcoords.size() * sizeof(Vector2f),&mr.texcoords[0],GL_STATIC_DRAW);

            glGenBuffers(1,&m.ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m.ibo);
            //This is a memorial
            //to the time wasted on
            //finding the small v which needed
            //to be changed to a i
            //May he forever be hated
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,mr.index.size() * sizeof(unsigned int),&mr.index[0],GL_STATIC_DRAW);


            glGenVertexArrays(1, &m.vao);
            glBindVertexArray(m.vao);

            glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
            glEnableVertexAttribArray(0); // vertex on location 0
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER, m.nbo);
            glEnableVertexAttribArray(1); // normals on loaction 1
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER, m.tbo);
            glEnableVertexAttribArray(2); // normals on loaction 1
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);


            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ibo);

            glBindVertexArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            m.indexsize = mr.indexsize;
        }

        void MeshManager::unloadMesh(Mesh & m){
            glDeleteBuffers(1,&m.vbo);
            m.vbo = 0;
            glDeleteBuffers(1,&m.nbo);
            m.nbo = 0;
            glDeleteBuffers(1,&m.tbo);
            m.tbo = 0;
            glDeleteBuffers(1,&m.ibo);
            m.ibo = 0;

            glDeleteVertexArrays(1,&m.vao);
            m.vao = 0;
        }

        void MeshManager::clean(){
            for(auto it = mesh_map.begin();it != mesh_map.end();it++){
                if(it->second.loaded){
                    unloadMesh(it->second.m);
                    it->second.loaded = false;
                }
            }
        }

        Mesh * MeshManager::getMesh(std::string name){
            auto it = mesh_map.find(name);    
            if(it == mesh_map.end()){
                //LOGLVL("[warning] mesh requested which is not in memory",Log::Level::RENDERING)
                return &default_shape.m;
            }else{
                if(it->second.loaded){
                    return &(it->second.m);
                }
                M_LOGLVL("[warning] mesh requested whuch is not in graphics memory",Log::Level::RENDERING)
                    return &it->second.m;
            }
        }
    }
}
