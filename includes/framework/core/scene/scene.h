#ifndef CG_FRAMEWORK_CORE_SCENE_SCENE_H
#define CG_FRAMEWORK_CORE_SCENE_SCENE_H

#include <core/object3D/object3D.h>
#include <core/mesh/mesh.h>
#include <core/color/color.h>

namespace CG{
    //a scene that holds the whole rendering context (all objects, the camera, etc)
    class Scene : public Object3D{
    protected:
        RGBA_Color m_background{ 0.0, 0.0, 0.0, 1.0 };

        std::vector<std::shared_ptr<CG::Mesh>> m_children;

    public:
        Scene();
        Scene(const RGBA_Color &background);

        void setBackground(const RGBA_Color &background);
        const RGBA_Color& getBackground() const;

        void addChild(std::shared_ptr<Mesh> newChild);
        void removeChild(Mesh *objPtr);
        const std::vector<std::shared_ptr<Mesh>>& getChildren() const;
    };
}

#endif