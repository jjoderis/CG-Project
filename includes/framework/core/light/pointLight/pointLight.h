#ifndef CG_FRAMEWORK_CORE_LIGHT_POINTLIGHT_H
#define CG_FRAMEWORK_CORE_LIGHT_POINTLIGHT_H

#include "../light.h"

namespace CG{
    class PointLight: public Light{
    public:
        PointLight(const Vector3 &position);

        PointLight(const Vector3 &position, float cAttenuation, float lAttenuation, float qAttenuation);
    };
}

#endif