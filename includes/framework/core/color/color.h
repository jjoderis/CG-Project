#ifndef CG_FRAMEWORK_CORE_COLOR_COLOR_H
#define CG_FRAMEWORK_CORE_COLOR_COLOR_H

#include <LinAlg/vector/vector.h>

namespace CG{
    //Creating typedefs to use vectors as the basis for colors in our application
    using RGB_Color = LinAlg::Vector<float, 3>;
    using RGBA_Color = LinAlg::Vector<float, 4>;
}

#endif