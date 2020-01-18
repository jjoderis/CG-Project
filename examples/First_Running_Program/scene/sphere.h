#include <OpenGL/scene/OpenGLScene.h>
#include <OpenGL/geometry/sphereGeometry/OpenGLSphereGeometry.h>
#include <OpenGL/material/OpenGLMaterial.h>
#include <fileHandling/fileHandler.h>

void setUpSphere(CG::OpenGLScene &scene){
    std::shared_ptr<CG::OpenGLSphereGeometry> geoPtr = std::make_shared<CG::OpenGLSphereGeometry>(CG::OpenGLSphereGeometry{1.0, 30, 30});
  
    std::shared_ptr<CG::OpenGLMaterial> redPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{
        readTextFile("../media/shaders/phongShader/phong.vert"),
        readTextFile("../media/shaders/phongShader/phong.frag")
    });

    redPtr->setColor(1.0, 0.0, 0.0);
    redPtr->setShininess(120.0);

    std::shared_ptr<CG::OpenGLMesh> redSphere(new CG::OpenGLMesh{geoPtr, redPtr});

    void (*animation)(CG::Object3D&) = [](CG::Object3D &obj) {
        float radius{ std::dynamic_pointer_cast<CG::SphereGeometry>(dynamic_cast<CG::OpenGLMesh&>(obj).getGeometry())->getRadius() };
        CG::Matrix4 worldMatrix{obj.getMatrixWorld()};
        CG::Vector3 worldPos{ dot(worldMatrix, CG::Vector4{ obj.getPosition(), 1.0} ) };

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

    redSphere->setVelocity(CG::Vector3{0.06, 0.05, 0.2});

    redSphere->setAnimation(animation);

    redSphere->setRenderFunction([](CG::OpenGLMesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 & projectionMatrix){
        std::shared_ptr<CG::OpenGLMaterial> material{ mesh->getMaterial() };
        std::shared_ptr<CG::OpenGLGeometry> geometry{ mesh->getGeometry() }; 

        CG::Matrix4 modelViewMatrix{dot(viewMatrix, mesh->getMatrixWorld())};
        //transpose inverse of modelView Matrix N = ((mV)^-1)^T = ((V * M)^-1)^T = (M^-1 * V^-1)^T
        
        CG::Matrix4 normalMatrix{dot(mesh->getMatrixWorldInverse(), viewMatrixInverse).transpose()};

        glUseProgram(material->getProgram());

        glUniform4fv(material->uniformLocs.baseColor, 1, material->getColor().data());
        glUniformMatrix4fv(material->uniformLocs.modelMatrix, 1, GL_FALSE, mesh->getMatrixWorld().data());
        glUniformMatrix4fv(material->uniformLocs.viewMatrix, 1, GL_FALSE, viewMatrix.data());
        glUniformMatrix4fv(material->uniformLocs.modelViewMatrix, 1, GL_FALSE, modelViewMatrix.data());
        glUniformMatrix4fv(material->uniformLocs.projectionMatrix, 1, GL_FALSE, projectionMatrix.data());
        glUniformMatrix4fv(material->uniformLocs.normalMatrix, 1, GL_FALSE, normalMatrix.data());
        glUniform1f(material->uniformLocs.shininess, material->getShininess());

        glBindVertexArray(geometry->getVAO());
        glDrawElements(GL_TRIANGLES, 3 * geometry->getNumFaces(), GL_UNSIGNED_INT, NULL);
        

        for(const std::shared_ptr<CG::OpenGLMesh> &child : mesh->getChildren()){
            child->render(viewMatrix, viewMatrixInverse, projectionMatrix);
        }
    });

    scene.addChild(redSphere);
}