#ifndef CG_FRAMEWORK_CORE_CAMERA_CAMERA_H
#define CG_FRAMEWORK_CORE_CAMERA_CAMERA_H

#include <object3D/object3D.h>

namespace CG{
    //a basic camera class that will be used for rendering
    class Camera : public Object3D{

    Matrix4 m_projectionMatrix;

    float m_near{ 1 };
    float m_far{ 10 };
    float m_fov{ 0.707 };
    float m_aspectRatio{ 16 / 9 };

    public:
        Camera();
        Camera(float near, float far, float fov, float aspectRatio);
        Camera(const Camera &other);

        void updateProjectionMatrix();

        void lookAt(const Vector3 position);
        void lookAt(float x, float y, float z);

        void setNear(float near);
        void setFar(float far);
        void setFOV(float fov);
        void setAspectRatio(float aspectRatio);

        float getNear();
        float getFar();
        float getFOV();
        float getAspectRatio();

        const Matrix4& getProjectionMatrix() const;
    };

}

#endif