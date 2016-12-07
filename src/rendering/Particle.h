#ifndef PARTICLE_H
#define PARTICLE_H

#include <GL/glew.h>
#include <vector>

namespace NNY{
namespace Render{

class Particle{
    public
        Particle(std::string tex_path,unsigned x_div,unsigned y_div,unsigned max,float life_step,float max_life);
        std::vector<Vector3f> particle_pos;
        std::vector<Vector3f> particle_velocity;
        std::vector<float> particle_life;
    private:
        Particle();
        unsigned first,last;
        unsigned max;
        float life_step,max_life;
        GLuint texture;
        GLuint vertex;
        GLuint life;
}

}}

#endif
