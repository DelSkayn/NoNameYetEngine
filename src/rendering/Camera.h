#ifndef CAMERA_H
#define CAMERA_H

#include "../util/Math3D.h"

class Camera{
    public:
        Camera(float fov = 90,float near = 1,float far = 10000.0,float aspectRatio = 1280/720);
        Matrix4d getViewProjection() const;
        Matrix4d getProjection() const;
        Matrix4d getView() const;
        void setPosition(double x,double y,double z);
        void lookAt(double x,double y,double z);
        Quaterniond rotation;
        Vector3d position;
    private:
        Matrix4d perspective;
};

#endif /* CAMERA_H */
