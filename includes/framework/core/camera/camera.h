#ifndef CG_FRAMEWORK_CORE_CAMERA_CAMERA_H
#define CG_FRAMEWORK_CORE_CAMERA_CAMERA_H

#include <core/object3D/object3D.h>

namespace CG{
    //a basic camera class that will be used for rendering
    class Camera : public Object3D{

    Matrix4 m_projectionMatrix;

    GLfloat m_near{ 1 };
    GLfloat m_far{ 10 };
    GLfloat m_fov{ 0.707 };
    GLfloat m_aspectRatio{ 16 / 9 };

    public:
        Camera();
        Camera(GLfloat near, GLfloat far, GLfloat fov, GLfloat aspectRatio);
        Camera(const Camera &other);

        void updateProjectionMatrix();

        void lookAt(const Vector3 position);
        void lookAt(float x, float y, float z);

        void setNear(GLfloat near);
        void setFar(GLfloat far);
        void setFOV(GLfloat fov);
        void setAspectRatio(GLfloat aspectRatio);

        GLfloat getNear();
        GLfloat getFar();
        GLfloat getFOV();
        GLfloat getAspectRatio();

        const Matrix4& getProjectionMatrix() const;
    };

}

#endif