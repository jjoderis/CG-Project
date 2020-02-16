#ifndef CG_FRAMEWORK_CORE_SCENE_SCENE_H
#define CG_FRAMEWORK_CORE_SCENE_SCENE_H

#include <object3D/object3D.h>
#include <mesh/mesh.h>
#include <color/color.h>
#include <light/light.h>

namespace CG{
    //a scene that holds the whole rendering context (all objects, the camera, etc)
    template<typename meshClass>
    class Scene : public Object3D{
    protected:
        RGBA_Color m_background{ 0.0, 0.0, 0.0, 1.0 };

        std::vector<std::shared_ptr<meshClass>> m_children;

        std::vector<std::shared_ptr<meshClass>> m_particles;

        std::vector<std::shared_ptr<Light>> m_lights;

    public:
        Scene();
        Scene(const RGBA_Color &background);

        void setBackground(const RGBA_Color &background);
        const RGBA_Color& getBackground() const;

        virtual void addChild(std::shared_ptr<meshClass> newChild);
        void removeChild(meshClass *objPtr);
        const std::vector<std::shared_ptr<meshClass>>& getChildren() const;

        void addParticles(const std::shared_ptr<meshClass> particles);
        void removeParticles(meshClass *objPtr);
        const std::vector<std::shared_ptr<meshClass>>& getParticles() const;

        virtual void addLight(std::shared_ptr<CG::Light> &light);
    };

    using BaseScene = Scene<BaseMesh>;
}

#endif