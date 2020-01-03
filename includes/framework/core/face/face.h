#ifndef CG_FRAMEWORK_CORE_FACE_FACE_H
#define CG_FRAMEWORK_CORE_FACE_FACE_H

#include <iostream>

namespace CG {
    //A face denotes the indices of a triangle that are supposed to form a polygon
    class Face3 {
    public:
        unsigned int a;
        unsigned int b;
        unsigned int c;

        Face3() {}
        
        Face3(unsigned int a, unsigned int b, unsigned int c);

        Face3(const Face3 &other);

        Face3& operator= (const Face3 &other);

        friend bool operator== (const Face3 &f1, const Face3 &f2);

        friend std::ostream& operator<< (std::ostream &out, const Face3 &face);
    };

    bool operator== (const Face3 &f1, const Face3 &f2);

    std::ostream& operator<< (std::ostream &out, const Face3 &face);
}

#endif