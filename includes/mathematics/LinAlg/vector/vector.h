#ifndef MATHEMATICS_VECTOR_H
#define MATHEMATICS_VECTOR_H
#include <iostream>
#include <initializer_list>
#include <cassert>
#include <math.h>
#include <util/util.h>
#include <vector>

namespace LinAlg
{
    //A basic Vector class template for different types like int, float, etc, and different sizes size
    template <typename T, int size>
    class Vector
    {
    protected:
        std::vector<T> m_data;

    public:
        friend class Vector<T, size + 1>;
        friend class Vector<T, size - 1>;

        //Constructor: creates vector
        Vector() 
        {
            m_data.resize(size);
        }

        //Constructor: creates vector and initializes data with values from initializer list
        Vector(const std::initializer_list<T> &list)
        {
            assert(list.size() == size);

            m_data = list;
        }

        //Copy Constructor: creates a Vector as a copy of another vector
        Vector(const Vector &vector) : Vector() 
        {
            for(int i = 0; i < size; ++i){
                m_data[i] = vector.m_data[i];
            }
        }

        //create vector from a vector with one entry less and a given value
        Vector(const Vector<T, size-1> &vector, T val) : Vector()
        {

            for(int i = 0; i < size - 1; ++i){
                m_data[i] = vector.m_data[i];
            }
            m_data[size-1] = val;
        }

        //create vector from a vector with one entry more
        Vector(const Vector<T, size+1> &vector) : Vector()
        {
            for(int i = 0; i < size; ++i){
                m_data[i] = vector.m_data[i];
            }
        }

        //destructor: free dynamic allocated memory
        ~Vector() {}

        Vector<T, size>& operator= (const Vector<T, size> &vector){

            for(int i = 0; i < size; ++i){
                m_data[i] = vector.m_data[i];
            }

            return *this;
        };

        //returns the length of the given vector
        double length() const{
            return sqrt(this->dot(*this));
        }

        //return pointer to data of internal vector
        T* data(){
            return m_data.data();
        }

        const T* data() const{
            return m_data.data();
        }     

        //return value at index by reference
        T& at (int index){
            return m_data[index];
        }

        //return value at reference by value; used for const vector in dot function
        const T& at(int index) const{
            return m_data[index];
        }

        //sets value at index to val
        void set(int index, T val){
            m_data[index] = val;
        }

        //overload += to add the other vector to this one and return reference to this vector
        Vector<T, size>& operator+= (const Vector<T, size> &other){

            for(int i = 0; i < size; ++i){
                m_data[i] += other.m_data[i];
            }

            return *this;
        }

        //overload += to add a value to every entry of the vector
        Vector<T, size>& operator+= (T val){

            for(int i = 0; i < size; ++i){
                m_data[i] += val;
            }

            return *this;
        }

        //overload -= to subtract the other vector from this one and return reference to this vector
        Vector<T, size>& operator-= (const Vector<T, size> &other){

            for(int i = 0; i < size; ++i){
                m_data[i] -= other.m_data[i];
            }

            return *this;
        }

        //overload -= to subtract a value from every entry of the vector
        Vector<T, size>& operator-= (T val){

            for(int i = 0; i < size; ++i){
                m_data[i] -= val;
            }

            return *this;
        }

        //overload unary - operator to return inverse of given vector
        Vector<T, size> operator- () const{
            Vector<T, size> newVec{ *this };

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] *= -1;
            }

