#ifndef CG_FRAMEWORK_CORE_GEOMETRY_SPHEREGEOMETRY_SPHEREGEOMETRY_H
#define CG_FRAMEWORK_CORE_GEOMETRY_SPHEREGEOMETRY_SPHEREGEOMETRY_H

#include <core/geometry/geometry.h>

namespace CG{
    // a special geometry in form of a sphere; might be useful when using sphere specific intersection alogrithms etc. vs a undefined geometry
    class SphereGeometry : virtual public Geometry{
    protected:
        float m_radius{ 1.0f };

    public:
        SphereGeometry(float radius, unsigned int widthSegs, unsigned int heightSegs);
    };

}



#endif