#ifndef CG_FRAMEWORK_CORE_CAMERA_CAMERA_H
#define CG_FRAMEWORK_CORE_CAMERA_CAMERA_H

#include <core/object3D/object3D.h>

namespace CG{
    //a basic camera class that will be used for rendering
    class Camera : public Object3D{

    Matrix4 m_projectionMatrix;

    GLfloat m_near = 1;
    GLfloat m_far = 10;
    GLfloat m_left = -1;
    GLfloat m_right = 1;
    GLfloat m_bottom = -1;
    GLfloat m_top = 1;

    public:
        Camera();
        Camera(GLfloat near, GLfloat far, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);
        Camera(const Camera &other);

        void updateProjectionMatrix();

        void lookAt(const Vector3 position);
        void lookAt(float x, float y, float z);
    };

}

#endif