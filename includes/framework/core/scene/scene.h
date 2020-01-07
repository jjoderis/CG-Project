#ifndef CG_FRAMEWORK_CORE_SCENE_SCENE_H
#define CG_FRAMEWORK_CORE_SCENE_SCENE_H

#include <core/object3D/object3D.h>
#include <core/camera/camera.h>

namespace CG{
    //a scene that holds the whole rendering context (all objects, the camera, etc)
    class Scene : public CG::Object3D{
    private:
        CG::Camera m_camera;

    public:
        Scene();
        Scene(const Camera &camera);

        void setCamera(const Camera &camera);
        Camera& getCamera();
        void render();
    };
}

#endif