#ifndef MATHEMATICS_MATRIX_H
#define MATHEMATICS_MATRIX_H
#include <iostream>
#include <initializer_list>
#include <cassert>
#include <math.h>
#include <util/util.h>

namespace CG
{
    namespace LinAlg
    {
        template <typename T, int rows, int cols>
        class Matrix
        {
        protected:
            T m_data[rows*cols]; //array with all matrix elements in column major order

        public:
            //Constructor: creates matrix but doesn't initialize any values
            Matrix() {}

            //Constructor: creates Matrix and initializes with values from initializer lists
            Matrix(const std::initializer_list<std::initializer_list<T>> &list){

                assert(list.size() == rows);

                int i = 0;
                for(const std::initializer_list<T> &subList : list){
                    assert(subList.size() == cols);

                    int j = 0;
                    for(const T &element : subList){
                        m_data[j*rows+i] = element;
                        ++j;
                    }
                    ++i;
                }
            }

            operator T*(){
                return m_data;
            }
        };
    }
}

#endif