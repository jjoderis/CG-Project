#ifndef MATHEMATICS_UTIL_H
#define MATHEMATICS_UTIL_H
#include <cmath>


namespace CG
{
    namespace Util
    {
        //function for comparing floating point numbers
        //as seen here: https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/
        // return true if the difference between a and b is less than absEpsilon, or within relEpsilon percent of the larger of a and b
        bool isClose(double a, double b, double absEpsilon, double relEpsilon)
        {
            // Check if the numbers are really close -- needed when comparing numbers near zero.
            double diff{ std::abs(a - b) };
            if (diff <= absEpsilon)
                return true;
        
            // Otherwise fall back to Knuth's algorithm
            return (diff <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
        }
    }
}

#endif