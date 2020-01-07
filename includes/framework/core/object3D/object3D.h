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
        CG::Vector3 m_position{ 0.0, 0.0, 0.0 };

        //scaling factors in x, y and z direction
        CG::Vector3 m_scale{ 1.0, 1.0, 1.0 };

        //quaternion representing the rotation of the object
        CG::Quaternion m_rotation{ 0.0, 0.0, 0.0, 1.0 };

        //shearing matrix
        CG::Matrix4 m_shear;

        //matrix that can be used to transform the model coordinates to world coordinates
        CG::Matrix4 m_worldMatrix;
        CG::Matrix4 m_worldMatrixInverse;

        //matrix that can be used to transform normal vectors to world coordinates

        std::weak_ptr<CG::Object3D> m_parent; //use weak ptr to aleviate cyclic dependency issues
        std::vector<std::shared_ptr<CG::Object3D>> m_children;

    public:
        Object3D();

        //Copy constructor
        Object3D(const Object3D &other);

        virtual Object3D& operator= (const Object3D &other);

        void updateMatrixWorld();

        void setPosition(const CG::Vector3 &position);
        void setPosition(GLfloat x, GLfloat y, GLfloat z);
        void translate(const CG::Vector3 &transVec);
        void translate(GLfloat x, GLfloat y, GLfloat z);

        void setScale(const CG::Vector3 &scales);
        void setScale(GLfloat xFac, GLfloat yFac, GLfloat zFac);
        void scale(const CG::Vector3 &scales);
        void scale(GLfloat xFac, GLfloat yFac, GLfloat zFac);
        void scale(GLfloat scale);

        void setRotation(const CG::Quaternion &rotation);
        void setRotation(const CG::Vector3 &axis, GLfloat amount);
        void setRotation(GLfloat axisX, GLfloat axisY, GLfloat axisZ, GLfloat amount);
        void rotate(const CG::Vector3 &axis, GLfloat amount);
        void rotate(GLfloat axisX, GLfloat axisY, GLfloat axisZ, GLfloat amount);
        void rotateX(GLfloat amount);
        void rotateY(GLfloat amount);
        void rotateZ(GLfloat amount);
        void resetRotation();

        void shear(int sheared, int shearing, float amount);
        void resetShearing();
        
        //returns a reference to the objects position
        CG::Vector3& getPosition();

        CG::Vector3& getScale();

        CG::Quaternion& getRotation();

        //calls virtual render function on all children
        virtual void render();

        void addChild(std::shared_ptr<CG::Object3D> newChild);
        void removeChild(CG::Object3D *objPtr);
        const std::vector<std::shared_ptr<CG::Object3D>>& getChildren();

        void setParent(std::shared_ptr<CG::Object3D> obj);
        const std::shared_ptr<CG::Object3D> getParent();
    };
}

#endif