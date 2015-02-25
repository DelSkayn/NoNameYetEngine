#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "../util/Math3D.h"

namespace NNY{
    namespace Render{

        class Mesh;


        struct RenderObject{
            Mesh * m;
            Matrix4d ModelMat;
        };
    }
}

#endif /* RENDEROBJECT */
