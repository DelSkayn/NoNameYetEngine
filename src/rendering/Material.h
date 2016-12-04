#ifndef MATERIAL_H
#define MATERIAL_H

#include "../util/Math3D.h"
#include <memory>
#include <climits>

namespace NNY{
namespace Render{

#define NO_TEXTURE UINT_MAX;

struct Material{
    float roughness;
    float metalness;
    Vector3f color;
    unsigned int diffuse_texture_index;
    unsigned int normal_texture_index;
};

}
}

#endif //MATERIAL_H
