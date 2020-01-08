#include "camera.h"

CG::Camera::Camera(){
    lookAt(0.0, 0.0, -1.0);
    updateMatrixWorld();
    updateProjectionMatrix();
}

CG::Camera::Camera(GLfloat near, GLfloat far, GLfloat fov, GLfloat aspectRatio)
    : Camera()
{
    m_near = near;
    m_far = far;
    m_fov = fov;
    m_aspectRatio = aspectRatio;
    updateProjectionMatrix();
}

CG::Camera::Camera(const Camera &other) 
    : Object3D(other), m_near{ other.m_near }, m_far{ other.m_far }, m_fov{ other.m_fov }, m_aspectRatio{ other.m_aspectRatio }
{
    m_projectionMatrix = other.m_projectionMatrix;
    updateMatrixWorld();
}

void CG::Camera::updateProjectionMatrix(){
    GLfloat c{ 1.0f/tan(m_fov/2) };
    m_projectionMatrix = Matrix4{
        { c/m_aspectRatio, 0.0, 0.0, 0.0},
        { 0.0, c, 0.0, 0.0},
        { 0.0, 0.0, -((m_far+m_near)/(m_far-m_near)), -((2*m_far*m_near)/(m_far*m_near))},
        { 0.0, 0.0, -1.0, 0.0 }
    };
}

void CG::Camera::lookAt(CG::Vector3 position){
    Vector3 worldPosition{dot(m_worldMatrix, Vector4{m_position, 1.0})};
    Vector3 view{(worldPosition - position).normalize()};

    Vector3 upWorld{dot(m_worldMatrix, Vector4{ 0.0, 1.0, 0.0, 1.0 })};

    Vector3 right{-(cross(view, upWorld).normalize())};

    upWorld = cross(view, right);

    Matrix4 baseChange{
        { right.at(0), right.at(1), right.at(2), 0.0 },
        { upWorld.at(0), upWorld.at(1), upWorld.at(2), 0.0 },
        { view.at(0), view.at(1), view.at(2), 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };

    GLfloat qw = 0.5f * sqrt(baseChange.trace());
    GLfloat qx = (baseChange.at(2, 1) - baseChange.at(1, 2)) / (4.0f * qw);
    GLfloat qy = (baseChange.at(0, 2) - baseChange.at(2, 0)) / (4.0f * qw);
    GLfloat qz = (baseChange.at(1, 0) - baseChange.at(0, 1)) / (4.0f * qw);

    m_rotation = CG::Quaternion{ qx, qy, qz, qw };

    updateMatrixWorld();
}

void CG::Camera::lookAt(float x, float y, float z){
    lookAt(Vector3{x, y, z});
}

void CG::Camera::setNear(GLfloat near){
    m_near = near;
}
void CG::Camera::setFar(GLfloat far){
    m_far = far;
}
void CG::Camera::setFOV(GLfloat fov){
    m_fov = fov;
}
void CG::Camera::setAspectRatio(GLfloat aspectRatio){
    m_aspectRatio = aspectRatio;
}

GLfloat CG::Camera::getNear(){
    return m_near;
}
GLfloat CG::Camera::getFar(){
    return m_far;
}
GLfloat CG::Camera::getFOV(){
    return m_fov;
}
GLfloat CG::Camera::getAspectRatio(){
    return m_aspectRatio;
}

const CG::Matrix4& CG::Camera::getProjectionMatrix() const{
    return m_projectionMatrix;
}