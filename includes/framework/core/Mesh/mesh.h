#ifndef CG_FRAMEWORK_CORE_MESH_MESH_H
#define CG_FRAMEWORK_CORE_MESH_MESH_H

#include <core/object3D/object3D.h>

namespace CG{
    //a class that defines a renderable object in 3D space
    class Mesh : public Object3D{

    protected:
        //the objects geometry
        std::shared_ptr<CG::Geometry> m_geometry;
        //the objects material
        std::shared_ptr<CG::Material> m_material;

    public:
        Mesh();

        Mesh(const CG::Geometry &geometry, const CG::Material &material);

        Mesh(const std::shared_ptr<CG::Geometry> &geometry, const std::shared_ptr<CG::Material> &material);

        Mesh(const Mesh &other);

        virtual Mesh& operator= (const Mesh &other);

        void setGeometry(const CG::Geometry &geometry);
        void setGeometry(const std::shared_ptr<CG::Geometry> &geometry);
        std::shared_ptr<CG::Geometry>& getGeometry();

        void setMaterial(const CG::Material &material);
        void setMaterial(const std::shared_ptr<CG::Material> &material);
        std::shared_ptr<CG::Material>& getMaterial();

        //uses geometry and material to render object
        void render() const;
    };
}

#endif