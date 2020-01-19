#ifndef CG_EXMAPLES_ANIMATIONS_BOUNCE_AROUND_H
#define CG_EXMAPLES_ANIMATIONS_BOUNCE_AROUND_H

#include <core/object3D/object3D.h>
#include <memory>
#include <OpenGL/geometry/sphereGeometry/OpenGLSphereGeometry.h>
#include <OpenGL/mesh/OpenGLMesh.h>

void bounceAround(CG::Object3D &obj) {
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
}

#endif