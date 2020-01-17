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


void setUp(CG::Scene &scene, CG::Camera &camera, CG::Renderer &renderer){
    (void)camera;
    (void)renderer;

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

    scene.addChild(redSphere);
    scene.addChild(yellowCube);

    setUpRenderer(renderer);
}

void setUpRenderer(CG::Renderer &renderer){
    // (void)renderer;

    renderer.setRenderFunction([](CG::Renderer &renderer, CG::Scene &scene, CG::Camera &camera){
        (void)renderer;
        (void)scene;
        (void)camera;

        std::cout << "Test\n";
    });
}