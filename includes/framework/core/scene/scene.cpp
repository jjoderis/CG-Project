#include <core/scene/scene.h>

CG::Scene::Scene(){}

CG::Scene::Scene(const Camera &camera){
    m_camera = camera;
}

void CG::Scene::setCamera(const Camera &camera){
    m_camera = camera;
}

CG::Camera& CG::Scene::getCamera(){
    return m_camera;
}