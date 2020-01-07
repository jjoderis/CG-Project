#include "camera.h"

CG::Camera::Camera(){
    lookAt(0.0, 0.0, -1.0);
    updateMatrixWorld();
    updateProjectionMatrix();
}

CG::Camera::Camera(GLfloat near, GLfloat far, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
    : Camera()
{
    m_near = near;
    m_far = far;
    m_left = left;
    m_right = right;
    m_bottom = bottom;
    m_top = top;
    updateProjectionMatrix();
}

CG::Camera::Camera(const Camera &other){
    m_projectionMatrix = other.m_projectionMatrix;
    updateMatrixWorld();
}

void CG::Camera::updateProjectionMatrix(){
    m_projectionMatrix = Matrix4{
        { 2*m_near/(m_right-m_left), 0.0, -((m_right+m_left)/(m_right-m_left)), 0.0},
        { 0.0, 2*m_near/(m_top-m_bottom), -((m_top+m_bottom)/(m_top-m_bottom)), 0.0},
        { 0.0, 0.0, ((m_far+m_near)/(m_far-m_near)), -((2*m_far*m_near)/(m_far*m_near))},
        { 0.0, 0.0, 1.0, 0.0 }
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