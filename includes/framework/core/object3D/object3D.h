#ifndef CG_FRAMEWORK_CORE_OBJECT3D_OBJECT3D
#define CG_FRAMEWORK_CORE_OBJECT3D_OBJECT3D

#include <GL/glew.h>
#include <memory>
#include <core/math/math.h>
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

        //matrix that can be used to transform the model coordinates to world coordinates
        CG::Matrix4 m_worldMatrix;

        std::weak_ptr<CG::Object3D> m_parent; //use weak ptr to aleviate cyclic dependency issues
        std::vector<std::shared_ptr<CG::Object3D>> m_children;

    public:
        Object3D();

        //Copy constructor
        Object3D(const Object3D &other);

        virtual Object3D& operator= (const Object3D &other);

        void updateMatrixWorld();

        void setPosition(const CG::Vector3 &position);
        void translate(const CG::Vector3 &transVec);

        void setScale(const CG::Vector3 &scales);
        void scale(const CG::Vector3 &scales);
        void scale(GLfloat scale);
        
        //returns a reference to the objects position
        CG::Vector3& getPosition();

        CG::Vector3& getScale();

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