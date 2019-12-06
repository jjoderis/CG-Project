#ifndef MATHEMATICS_VECTOR_H
#define MATHEMATICS_VECTOR_H
#include <iostream>
#include <initializer_list>

namespace CG
{
    namespace LinAlg
    {
        //Workaround to make friend functions only with correct template class
        template <typename T, int size>
        class Vector;

        template <typename T, int size>
        std::ostream& operator<< (std::ostream &out, const Vector<T, size> &vector);

        template <typename T, int size>
        Vector<T, size> operator+(const Vector<T, size> &v1, const Vector<T, size> &v2);

        //A basic Vector class template for different types like int, float, etc, and different sizes size
        template <typename T, int size>
        class Vector
        {
        protected:
            T m_data[size]; //array of static size with vector elements

        public:
            //Constructor: creates vector
            Vector() : {}

            //Constructor: creates vector and initializes data with values from initializer list
            Vector(const std::initializer_list<T> &list)
            {
                assert(list.size() == size);

                int count = 0;
                for (const T &element : list)
                {
                    m_data[count] = element;
                    ++count;
                }
            }

            //Copy Constructor: creates a Vector as a copy of another vector
            Vector(const Vector &vector) {
                for(int i = 0; i < size; ++i){
                    m_data[i] = vector.m_data[i];
                }
            }

            //Delete assignment operation
            Vector<T, size>& operator= (const Vector<T, size> &vector) = delete;

            //overload typecast to T* to make vector decay to m_data if necessary
            operator T*() const{
                return m_data;
            }

            //overload subscript operator to access elements in m_data
            T& operator[] (int index){
                return m_data[index];
            }


            //overload + to return a new vector that is the sum of the two given vectors
            friend Vector<T, size> operator+<T, size> (const Vector<T, size> &v1, const Vector<T, size> &v2);

            //overload << to be able to write vector to console
            friend std::ostream& operator<<<T, size> (std::ostream &out, const Vector<T, size> &vector);
        };

        template <typename T, int size>
        Vector<T, size> operator+(const Vector<T, size> &v1, const Vector<T, size> &v2){
            
        }

        template <typename T, int size>
        std::ostream& operator<< (std::ostream &out, const Vector<T, size> &vector){
            out << "[ " << vector.m_data[0];

            for(int i = 1; i < size; ++i){
                out << ", " << vector.m_data[i];
            }

            out << " ]";
        }
    }
}

#endif