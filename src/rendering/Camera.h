#ifndef CAMERA_H
#define CAMERA_H

#include "../util/Math3D.h"

class Camera{
    public:
        Camera(float fov = 90,float near = 1,float far = 10000.0,float aspectRatio = 600/400);
        Matrix4d getCameraMatrix() const;
        void setPosition(double x,double y,double z);
        void lookAt(double x,double y,double z);
    private:
    Vector3d position;
    Quaterniond rotation;
    Matrix4d perspective;
};

#endif /* CAMERA_H */
