#ifndef CG_FRAMEWORK_CORE_OBJECT3D_OBJECT3D
#define CG_FRAMEWORK_CORE_OBJECT3D_OBJECT3D

#include <GL/glew.h>
#include <memory>
#include <math/math.h>
#include <math/quaternion/quaternion.h>
#include <core/geometry/geometry.h>
#include <core/material/material.h>

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

        //matrix that can be used to transform the model coordinates to world coordinates
        Matrix4 m_worldMatrix{ createIdentityMatrix() };
        Matrix4 m_worldMatrixInverse{ createIdentityMatrix() };

        //matrix that can be used to transform normal vectors to world coordinates

    public:
        Object3D();

        //Copy constructor
        Object3D(const Object3D &other);

        Object3D& operator= (const Object3D &other);

        void updateMatrixWorld();

        void setPosition(const Vector3 &position);
        void setPosition(GLfloat x, GLfloat y, GLfloat z);
        void translate(const Vector3 &transVec);
        void translate(GLfloat x, GLfloat y, GLfloat z);

        void setScale(const Vector3 &scales);
        void setScale(GLfloat xFac, GLfloat yFac, GLfloat zFac);
        void scale(const Vector3 &scales);
        void scale(GLfloat xFac, GLfloat yFac, GLfloat zFac);
        void scale(GLfloat scale);

        void setRotation(const Quaternion &rotation);
        void setRotation(const Vector3 &axis, GLfloat amount);
        void setRotation(GLfloat axisX, GLfloat axisY, GLfloat axisZ, GLfloat amount);
        void rotate(const Vector3 &axis, GLfloat amount);
        void rotate(GLfloat axisX, GLfloat axisY, GLfloat axisZ, GLfloat amount);
        void rotateX(GLfloat amount);
        void rotateY(GLfloat amount);
        void rotateZ(GLfloat amount);
        void resetRotation();
        
        //returns a reference to the objects position
        Vector3& getPosition();

        Vector3& getScale();

        Quaternion& getRotation();

        const Matrix4& getMatrixWorld() const;
        const Matrix4& getMatrixWorldInverse() const;

    };
}

#endif