#ifndef CAMERA_H
#define CAMERA_H

#include "../util/Math3D.h"
namespace NNY{
    namespace Render{

        class Camera{
            public:
                Camera(float fov = 90,float near = 1,float far = 10000.0,float aspectRatio = 1280/720);
                Matrix4d getViewProjection() const;
                Matrix4d getProjection() const;
                Matrix4d getView() const;
                void setPosition(double x,double y,double z);
                void lookAt(double x,double y,double z);

                void setPosition(Vector3d & rotation);

                void setAsCurrent();

                static Camera * current_camera;

                Quaterniond rotation;
                Vector3d position;
            private:
                Matrix4d perspective;
                bool is_current;

        };
    }
}

#endif /* CAMERA_H */
