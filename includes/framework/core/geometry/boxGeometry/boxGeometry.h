#ifndef CG_FRAMEWORK_CORE_GEOMETRY_BOXGEOMETRY_BOXGEOMETRY_H
#define CG_FRAMEWORK_CORE_GEOMETRY_BOXGEOMETRY_BOXGEOMETRY_H

#include <geometry/geometry.h>

namespace CG{

    class BoxGeometry : virtual public CG::Geometry{
    protected:
        Vector3 m_bottomLeft{ -0.5, -0.5, 0.5 };
        Vector3 m_topRight{ 0.5, 0.5, -0.5 };

    public:
        BoxGeometry();

        BoxGeometry(float width, float height, float depth);

        float getWidth();
        float getHeigth();
        float getDepth();
    };

}


#endif