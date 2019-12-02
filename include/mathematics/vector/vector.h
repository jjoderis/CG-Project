#ifndef MATHEMATICS_VECTOR_H
#define MATHEMATICS_VECTOR_H

namespace Mathematics
{
   template <typename T>
   class Vector
   {
    protected:
        int m_size;
        T* m_data;

    public:
        Vector(int size) : m_size{size}, m_data{ new T[size] } {}

        ~Vector(){
            delete [] m_data;
        }
   } ;
}

#endif