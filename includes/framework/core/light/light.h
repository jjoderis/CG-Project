#ifndef CG_FRAMEWORK_CORE_LIGHT_H
#define CG_FRAMEWORK_CORE_LIGHT_H

#include <object3D/object3D.h>
#include <color/color.h>

namespace CG{
    // a basic light class usable for different kinds of light; default point light
    class Light : public Object3D{
    protected:
        bool m_isEnabled{ true };
        bool m_isLocal{ true };

        bool m_isSpot{ false };
        CG::Vector4 m_ambient{ 0.1, 0.1, 0.1, 1.0 };
        CG::RGBA_Color m_color{ 1.0, 1.0, 1.0, 1.0 };

        CG::Vector4 m_halfVector{ 0.0, 0.0, 0.0, 1.0 };
        CG::Vector4 m_coneDirection{ 0.0, 0.0, -1.0, 1.0 };
        float m_spotCosCutoff{ 0.0 };
        float m_spotExponent{ 1.0 };

        float m_constantAttenuation{ 1.0 };
        float m_linearAttenuation{ 1.0 };
        float m_quadraticAttenuation{ 1.0 };

        Light();

        Light(const Light &other);

        Light& operator= (const Light &other);

    public:
        void enable();
        void disable();
        void setColor(const CG::RGBA_Color &color);
        CG::RGBA_Color getColor() const;

        void setConstantAttenuation(float attenuation);
        void setLinearAttenuation(float attenuation);
        void setQuadraticAttenuation(float attenuation);

        bool isEnabled() const;
        bool& isLocal();
        bool& isSpot();
        CG::Vector4& ambient();
        CG::RGBA_Color& color();
        CG::Vector4& halfVector();
        CG::Vector4& coneDirection();
        float& spotCosCutoff();
        float& spotExponent();
        float& constantAttenuation();
        float& linearAttenuation();
        float& quadraticAttenuation();
    };
}

#endif