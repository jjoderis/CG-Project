include_directories(
    .
    ../mathematics
    ../../glew
)

add_library(CG_Framework
    ./math/math.cpp
    ./math/quaternion/quaternion.cpp
    core/face/face.cpp
    core/geometry/geometry.cpp
    core/shader/shader.cpp
    core/material/material.cpp
    core/object3D/object3D.cpp
    core/Mesh/mesh.cpp
    core/scene/scene.cpp
    core/camera/camera.cpp
    core/renderer/renderer.cpp
    core/geometry/sphereGeometry/sphereGeometry.cpp
)

set(TEST_FILES
    ${TEST_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/core/face/test/faceTest.cpp
    PARENT_SCOPE
)