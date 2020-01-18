#ifndef CG_FRAMEWORK_CORE_MESH_MESH_H
#define CG_FRAMEWORK_CORE_MESH_MESH_H

#include <memory>
#include <core/object3D/object3D.h>
#include <core/geometry/geometry.h>
#include <core/material/material.h>
#include <string>

namespace CG{
    //a class that defines a renderable object in 3D space
    //templated for use with different derived geometries and materials
    template <typename geometryClass, typename materialClass>
    class Mesh : public Object3D{
    protected:

        std::string m_name{};
        //the objects geometry
        std::shared_ptr<geometryClass> m_geometry;
        //the objects material
        std::shared_ptr<materialClass> m_material;

        std::weak_ptr<Mesh<geometryClass, materialClass>> m_parent; //use weak ptr to aleviate cyclic dependency issues
        std::vector<std::shared_ptr<Mesh<geometryClass, materialClass>>> m_children;

        void (*m_renderFunction)(Mesh<geometryClass, materialClass> *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){
            [](Mesh<geometryClass, materialClass> *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){
                (void)mesh;(void)viewMatrix;(void)viewMatrixInverse;(void)projectionMatrix;
            }
        };

    public:
        Mesh();

        Mesh(const geometryClass &geometry, const materialClass &material);

        Mesh(const std::shared_ptr<geometryClass> &geometry, const std::shared_ptr<materialClass> &material);

        Mesh(const Mesh &other);

        Mesh<geometryClass, materialClass>& operator= (const Mesh<geometryClass, materialClass> &other);

        void updateMatrixWorld();

        void setName(std::string &name);
        void setName(const char* name);
        const std::string& getName();

        void setGeometry(const geometryClass &geometry);
        void setGeometry(const std::shared_ptr<geometryClass> &geometry);
        std::shared_ptr<geometryClass> getGeometry() const;

        void setMaterial(const materialClass &material);
        void setMaterial(const std::shared_ptr<materialClass> &material);
        std::shared_ptr<materialClass> getMaterial() const;

        void addChild(std::shared_ptr<Mesh<geometryClass, materialClass>> newChild);
        void removeChild(Mesh<geometryClass, materialClass> *objPtr);
        const std::vector<std::shared_ptr<Mesh<geometryClass, materialClass>>>& getChildren() const;

        void setParent(std::shared_ptr<Mesh<geometryClass, materialClass>> obj);
        const std::shared_ptr<Mesh<geometryClass, materialClass>> getParent();

        void render(const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix);

        void setRenderFunction(void(*renderFunction)(Mesh<geometryClass, materialClass> *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix)); 
    };

    using BaseMesh = Mesh<CG::Geometry, CG::Material>;
}

#endif