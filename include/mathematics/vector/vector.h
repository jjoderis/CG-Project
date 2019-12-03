#ifndef MATHEMATICS_VECTOR_H
#define MATHEMATICS_VECTOR_H
#include <iostream>
#include <initializer_list>

namespace Mathematics
{
   //A basic Vector class template for different types like int, float, etc
   template <typename T>
   class Vector
   {
    protected:
        int m_size; //number of elements in the vector
        T* m_data = nullptr; //array with vector elements

    public:
        //Constructor: creates vector, creates array with given size but doesn't initialize values
        Vector(int size) : m_size{size}, m_data{ new T[size] } {}

        Vector(const std::initializer_list<T> &list)
            : Vector<T>(static_cast<int>(list.size()))
        {
            int count = 0;
            for (const T &element : list)
            {
                m_data[count] = element;
                ++count;
            }
        }

        //Copy Constructor: creates a Vector as a copy of another vector
        Vector(const Vector &vector) : m_size{ vector.m_size }, m_data{ new T[vector.m_size] } {
            for(int i = 0; i < m_size; ++i){
                m_data[i] = vector.m_data[i];
            }
        }

        //Delete assignment operation
        Vector<T>& operator= (const Vector<T> &vector) = delete;

        //free data on object destruction
        virtual ~Vector(){
            delete [] m_data;
        }

        //return the number of elements of the vector
        int size() const{
            return m_size;
        }

        //overload typecast to T* to make vector decay to m_data if necessary
        operator T*() const{
            return m_data;
        }

        //overload subscript operator to access elements in m_data
        T& operator[] (int index){
            return m_data[index];
        }

        //overload << to be able to write vector to console
        template <typename U>
        friend std::ostream& operator<< (std::ostream &out, const Vector<U> &vector);
    };

    template <typename T>
    std::ostream& operator<< (std::ostream &out, const Vector<T> &vector){
        out << "[ " << vector.m_data[0];

        for(int i = 1; i < vector.m_size; ++i){
            out << ", " << vector.m_data[i];
        }

        out << " ]";
    }
}

#endif