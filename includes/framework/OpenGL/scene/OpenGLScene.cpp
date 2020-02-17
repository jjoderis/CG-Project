#include "OpenGLScene.h"
#include <core/scene/scene.cpp>

template class CG::Scene<CG::OpenGLMesh>;

CG::OpenGLScene::OpenGLScene(){
    glCreateBuffers(1, &m_lightInfoUbo);
    int init{ 0 };
    glNamedBufferData(m_lightInfoUbo, sizeof(int), &init, GL_DYNAMIC_DRAW);
}

void CG::OpenGLScene::addLight(std::shared_ptr<CG::Light> &light){
    m_lights.emplace_back(light);

    updateLightInfoUBO();

    int curIndex{ static_cast<int>(m_lights.size()) - 1 };
    //register for updates of light to update ubo when information changes
    light->registerForCallback(this, [curIndex, this](const char* event){
        this->updateLightInBuffer(curIndex);
    });
}

//TODO: bind ubo to mesh material program
void CG::OpenGLScene::addChild(std::shared_ptr<CG::OpenGLMesh> mesh){
    m_children.emplace_back(mesh);

    int program = mesh->getMaterial()->getProgram();
    int index = glGetUniformBlockIndex(program, "Lights");

    if (index != GL_INVALID_INDEX) {
        glBindBufferBase(GL_UNIFORM_BUFFER, index, m_lightInfoUbo);
    }
}

struct LightPorperties{
    float isEnabled; //cast bools to float for needed padding
    float isLocal;
    float isSpot;

    float pad1;

    float ambient[4];
    float lightColor[4];
    float lightPosition[4];

    float lightDirection[4];
    float coneDirection[4];
    float spotCosCutoff;
    float spotExponent;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;

    float pad2[3];
};

void CG::OpenGLScene::updateLightInfoUBO() const{
    int numLights{ static_cast<int>(m_lights.size()) };
    glNamedBufferData(m_lightInfoUbo, numLights * sizeof(LightPorperties) + 4 * sizeof(int), NULL, GL_STATIC_DRAW);
    glNamedBufferSubData(m_lightInfoUbo, 0, sizeof(int), &numLights);

    for (int i = 0; i < numLights; ++i) {
        updateLightInBuffer(i);
    }
}

void CG::OpenGLScene::updateLightInBuffer(int i) const{
    CG::Light *light{ m_lights.at(i).get() };
    LightPorperties props{
        static_cast<float>(light->isEnabled()),
        static_cast<float>(light->isLocal()),
        static_cast<float>(light->isSpot()),

        1.0,

        light->ambient().at(0), light->ambient().at(1), light->ambient().at(2), light->ambient().at(3),
        light->getColor().at(0), light->getColor().at(1), light->getColor().at(2), light->getColor().at(3),
        light->getPosition().at(0), light->getPosition().at(1), light->getPosition().at(2), 1.0,

        light->halfVector().at(0), light->halfVector().at(1), light->halfVector().at(2), light->halfVector().at(3),
        light->coneDirection().at(0), light->coneDirection().at(1), light->coneDirection().at(2), light->coneDirection().at(3),
        light->spotCosCutoff(),
        light->spotExponent(),
        light->constantAttenuation(),
        light->linearAttenuation(),
        light->quadraticAttenuation(),

        1.0, 1.0, 1.0
    };

    glNamedBufferSubData(m_lightInfoUbo, 4 * sizeof(int) + i * sizeof(LightPorperties), sizeof(LightPorperties), &props);
}