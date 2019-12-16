#ifndef MATHEMATICS_VECTOR_H
#define MATHEMATICS_VECTOR_H
#include <iostream>
#include <initializer_list>
#include <cassert>
#include <math.h>
#include <util/util.h>

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
        bool operator== (const Vector<T, size> &vec1, const Vector<T, size> &vec2);

        template <typename T, int size>
        bool operator!= (const Vector<T, size> &vec1, const Vector<T,size> &vec2);

        template <typename T, int size>
        Vector<T, size> operator+(const Vector<T, size> &v1, const Vector<T, size> &v2);

        template <typename T, int size>
        Vector<T, size> operator+(const Vector<T, size> &vec, T val);   

        template <typename T, int size>
        Vector<T, size> operator+(T val, const Vector<T, size> &vec);   

        template <typename T, int size>
        Vector<T, size> operator-(const Vector<T, size> &v1, const Vector<T, size> &v2);

        template <typename T, int size>
        Vector<T, size> operator-(const Vector<T, size> &vec, T val);   

        template <typename T, int size>
        Vector<T, size> operator-(T val, const Vector<T, size> &vec);

        template <typename T, int size>
        Vector<T, size> operator*(const Vector<T, size> &v1, const Vector<T, size> &v2);

        template <typename T, int size>
        Vector<T, size> operator*(const Vector<T, size> &vec, T val);   

        template <typename T, int size>
        Vector<T, size> operator*(T val, const Vector<T, size> &vec);

        template <typename T, int size>
        Vector<T, size> operator/(const Vector<T, size> &v1, const Vector<T, size> &v2);

        template <typename T, int size>
        Vector<T, size> operator/(const Vector<T, size> &vec, T val);   

        template <typename T, int size>
        Vector<T, size> operator/(T val, const Vector<T, size> &vec); 

        template<typename T, int size>
        Vector<T, size> orthogonalProject(const Vector<T, size> &v1, const Vector<T, size> &v2);

        template<typename T>
        Vector<T, 3> cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2);        

        //A basic Vector class template for different types like int, float, etc, and different sizes size
        template <typename T, int size>
        class Vector
        {
        protected:
            T m_data[size]; //array of static size with vector elements

        public:
            friend class Vector<T, size + 1>;

            //Constructor: creates vector
            Vector(){}

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

            //create vector from a vector with one entry less and a given value
            Vector(const Vector<T, size-1> &vector, T val) {

                for(int i = 0; i < size - 1; ++i){
                    m_data[i] = vector.m_data[i];
                }
                m_data[size-1] = val;
            }

            //Delete assignment operation
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

            //overload typecast to T* to make vector decay to m_data if necessary
            operator T*(){
                return m_data;
            }

            //overload subscript operator to access elements in m_data
            T& at (int index){
                return m_data[index];
            }


            //overload + to return a new vector that is the sum of the two given vectors
            friend Vector<T, size> operator+<T, size> (const Vector<T, size> &v1, const Vector<T, size> &v2);

            //overload += to add the other vector to this one and return reference to this vector
            Vector<T, size>& operator+= (const Vector<T, size> &other){

                for(int i = 0; i < size; ++i){
                    m_data[i] += other.m_data[i];
                }

                return *this;
            }

            //overload + to add the given value to all entries of the given vector and return new vector by value
            friend Vector<T, size> operator+<T, size> (const Vector<T, size> &vec, T val);
            friend Vector<T, size> operator+<T, size> (T val, const Vector<T, size> &vec);

            //overload += to add a value to every entry of the vector
            Vector<T, size>& operator+= (T val){

                for(int i = 0; i < size; ++i){
                    m_data[i] += val;
                }

                return *this;
            }

            //overload - to return a new vector that is the difference of the two given vectors
            friend Vector<T, size> operator-<T, size> (const Vector<T, size> &v1, const Vector<T, size> &v2);

            //overload -= to subtract the other vector from this one and return reference to this vector
            Vector<T, size>& operator-= (const Vector<T, size> &other){

                for(int i = 0; i < size; ++i){
                    m_data[i] -= other.m_data[i];
                }

                return *this;
            }

            //overload - to subtract the given value from all entries of the given vector and return new vector by value
            friend Vector<T, size> operator-<T, size> (const Vector<T, size> &vec, T val);
            //overload - to return a new vector that is equal to difference of the given value and each vector entry
            friend Vector<T, size> operator-<T, size> (T val, const Vector<T, size> &vec);

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

            //overload * to do element wise multiplication and return the resulting vector
            friend Vector<T, size> operator*<T, size> (const Vector<T, size> &v1, const Vector<T, size> &v2);

            //overload * set this vector to result of element wise multiplication with given vector and return reference to it
            Vector<T, size>& operator*= (const Vector<T, size> &other){

                for(int i = 0; i < size; ++i){
                    m_data[i] *= other.m_data[i];
                }

                return *this;
            } 

            //overload * to return a vector that is equal to this vector multiplied by a scalar
            friend Vector<T, size> operator*<T, size> (const Vector<T, size> &vec, T val);
            friend Vector<T, size> operator*<T, size> (T val, const Vector<T, size> &vec);

            //overload *= to multiply every entry of the vector with a given value
            Vector<T, size>& operator*= (T val){

                for(int i = 0; i < size; ++i){
                    m_data[i] *= val;
                }

                return *this;
            }

            //overload / to do element wise division and return the resulting vector
            friend Vector<T, size> operator/<T, size> (const Vector<T, size> &v1, const Vector<T, size> &v2);

            //overload / set this vector to result of element wise division with given vector and return reference to it
            Vector<T, size>& operator/= (const Vector<T, size> &other){

                for(int i = 0; i < size; ++i){
                    m_data[i] /= other.m_data[i];
                }

                return *this;
            } 

            //overload / to return a vector that is equal to (this vector divided by a scalar)/(a scalar divided by this vector)
            friend Vector<T, size> operator/<T, size> (const Vector<T, size> &vec, T val);
            friend Vector<T, size> operator/<T, size> (T val, const Vector<T, size> &vec);

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

            //compares two vectors taking possible rounding errors into account
            bool allClose(const Vector<T, size> &other) const{

                for(int i = 0; i < size; ++i){
                    if(!CG::Util::isClose(m_data[i], other.m_data[i], 1E-10, 1E-6)){
                        return false;
                    }
                }

                return true;
            }

            //orthogonaly project v1 onto v2
            friend Vector<T, size> orthogonalProject<T, size> (const Vector<T, size> &v1, const Vector<T, size> &v2);

            //cross product between v1 and v2; only defined for Vectors<T, 3>
            friend Vector<T, 3> cross<T> (const Vector<T, 3> &v1, const Vector<T, 3> &v2);

            //overload == operator; this is strict equality which is not necessarily what we want for floating point values
            friend bool operator==<T, size> (const Vector<T, size> &vec1, const Vector<T, size> &vec2);
            friend bool operator!=<T, size> (const Vector<T, size> &vec1, const Vector<T, size> &vec2);

            //overload << to be able to write vector to console
            friend std::ostream& operator<<<T, size> (std::ostream &out, const Vector<T, size> &vector);

        };

        template <typename T, int size>
        Vector<T, size> operator+(const Vector<T, size> &v1, const Vector<T, size> &v2){
            Vector<T, size> newVec;

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] = v1.m_data[i] + v2.m_data[i];
            }     

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator+ (const Vector<T, size> &vec, T val){
            Vector<T, size> newVec{ vec };

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] += val;
            }

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator+ (T val, const Vector<T, size> &vec){
            Vector<T, size> newVec{ vec };

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] += val;
            }

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator-(const Vector<T, size> &v1, const Vector<T, size> &v2){
            Vector<T, size> newVec;

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] = v1.m_data[i] - v2.m_data[i];
            }     

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator- (const Vector<T, size> &vec, T val){
            Vector<T, size> newVec{ vec };

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] -= val;
            }

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator- (T val, const Vector<T, size> &vec){
            Vector<T, size> newVec;

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] = val - vec.m_data[i];
            }

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator*(const Vector<T, size> &v1, const Vector<T, size> &v2){
            Vector<T, size> newVec;

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] = v1.m_data[i] * v2.m_data[i];
            }     

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator* (const Vector<T, size> &vec, T val){
            Vector<T, size> newVec{ vec };

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] *= val;
            }

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator* (T val, const Vector<T, size> &vec){
            Vector<T, size> newVec{ vec };

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] *= val;
            }

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator/(const Vector<T, size> &v1, const Vector<T, size> &v2){
            Vector<T, size> newVec;

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] = v1.m_data[i] / v2.m_data[i];
            }     

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator/ (const Vector<T, size> &vec, T val){
            Vector<T, size> newVec{ vec };

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] /= val;
            }

            return newVec;
        }

        template <typename T, int size>
        Vector<T, size> operator/ (T val, const Vector<T, size> &vec){
            Vector<T, size> newVec;

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] = val / vec.m_data[i];
            }

            return newVec;
        }

        template<typename T, int size>
        Vector<T, size> orthogonalProject(const Vector<T, size> &v1, const Vector<T, size> &v2){
            double t = (v1.dot(v2))/(v2.dot(v2));

            Vector<T, size> newVec{ v2 };

            for(int i = 0; i < size; ++i){
                newVec.m_data[i] *= t;
            }

            return newVec;
        }

        template<typename T>
        Vector<T, 3> cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2){
            Vector<T, 3> newVec;

            newVec.m_data[0] = v1.m_data[1] * v2.m_data[2] - v1.m_data[2] * v2.m_data[1];
            newVec.m_data[1] = v1.m_data[2] * v2.m_data[0] - v1.m_data[0] * v2.m_data[2];
            newVec.m_data[2] = v1.m_data[0] * v2.m_data[1] - v1.m_data[1] * v2.m_data[0];

            return newVec;
        }

        template<typename T, int size>
        bool operator== (const Vector<T, size> &vec1, const Vector<T, size> &vec2){
            
            for(int i = 0; i < size; ++i){
                if(vec1.m_data[i] != vec2.m_data[i]){
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
            out << "[ " << vector.m_data[0];

            for(int i = 1; i < size; ++i){
                out << ", " << vector.m_data[i];
            }

            out << " ]";

            return out;
        }
    }
}

#endif