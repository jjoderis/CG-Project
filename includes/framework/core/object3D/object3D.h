#ifndef CG_FRAMEWORK_CORE_OBJECT3D_OBJECT3D
#define CG_FRAMEWORK_CORE_OBJECT3D_OBJECT3D

#include <GL/glew.h>
#include <memory>
#include <LinAlg/vector/vector.h>
#include <core/geometry/geometry.h>
#include <core/material/material.h>

namespace CG{
    //base class for an Object in 3D space (Mesh, Camera, etc.)
    //contains information regarding position, scale, etc
    class Object3D{
    
    protected:
        //position of the object in 3D space
        CG::LinAlg::Vector4<GLfloat> m_position{ 0.0, 0.0, 0.0, 1.0 };

    public:
        Object3D();

        //Copy constructor
        Object3D(const Object3D & other);

        virtual Object3D& operator= (const Object3D &other);

        void setPosition(const CG::LinAlg::Vector4<GLfloat> position);
        
        //returns a reference to the objects position
        CG::LinAlg::Vector4<GLfloat>& getPosition();
    };
}

#endif