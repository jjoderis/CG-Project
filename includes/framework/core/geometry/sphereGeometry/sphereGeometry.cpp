#include "sphereGeometry.h"

CG::SphereGeometry::SphereGeometry(float radius, unsigned int widthSegs, unsigned int heightSegs) : m_radius{ radius }{
    widthSegs = (widthSegs > 4) ? widthSegs : 4;
    heightSegs = (heightSegs > 0) ? heightSegs : 1; 

    unsigned int numVertices = widthSegs * heightSegs + 2;
    unsigned int numFaces = 2 * widthSegs * heightSegs;

    m_vertices.resize(numVertices);
    m_vertNormals.resize(numVertices);
    m_vertUVs.resize(numVertices);
    m_faces.resize(numFaces);

    m_vertices[0] = Vector3{ 0.0, radius, 0.0 };
    m_vertNormals[0] = Vector3{ 0.0, 1.0, 0.0 };
    m_vertices[numVertices - 1] = Vector3{ 0.0, -radius, 0.0};
    m_vertNormals[numVertices - 1] = Vector3{ 0.0, -1.0, 0.0};

    for(unsigned int i = 0; i < heightSegs; ++i){
        float hFrac = (i + 1.0) / (heightSegs + 1.0);
        for(unsigned int j = 0; j < widthSegs; ++j){
            float wFrac = static_cast<float>(j) / widthSegs;
            float x = radius * sin(hFrac * M_PI) * sin(wFrac * 2 * M_PI);
            float y = radius * cos(hFrac * M_PI);
            float z = radius * sin(hFrac * M_PI) * cos(wFrac * 2 * M_PI);
            Vector3 vec{x, y, z};
            m_vertices[1 + i * widthSegs + j] = vec;
            m_vertNormals[1 + i * widthSegs + j] = vec.normalize();

            if(i == 0){
                m_faces[j] = Face{j+1, (j+1)%(widthSegs) + 1, 0};
            }

            //index of first vertex in current row
            int fRVI = 1 + i * widthSegs;
            if(i > 0){
                m_faces[widthSegs + 2 * (i - 1) * widthSegs + 2 * j] = Face{fRVI + j, fRVI + ((j + 1) % widthSegs), fRVI + j - widthSegs};
                m_faces[widthSegs + 2 * (i - 1) * widthSegs + 2 * j + 1] = Face{fRVI + ((j + 1) % widthSegs), fRVI + ((j + 1) % widthSegs) - widthSegs, fRVI + j - widthSegs};
            }

            if(i == heightSegs - 1){
                m_faces[numFaces - widthSegs + j] = Face{numVertices - 1, fRVI + ((j + 1) % widthSegs), fRVI + j};
            }
        }
    }

    for (unsigned int i = 0; i < numVertices; i++) {
        float u = (M_PI + atan2(m_vertices[i].at(1) - m_center.at(1), m_vertices[i].at(0) - m_center.at(0))) / (2 * M_PI);
        float v = atan2( sqrt( pow( m_vertices[i].at(0) - m_center.at(0) , 2 ) + pow( m_vertices[i].at(1) - m_center.at(1) , 2 ) ) , m_vertices[i].at(2) - m_center.at(2) ) / M_PI;
        m_vertUVs[i] = Vector2{u, v};
    }
    
    calculateFaceNormals();
    calculateVertexNormals();
}

float CG::SphereGeometry::getRadius(){
    return m_radius;
}