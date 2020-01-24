#ifndef CG_FRAMEWORK_CORE_FACE_FACE_H
#define CG_FRAMEWORK_CORE_FACE_FACE_H

#include <iostream>
#include <vector>

namespace CG {
    //TODO find suitable name since a "face" that is just a line makes no sense

    //A face denotes the indices of a triangle or quad that are supposed to form a polygon
    class Face {
        std::vector<unsigned int> m_indices;
    public:

        Face();
        
        Face(unsigned int a, unsigned int b);

        Face(unsigned int a, unsigned int b, unsigned int c);

        Face(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

        Face(const Face &other);

        int getNumIndices() const;

        unsigned int& at(int index);

        Face& operator= (const Face &other);

        friend bool operator== (const Face &f1, const Face &f2);

        friend std::ostream& operator<< (std::ostream &out, const Face &face);
    };

    bool operator== (const Face &f1, const Face &f2);

    std::ostream& operator<< (std::ostream &out, const Face &face);
}

#endif