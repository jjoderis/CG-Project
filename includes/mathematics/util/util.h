#ifndef MATHEMATICS_UTIL_H
#define MATHEMATICS_UTIL_H

namespace CG
{
    namespace Util
    {
        //function for comparing floating point numbers
        //as seen here: https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/
        // return true if the difference between a and b is less than absEpsilon, or within relEpsilon percent of the larger of a and b
        bool isClose(double a, double b, double absEpsilon, double relEpsilon);
        
    }
}

#endif