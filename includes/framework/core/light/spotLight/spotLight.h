#ifndef CG_FRAMEWORK_CORE_LIGHT_SPOTLIGHT_H
#define CG_FRAMEWORK_CORE_LIGHT_SPOTLIGHT_H

#include "../light.h"

namespace CG{
    class SpotLight: public Light{
    public:
        SpotLight(const Vector3 &position);

        SpotLight(const Vector3 &position, float cAttenuation, float lAttenuation, float qAttenuation);
    };
}

#endif