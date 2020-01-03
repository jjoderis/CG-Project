include_directories(
    .
    ../mathematics
    ../../glew
)

add_library(CG_Framework
    core/face/face.cpp
    core/geometry/geometry.cpp
    core/shader/shader.cpp
    core/material/material.cpp
    core/object3D/object3D.cpp
    core/Mesh/mesh.cpp
)