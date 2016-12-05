#ifndef MATERIAL_H
#define MATERIAL_H

#include "../util/Math3D.h"
#include <memory>
#include <climits>

#define NO_TEXTURE UINT_MAX

namespace NNY{
namespace Render{


struct Material{
    float roughness;
    float metalness;
    Vector3f color;
    unsigned int albedo_texture_index;
    unsigned int normal_texture_index;
    unsigned int roughness_texture_index;
};

}
}

#endif //MATERIAL_H
