#ifndef LIGHT_H
#define LIGHT_H

#include "../util/Math3D.h" 

namespace NNY{
namespace Render{

struct DirectionalLight{
    float intensity;
    Vector3f color;
    Vector3f direction;
};

struct PointLight{
    float intensity;
    Vector3f color;
    Vector3f position;
};

struct SpotLight{
    float intensity;
    float Angle;
    Vector3f color;
    Vector3f position;
    Quaternionf rotation;
};

}}

#endif /* LIGHT_H */
