#include "Camera.h"

#include <cmath>

#include"../util/Log.h"
#include"../util/Math3D.h"

namespace NNY{
    namespace Render{

        Camera::Camera(float fov,float near,float far,float aspectRatio){
            perspective.toPerspective(fov,aspectRatio,near,far);
            LOG_DEBUG(MathUtil::matrixToStr(perspective))
        }

        Matrix4d Camera::getViewProjection() const{
            Matrix4d rot = rotation.conjugate().toMatrix();
            Matrix4d trans = Matrix4d().toTranslation(position * -1);
            //TODO scale??
            //In order to move the camera downwards we actually 
            //need to move the world opisite direction.
            return perspective * rot * trans;
        }

        Matrix4d Camera::getView() const{
            Matrix4d rot = rotation.conjugate().toMatrix();
            Matrix4d trans = Matrix4d().toTranslation(position * -1);
            //TODO scale??
            //In order to move the camera downwards we actually 
            //need to move the world opisite direction.
            return rot * trans;
        }

        Matrix4d Camera::getProjection() const{
            return perspective;
        }

        void Camera::setPosition(double x,double y,double z){
            position.set(x,y,z);
        }

        void Camera::lookAt(double x,double y,double z){
            Vector3d lookVector(x,y,z);
            Vector3d forward = (lookVector-position).normalize();

            double dot = Vector3d(0,0,1).dot(forward);

            if(std::fabs(dot - (-1.0)) < 0.000001){
                rotation = Quaterniond(Vector3d(0,1,0),MATH_PI);
                return;
            }
            else if(std::fabs(dot -(1.0)) < 0.000001){
                rotation = Quaterniond();
                return;
            }

            double rotAngle = std::acos(dot);
            Vector3d rotAxis = Vector3d(0,0,1).cross(forward).normalize();
            rotation = Quaterniond(rotAxis,rotAngle);
        }
    }
}
