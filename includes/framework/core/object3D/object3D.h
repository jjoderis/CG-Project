#ifndef CG_FRAMEWORK_CORE_OBJECT3D_OBJECT3D
#define CG_FRAMEWORK_CORE_OBJECT3D_OBJECT3D

#include <math/math.h>
#include <math/quaternion/quaternion.h>

namespace CG{
    //base class for an Object in 3D space (Mesh, Camera, etc.)
    //contains information regarding position, scale, etc
    class Object3D{
    
    protected:
        //position of the object in 3D space
        Vector3 m_position{ 0.0, 0.0, 0.0 };

        //scaling factors in x, y and z direction
        Vector3 m_scale{ 1.0, 1.0, 1.0 };

        //quaternion representing the rotation of the object
        Quaternion m_rotation{ 0.0, 0.0, 0.0, 1.0 };

        //an objects velocity: speed in regard to direction
        Vector3 m_velocity{ 0.0, 0.0, 0.0 };

        //matrix that can be used to transform the model coordinates to world coordinates
        Matrix4 m_worldMatrix{ createIdentityMatrix() };
        Matrix4 m_worldMatrixInverse{ createIdentityMatrix() };

        void (*m_animationPtr)(Object3D&);

    public:
        bool isAnimated{ false };

        Object3D();

        virtual ~Object3D();

        //Copy constructor
        Object3D(const Object3D &other);

        Object3D& operator= (const Object3D &other);

        void updateMatrixWorld();

        void setPosition(const Vector3 &position);
        void setPosition(float x, float y, float z);
        void translate(const Vector3 &transVec);
        void translate(float x, float y, float z);

        void setScale(const Vector3 &scales);
        void setScale(float xFac, float yFac, float zFac);
        void scale(const Vector3 &scales);
        void scale(float xFac, float yFac, float zFac);
        void scale(float scale);

        void setRotation(const Quaternion &rotation);
        void setRotation(const Vector3 &axis, float amount);
        void setRotation(float axisX, float axisY, float axisZ, float amount);
        void rotate(const Vector3 &axis, float amount);
        void rotate(float axisX, float axisY, float axisZ, float amount);
        void rotateX(float amount);
        void rotateY(float amount);
        void rotateZ(float amount);
        void resetRotation();
        
        //returns a reference to the objects position
        Vector3& getPosition();

        Vector3& getScale();

        Quaternion& getRotation();

        const Matrix4& getMatrixWorld() const;
        const Matrix4& getMatrixWorldInverse() const;

        void setVelocity(const Vector3 &velocity);
        const Vector3& getVelocity();

        void animate();

        void setAnimation(void (*animationPtr)(Object3D&));
        void deleteAnimation();
    };
}

#endif