#include <core/scene/scene.h>

CG::Scene::Scene(){}

CG::Scene::Scene(const RGBA_Color &background) : m_background{ background} {}

void CG::Scene::setBackground(const RGBA_Color &background){
    m_background = background;
}

const CG::RGBA_Color& CG::Scene::getBackground() const{
    return m_background;
}

void CG::Scene::addChild(std::shared_ptr<Mesh> newChild){
    m_children.emplace_back(newChild);
}

void CG::Scene::removeChild(Mesh *objPtr){
    for(unsigned int i = 0; i < m_children.size(); ++i){
        if(m_children[i].get() == objPtr){
            m_children.erase(m_children.begin() + i);
            break;
        }
    }
}

const std::vector<std::shared_ptr<CG::Mesh>>& CG::Scene::getChildren() const{
    return m_children;
}