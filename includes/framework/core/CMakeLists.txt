include_directories(
    .
    ../..
    ../../mathematics
)

add_library(CG_Framework_Core
    camera/camera.cpp
    face/face.cpp
    geometry/geometry.cpp
    geometry/boxGeometry/boxGeometry.cpp
    geometry/sphereGeometry/sphereGeometry.cpp
    ./math/math.cpp
    ./math/quaternion/quaternion.cpp
    material/material.cpp
    mesh/baseMesh.cpp
    object3D/object3D.cpp
    scene/baseScene.cpp
)

set(TEST_FILES
    ${TEST_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/geometry/test/geometryTest.cpp
    PARENT_SCOPE
)