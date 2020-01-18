#include <cstring>
#include <fstream>
#include <string>
#include <cerrno>

#include <core/scene/scene.h>
#include <core/mesh/mesh.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>
#include <OpenGL/material/OpenGLMaterial.h>
#include <OpenGL/geometry/sphereGeometry/OpenGLSphereGeometry.h>
#include <OpenGL/geometry/boxGeometry/OpenGLBoxGeometry.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

void renderMesh(CG::Mesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 &projectionMatrix){
    std::shared_ptr<CG::OpenGLMaterial> material{ std::dynamic_pointer_cast<CG::OpenGLMaterial>(mesh->getMaterial()) };
    std::shared_ptr<CG::OpenGLGeometry> geometry{ std::dynamic_pointer_cast<CG::OpenGLGeometry>(mesh->getGeometry()) }; 

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
    if(geometry->getNumFaces()){
        glDrawElements(material->getDrawMode(), 3 * geometry->getNumFaces(), GL_UNSIGNED_INT, NULL);
    }else{
        glDrawArrays(material->getDrawMode(), 0, geometry->getNumVertices());
    }

    for(const std::shared_ptr<CG::Mesh> &child : mesh->getChildren()){
        renderMesh(child.get(), viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}

// source: http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
std::string readTextFile(const char* filePath){
  std::ifstream in(filePath, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

void setUpRenderer(CG::Renderer &renderer);

void setUpSphere(CG::Scene &scene){
    std::shared_ptr<CG::OpenGLSphereGeometry> geoPtr = std::make_shared<CG::OpenGLSphereGeometry>(CG::OpenGLSphereGeometry{1.0, 30, 30});
  
    std::shared_ptr<CG::OpenGLMaterial> redPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{
        readTextFile("../media/shaders/phongShader/phong.vert"),
        readTextFile("../media/shaders/phongShader/phong.frag")
    });

    redPtr->setColor(1.0, 0.0, 0.0);
    redPtr->setShininess(120.0);

    std::shared_ptr<CG::Mesh> redSphere(new CG::Mesh{geoPtr, redPtr});

    void (*animation)(CG::Object3D&) = [](CG::Object3D &obj) {
        float radius{ std::dynamic_pointer_cast<CG::SphereGeometry>(dynamic_cast<CG::Mesh&>(obj).getGeometry())->getRadius() };
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
    redSphere->setRenderFunction(renderMesh);

    scene.addChild(redSphere);
}

void setUpBox(CG::Scene &scene){
    std::shared_ptr<CG::OpenGLGeometry> boxPtr = std::make_shared<CG::OpenGLGeometry>(CG::OpenGLGeometry{
        {
            { -5.0, -5.0, 5.0 },
            {  5.0, -5.0, 5.0 },
            { -5.0, -5.0, 5.0 },
            { -5.0,  5.0, 5.0 },
            {  5.0, -5.0, 5.0 },
            {  5.0,  5.0, 5.0 },
            { -5.0,  5.0, 5.0 },
            {  5.0,  5.0, 5.0 },
            
            { -5.0, -5.0, -5.0 },
            {  5.0, -5.0, -5.0 },
            { -5.0, -5.0, -5.0 },
            { -5.0,  5.0, -5.0 },
            {  5.0, -5.0, -5.0 },
            {  5.0,  5.0, -5.0 },
            { -5.0,  5.0, -5.0 },
            {  5.0,  5.0, -5.0 },

            { -5.0, -5.0, -5.0 },
            { -5.0, -5.0,  5.0 },
            {  5.0, -5.0, -5.0 },
            {  5.0, -5.0,  5.0 },
            { -5.0,  5.0, -5.0 },
            { -5.0,  5.0,  5.0 },
            {  5.0,  5.0, -5.0 },
            {  5.0,  5.0,  5.0 }
        },
        {}
    });
    std::shared_ptr<CG::OpenGLMaterial> yellowPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{CG::RGBA_Color{1.0, 1.0, 0.0, 1.0}});
    std::shared_ptr<CG::Mesh> yellowCube{new CG::Mesh{boxPtr, yellowPtr}};

    yellowPtr->setDrawMode(GL_LINES);
    yellowCube->setRenderFunction(renderMesh);

    scene.addChild(yellowCube);
}

void setUpParticles(CG::Scene &scene){
    CG::OpenGLGeometry particles{
        {
            { 1.0, 0.0, 1.0 },
            { -1.0, 0.0, 1.0 },
            { 1.0, 0.0, -1.0 },
            { -1.0, 0.0, -1.0 },
            { 0.8, 0.0, 1.0 },
            { 1.0, 0.0, 0.8 },
        },
        {}
    };

    CG::OpenGLMaterial redMat{CG::RGBA_Color{ 1.0, 0.0, 0.0, 1.0 }};
    redMat.setDrawMode(GL_POINTS);

    CG::Mesh part1{particles, redMat};
    CG::Mesh part2{particles, redMat};

    part1.setRenderFunction(renderMesh);
    part2.setRenderFunction(renderMesh);

    scene.addParticles(std::make_shared<CG::Mesh>(part1));
    scene.addParticles(std::make_shared<CG::Mesh>(part2));
}


void setUp(CG::Scene &scene, CG::Camera &camera, CG::Renderer &renderer){
    (void)camera;
    (void)renderer;

    setUpSphere(scene);
    setUpBox(scene);
    setUpParticles(scene);

    setUpRenderer(renderer);
}

void setUpRenderer(CG::Renderer &renderer){
    
    renderer.setRenderFunction([](CG::Renderer &renderer, CG::Scene &scene, CG::Camera &camera){
        (void)renderer;

        glClearBufferfv(GL_COLOR, 0, scene.getBackground().data());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        CG::Matrix4 viewMatrix = camera.getMatrixWorldInverse();
        CG::Matrix4 viewMatrixInverse = camera.getMatrixWorld();
        CG::Matrix4 projectionMatrix = camera.getProjectionMatrix();

        for(const std::shared_ptr<CG::Mesh> &mesh : scene.getChildren()){

            if(mesh->isAnimated){
                mesh->animate();
            }

            mesh->render(viewMatrix, viewMatrixInverse, projectionMatrix);
        }
    });

}