#ifndef CG_FRAMEWORK_CORE_MESH_MESH_H
#define CG_FRAMEWORK_CORE_MESH_MESH_H

#include <memory>
#include <core/object3D/object3D.h>
#include <core/geometry/geometry.h>
#include <core/material/material.h>

namespace CG{
    //a class that defines a renderable object in 3D space
    class Mesh : public Object3D{
    protected:
        //the objects geometry
        std::shared_ptr<CG::Geometry> m_geometry;
        //the objects material
        std::shared_ptr<CG::Material> m_material;

        std::weak_ptr<Mesh> m_parent; //use weak ptr to aleviate cyclic dependency issues
        std::vector<std::shared_ptr<Mesh>> m_children;

        void (*m_renderFunction)(Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){
            [](Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){
                (void)mesh;(void)viewMatrix;(void)viewMatrixInverse;(void)projectionMatrix;
            }
        };

    public:
        Mesh();

        Mesh(const CG::Geometry &geometry, const CG::Material &material);

        Mesh(const std::shared_ptr<CG::Geometry> &geometry, const std::shared_ptr<CG::Material> &material);

        Mesh(const Mesh &other);

        Mesh& operator= (const Mesh &other);

        void updateMatrixWorld();

        void setGeometry(const CG::Geometry &geometry);
        void setGeometry(const std::shared_ptr<CG::Geometry> &geometry);
        std::shared_ptr<CG::Geometry> getGeometry() const;

        void setMaterial(const CG::Material &material);
        void setMaterial(const std::shared_ptr<CG::Material> &material);
        std::shared_ptr<CG::Material> getMaterial() const;

        void addChild(std::shared_ptr<Mesh> newChild);
        void removeChild(Mesh *objPtr);
        const std::vector<std::shared_ptr<Mesh>>& getChildren() const;

        void setParent(std::shared_ptr<Mesh> obj);
        const std::shared_ptr<Mesh> getParent();

        void render(Matrix4 &viewMatrix, Matrix4 &viewMatrixInverse, Matrix4 &projectionMatrix);

        void setRenderFunction(void(*renderFunction)(Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix)); 
    };
}

#endif