#ifndef CG_FRAMEWORK_CORE_FACE_H
#define CG_FRAMEWORK_CORE_FACE_H

#include <iostream>

namespace CG {

    class Face3 {
    public:
        unsigned int a;
        unsigned int b;
        unsigned int c;
        
        Face3(unsigned int a, unsigned int b, unsigned int c) : a(a), b(b), c(c) {}

        Face3(const Face3 &other) : a(other.a), b(other.b), c(other.c) {}

        Face3& operator= (const Face3 &other){
            a = other.a;
            b = other.b;
            c = other.c;

            return *this;
        }

        friend std::ostream& operator<< (std::ostream &out, const Face3 &face);
    };

    std::ostream& operator<< (std::ostream &out, const Face3 &face){
        out << "[ a: " << face.a << ", b: " << face.b << ", c: " << face.c << " ]";

        return out;
    }

}

#endif