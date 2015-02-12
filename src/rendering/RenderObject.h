#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

class Mesh;

#include "../util/Math3D.h"

struct RenderObject{
    Mesh * m;
    Matrix4d ModelMat;
};

#endif /* RENDEROBJECT */
