#include <OpenGL/scene/OpenGLScene.h>
#include <OpenGL/geometry/sphereGeometry/OpenGLSphereGeometry.h>
#include <OpenGL/material/OpenGLMaterial.h>
#include <fileHandling/fileHandler.h>
#include <random>

void setUpParticleGeometry(CG::OpenGLMesh *mesh){
    std::shared_ptr<CG::OpenGLGeometry> geoPtr = std::make_shared<CG::OpenGLGeometry>(CG::OpenGLGeometry{});

    std::vector<float> particleData(3*2*100);

    for(int i = 0; i < 100; ++i){
        float randX{static_cast<float>(rand())/(RAND_MAX/2) - 1.0f};
        float randY{static_cast<float>(rand())/(RAND_MAX/2) - 1.0f};
        float randZ{static_cast<float>(rand())/(RAND_MAX/2) - 1.0f};
        particleData[6*i] = randX;
        particleData[6*i+1] = randY;
        particleData[6*i+2] = randZ;
        particleData[6*i+3] = 0.0;
        particleData[6*i+4] = -0.15;
        particleData[6*i+5] = 0.0;
    }

    unsigned int VAO{ 0 };
    unsigned int VBO{ 0 };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glCreateBuffers(1, &VBO);
    glNamedBufferStorage(VBO, 2 * 3 * sizeof(float) * 100, particleData.data(), 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    geoPtr->setVAO(VAO);
    geoPtr->setVBO(VBO);

    mesh->setGeometry(geoPtr);
}

void setUpParticleMaterial(CG::OpenGLMesh *mesh){
    std::shared_ptr<CG::OpenGLMaterial> matPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{
        R"(
            #version 450 core

            layout (location = 0) in vec3 vPosition;
            layout (location = 1) in vec3 vVelocity;

            uniform mat4 viewMatrix;
            uniform mat4 projectionMatrix;

            layout (xfb_offset=0) out vec3 position;
            layout (xfb_offset=12) out vec3 velocity;
            
            void main(){
                velocity = vVelocity;

                if(vPosition.y < -10.0){
                    position = vec3(vPosition.x, 10.0, vPosition.z);
                } else {
                   position = vPosition + vVelocity;
                }

                gl_Position = projectionMatrix * viewMatrix * vec4(vPosition, 1.0);
            }
        )",
        R"(
            #version 450 core

            uniform vec4 baseColor;

            layout (location = 0) out vec4 fColor;

            void main(){
                fColor= baseColor;
            }
        )"
    });

    matPtr->addUniform("viewMatrix");
    matPtr->addUniform("projectionMatrix");
    matPtr->addUniform("baseColor");

    mesh->setMaterial(matPtr);
}

void setUpParticles(CG::OpenGLScene &scene){

    std::shared_ptr<CG::OpenGLMesh> partMesh1{ new CG::OpenGLMesh{} };
    std::shared_ptr<CG::OpenGLMesh> partMesh2{ new CG::OpenGLMesh{} };

    setUpParticleGeometry(partMesh1.get());
    setUpParticleMaterial(partMesh1.get());
    setUpParticleGeometry(partMesh2.get());
    setUpParticleMaterial(partMesh2.get());

    partMesh1->setRenderFunction([](CG::OpenGLMesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 &projectionMatrix){
        (void)viewMatrixInverse;
        
        std::shared_ptr<CG::OpenGLMaterial> material{ mesh->getMaterial() };
        std::shared_ptr<CG::OpenGLGeometry> geometry{ mesh->getGeometry() }; 

        glUseProgram(material->getProgram());

        glUniform4fv(material->uniforms.at("baseColor"), 1, material->getColor().data());
        glUniformMatrix4fv(material->uniforms.at("viewMatrix"), 1, GL_FALSE, viewMatrix.data());
        glUniformMatrix4fv(material->uniforms.at("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());

        glBindVertexArray(geometry->getVAO());
    });

    partMesh2->setRenderFunction([](CG::OpenGLMesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 &projectionMatrix){
        (void)viewMatrixInverse;
        
        std::shared_ptr<CG::OpenGLMaterial> material{ mesh->getMaterial() };
        std::shared_ptr<CG::OpenGLGeometry> geometry{ mesh->getGeometry() }; 

        glUseProgram(material->getProgram());

        glUniform4fv(material->uniforms.at("baseColor"), 1, material->getColor().data());
        glUniformMatrix4fv(material->uniforms.at("viewMatrix"), 1, GL_FALSE, viewMatrix.data());
        glUniformMatrix4fv(material->uniforms.at("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());

        glBindVertexArray(geometry->getVAO());
    });

    scene.addParticles(partMesh1);
    scene.addParticles(partMesh2);
}