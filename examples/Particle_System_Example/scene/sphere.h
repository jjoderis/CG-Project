#include <OpenGL/scene/OpenGLScene.h>
#include <OpenGL/geometry/sphereGeometry/OpenGLSphereGeometry.h>
#include <OpenGL/material/OpenGLMaterial.h>
#include <fileHandling/fileHandler.h>

void setUpSphereGeometry(CG::OpenGLMesh *mesh){
    std::shared_ptr<CG::OpenGLSphereGeometry> geoPtr = std::make_shared<CG::OpenGLSphereGeometry>(CG::OpenGLSphereGeometry{1.0, 30, 30});

    mesh->setGeometry(geoPtr);
}

void setUpRedMaterial(CG::OpenGLMesh *mesh){
    std::shared_ptr<CG::OpenGLMaterial> redPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{
        readTextFile("../media/shaders/phongTransformFeedback/phong.vert"),
        readTextFile("../media/shaders/phongTransformFeedback/phong.frag")
    });

    redPtr->setColor(1.0, 0.0, 0.0);
    redPtr->setShininess(120.0);

    redPtr->addUniform("modelViewMatrix");
    redPtr->addUniform("projectionMatrix");
    redPtr->addUniform("normalMatrix");
    redPtr->addUniform("viewMatrix");
    redPtr->addUniform("baseColor");
    redPtr->addUniform("shininess");
    redPtr->addUniform("modelMatrix");

    mesh->setMaterial(redPtr);
}

void setUpSphere(CG::OpenGLScene &scene){
    std::shared_ptr<CG::OpenGLMesh> redSphere(new CG::OpenGLMesh{});

    setUpSphereGeometry(redSphere.get());
    setUpRedMaterial(redSphere.get());

    void (*animation)(CG::Object3D&) = [](CG::Object3D &obj) {
        float radius{ std::dynamic_pointer_cast<CG::SphereGeometry>(dynamic_cast<CG::OpenGLMesh&>(obj).getGeometry())->getRadius() };
        CG::Matrix4 worldMatrix{obj.getMatrixWorld()};
        CG::Vector3 worldPos{ worldMatrix * CG::Vector4{ obj.getPosition(), 1.0} };

        for(int i = 0; i < 3; ++i){
        if(worldPos.at(i) + radius >= 10.0){
            CG::Vector3 normal{0.0, 0.0, 0.0};
            normal.set(i, 1.0);

            obj.setVelocity(obj.getVelocity().reflect(normal));
        }
        }

        for(int i = 0; i < 3; ++i){
        if(worldPos.at(i) - radius <= -10.0){
            CG::Vector3 normal{0.0, 0.0, 0.0};
            normal.set(i, -1.0);

            obj.setVelocity(obj.getVelocity().reflect(normal));
        }
        }

        obj.translate(obj.getVelocity());
        obj.updateMatrixWorld();
    };

    //redSphere->setVelocity(CG::Vector3{0.06, 0.05, 0.2});

    redSphere->setAnimation(animation);

    redSphere->setRenderFunction([](CG::OpenGLMesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 & projectionMatrix){
        std::shared_ptr<CG::OpenGLMaterial> material{ mesh->getMaterial() };
        std::shared_ptr<CG::OpenGLGeometry> geometry{ mesh->getGeometry() }; 

        CG::Matrix4 modelViewMatrix{ viewMatrix * mesh->getMatrixWorld() };
        //transpose inverse of modelView Matrix N = ((mV)^-1)^T = ((V * M)^-1)^T = (M^-1 * V^-1)^T
        
        CG::Matrix4 normalMatrix{(mesh->getMatrixWorldInverse(), viewMatrixInverse).transpose()};

        glUseProgram(material->getProgram());

        glUniform4fv(material->uniforms.at("baseColor"), 1, material->getColor().data());
        glUniformMatrix4fv(material->uniforms.at("modelMatrix"), 1, GL_FALSE, mesh->getMatrixWorld().data());
        glUniformMatrix4fv(material->uniforms.at("viewMatrix"), 1, GL_FALSE, viewMatrix.data());
        glUniformMatrix4fv(material->uniforms.at("modelViewMatrix"), 1, GL_FALSE, modelViewMatrix.data());
        glUniformMatrix4fv(material->uniforms.at("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
        glUniformMatrix4fv(material->uniforms.at("normalMatrix"), 1, GL_FALSE, normalMatrix.data());
        glUniform1f(material->uniforms.at("shininess"), material->getShininess());

        glBindVertexArray(geometry->getVAO());
        glDrawElements(GL_TRIANGLES, 3 * geometry->getNumFaces(), GL_UNSIGNED_INT, NULL);
    });

    redSphere->translate(3.0, 0.0, 0.0);
    redSphere->updateMatrixWorld();

    scene.addChild(redSphere);
}