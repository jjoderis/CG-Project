#ifndef CG_FRAMEWORK_OPENGL_SCENE_OPENGLSCENE_OPENGLSCENE_H
#define CG_FRAMEWORK_OPENGL_SCENE_OPENGLSCENE_OPENGLSCENE_H

#include <core/scene/scene.h>
#include <OpenGL/mesh/OpenGLMesh.h>
#include <core/light/light.h>
#include <core/light/pointLight/pointLight.h>

namespace CG{
    class OpenGLScene: public CG::Scene<CG::OpenGLMesh>{
    protected:
        GLuint m_lightInfoUbo{ 0 };
    public:
        OpenGLScene();

        virtual void addLight(std::shared_ptr<CG::Light> &light) override;
        virtual void addChild(std::shared_ptr<CG::OpenGLMesh> mesh) override;

        void updateLightInfoUBO() const;
        void updateLightInBuffer(int i) const;
    };
}


#endif