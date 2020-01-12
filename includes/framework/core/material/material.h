#ifndef CG_FRAMEWORK_CORE_MATERIAL_MATERIAL_H
#define CG_FRAMEWORK_CORE_MATERIAL_MATERIAL_H

#include <core/color/color.h>

namespace CG{
    //A class that handles different parameters used for rendering
    class Material{
    protected:
        //a base color
        CG::RGBA_Color m_color{ 1.0, 1.0, 1.0, 1.0 };

        //used in e.g. phong shader to calculate specularity
        float m_shininess{ 30 };

    public:
        //creates a material with a basic shader that only renders triangles with the stored color
        Material();

        //creates a Material and sets a color
        Material(RGBA_Color color);

        //creates a Material and sets a color
        Material(RGB_Color color);

        //Copy constructor: copies the color and deep copies the shader information; doesn't copy the program name
        Material(const Material &other);

        //copies the color and deep copies the shader information; doesn't copy the program name
        Material& operator= (const Material &other);

        //delete all shaders and the program of the program
        virtual ~Material();

        //sets new color
        void setColor(RGB_Color color);
        void setColor(float r, float g, float b);
        void setColor(RGBA_Color color);
        void setColor(float r, float g, float b, float a);
        RGBA_Color& getColor();

        void setShininess(float dullness);
        float getShininess();
    };
}

#endif