            return newVec;    
        }

        //overload * set this vector to result of element wise multiplication with given vector and return reference to it
        Vector<T, size>& operator*= (const Vector<T, size> &other){

            for(int i = 0; i < size; ++i){
                m_data[i] *= other.m_data[i];
            }

            return *this;
        } 

        //overload *= to multiply every entry of the vector with a given value
        Vector<T, size>& operator*= (T val){

            for(int i = 0; i < size; ++i){
                m_data[i] *= val;
            }

            return *this;
        }

        //overload / set this vector to result of element wise division with given vector and return reference to it
        Vector<T, size>& operator/= (const Vector<T, size> &other){

            for(int i = 0; i < size; ++i){
                m_data[i] /= other.m_data[i];
            }

            return *this;
        } 

        //overload /= to divide every entry of the vector by a given value
        Vector<T, size>& operator/= (T val){

            for(int i = 0; i < size; ++i){
                m_data[i] /= val;
            }

            return *this;
        }

        //returns the dot product between this vector and the given vector
        double dot(const Vector<T, size> &other) const{
            double sum = 0.0;
            
            for(int i = 0; i < size; ++i){
                sum += m_data[i] * other.m_data[i];
            }

            return sum;
        }

        //normalize the vector so it has a length of 1
        Vector<T, size>& normalize(){
            *this /= this->length();

            return *this;
        }

        //returns the angle between this and the other vector
        double angleTo(const Vector<T, size> &other) const{
            return acos(this->dot(other)/(this->length()*other.length()));
        }

        Vector<T, size> reflect(const Vector<T, size> &normal) const{
            return *this - 2 * ((T)this->dot(normal)) * normal; 
        }

        //compares two vectors taking possible rounding errors into account
        bool allClose(const Vector<T, size> &other) const{

            for(int i = 0; i < size; ++i){
                if(!CG::Util::isClose(m_data[i], other.m_data[i], 1E-10, 1E-6)){
                    return false;
                }
            }

            return true;
        }
    };

    template <typename T, int size>
    Vector<T, size> operator+(const Vector<T, size> &v1, const Vector<T, size> &v2){
        Vector<T, size> newVec;

        for(int i = 0; i < size; ++i){
            newVec.set(i, v1.at(i) + v2.at(i));
        }     

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator+ (const Vector<T, size> &vec, T val){
        Vector<T, size> newVec{ vec };

        newVec += val;

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator+ (T val, const Vector<T, size> &vec){
        Vector<T, size> newVec{ vec };

        newVec += val;

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator-(const Vector<T, size> &v1, const Vector<T, size> &v2){
        Vector<T, size> newVec;

        for(int i = 0; i < size; ++i){
            newVec.at(i) = v1.at(i) - v2.at(i);
        }     

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator- (const Vector<T, size> &vec, T val){
        Vector<T, size> newVec{ vec };

        newVec -= val;

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator- (T val, const Vector<T, size> &vec){
        Vector<T, size> newVec;

        for(int i = 0; i < size; ++i){
            newVec.at(i) = val - vec.at(i);
        }

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator*(const Vector<T, size> &v1, const Vector<T, size> &v2){
        Vector<T, size> newVec;

        for(int i = 0; i < size; ++i){
            newVec.at(i) = v1.at(i) * v2.at(i);
        }     

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator* (const Vector<T, size> &vec, T val){
        Vector<T, size> newVec{ vec };

        newVec *= val;

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator* (T val, const Vector<T, size> &vec){
        Vector<T, size> newVec{ vec };

        newVec *= val;

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator/(const Vector<T, size> &v1, const Vector<T, size> &v2){
        Vector<T, size> newVec;

        for(int i = 0; i < size; ++i){
            newVec.at(i) = v1.at(i) / v2.at(i);
        }     

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator/ (const Vector<T, size> &vec, T val){
        Vector<T, size> newVec{ vec };

        newVec /= val;

        return newVec;
    }

    template <typename T, int size>
    Vector<T, size> operator/ (T val, const Vector<T, size> &vec){
        Vector<T, size> newVec;

        for(int i = 0; i < size; ++i){
            newVec.at(i) = val / vec.at(i);
        }

        return newVec;
    }

    template<typename T, int size>
    Vector<T, size> normalize(const Vector<T, size> &vec){
        return Vector<T, size>{vec} / (float)vec.length();
    }

    template<typename T, int size>
    Vector<T, size> orthogonalProject(const Vector<T, size> &v1, const Vector<T, size> &v2){
        double t = (v1.dot(v2))/(v2.dot(v2));

        Vector<T, size> newVec{ v2 };

        for(int i = 0; i < size; ++i){
            newVec.at(i) *= t;
        }

        return newVec;
    }

    template<typename T, int size>
    double dot(const Vector<T, size> &v1, const Vector<T, size> &v2){
        double sum = 0.0;
        
        for(int i = 0; i < size; ++i){
            sum += v1.at(i) * v2.at(i);
        }

        return sum;
    }

    template<typename T>
    Vector<T, 3> cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2){
        Vector<T, 3> newVec;

        newVec.at(0) = v1.at(1) * v2.at(2) - v1.at(2) * v2.at(1);
        newVec.at(1) = v1.at(2) * v2.at(0) - v1.at(0) * v2.at(2);
        newVec.at(2) = v1.at(0) * v2.at(1) - v1.at(1) * v2.at(0);

        return newVec;
    }

    template<typename T, int size>
    bool operator== (const Vector<T, size> &vec1, const Vector<T, size> &vec2){
        
        for(int i = 0; i < size; ++i){
            if(vec1.at(i) != vec2.at(i)){
                return false;
            }
        }

        return true;
    }

    template<typename T, int size>
    bool operator!= (const Vector<T, size> &vec1, const Vector<T, size> &vec2){
        return !(vec1 == vec2);
    }

    template <typename T, int size>
    std::ostream& operator<< (std::ostream &out, const Vector<T, size> &vector){
        out << "[ " << vector.at(0);

        for(int i = 1; i < size; ++i){
            out << ", " << vector.at(i);
        }

        out << " ]";

        return out;
    }
}

#endif