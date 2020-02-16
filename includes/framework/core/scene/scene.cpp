#include "scene.h"

template <typename meshClass>
CG::Scene<meshClass>::Scene(){}

template <typename meshClass>
CG::Scene<meshClass>::Scene(const RGBA_Color &background) : m_background{ background} {}

template <typename meshClass>
void CG::Scene<meshClass>::setBackground(const RGBA_Color &background){
    m_background = background;
}

template <typename meshClass>
const CG::RGBA_Color& CG::Scene<meshClass>::getBackground() const{
    return m_background;
}

template <typename meshClass>
void CG::Scene<meshClass>::addChild(std::shared_ptr<meshClass> newChild){
    m_children.emplace_back(newChild);
}

template <typename meshClass>
void CG::Scene<meshClass>::removeChild(meshClass *objPtr){
    for(unsigned int i = 0; i < m_children.size(); ++i){
        if(m_children[i].get() == objPtr){
            m_children.erase(m_children.begin() + i);
            break;
        }
    }
}

template <typename meshClass>
const std::vector<std::shared_ptr<meshClass>>& CG::Scene<meshClass>::getChildren() const{
    return m_children;
}

template <typename meshClass>
void CG::Scene<meshClass>::addParticles(const std::shared_ptr<meshClass> particles){
    m_particles.emplace_back(particles);
}

template <typename meshClass>
void CG::Scene<meshClass>::removeParticles(meshClass *objPtr){
    for(unsigned int i = 0; i < m_particles.size(); ++i){
        if(m_particles[i].get() == objPtr){
            m_particles.erase(m_particles.begin() + i);
            break;
        }
    }
}

template <typename meshClass>
const std::vector<std::shared_ptr<meshClass>>& CG::Scene<meshClass>::getParticles() const{
    return m_particles;
}

template <typename meshClass>
void CG::Scene<meshClass>::addLight(std::shared_ptr<CG::Light> &light){
    m_lights.emplace_back(light);
}