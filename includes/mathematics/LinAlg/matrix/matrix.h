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
        class Matrix;

        template <typename T, int rows, int cols>
        bool operator== (const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

        template <typename T, int rows, int cols>
        std::ostream& operator<< (std::ostream &out, Matrix<T, rows, cols> &mat);

        template <typename T, int rows, int cols>
        Matrix<T, rows, cols> operator+(const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

        template <typename T, int rows, int cols>
        Matrix<T, rows, cols> operator+(const Matrix<T, rows, cols> &mat, T val);   

        template <typename T, int rows, int cols>
        Matrix<T, rows, cols> operator+(T val, const Matrix<T, rows, cols> &mat);

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

            //Copy Constructor: create Matrix as copy of another Matrix
            Matrix(const Matrix &other){
                for(int i = 0; i < rows*cols; ++i){
                    m_data[i] = other.m_data[i];
                }
            }

            //overload assignment operator to set the entries of this matrix to the ones of the other matrix
            Matrix<T, rows, cols>& operator= (const Matrix<T, rows, cols> &other){
                for(int i = 0; i < rows*cols; ++i){
                    m_data[i] = other.m_data[i];
                }

                return *this;
            }

            //overload T* typecast to make matrix decay to m_data if necessary
            operator T*(){
                return m_data;
            }

            //function to access an element at a certain matrix position; behaves as if matrix was in row major order
            T& at(int row, int col){
                return m_data[rows*col+row];
            }

            //overload + to return a new matrix that is the sum of the two given matrices
            friend Matrix<T, rows, cols> operator+<T, rows, cols> (const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

            //overload += to add the other matrix to this one and return reference to this matrix
            Matrix<T, rows, cols>& operator+= (const Matrix<T, rows, cols> &other){

                for(int i = 0; i < rows*cols; ++i){
                    m_data[i] += other.m_data[i];
                }

                return *this;
            }

            //overload + to add the given value to all entries of the given matrix and return new matrix by value
            friend Matrix<T, rows, cols> operator+<T, rows, cols> (const Matrix<T, rows, cols> &mat, T val);
            friend Matrix<T, rows, cols> operator+<T, rows, cols> (T val, const Matrix<T, rows, cols> &mat);

            //overload += to add a value to every entry of the vector
            Matrix<T, rows, cols>& operator+= (T val){

                for(int i = 0; i < rows*cols; ++i){
                    m_data[i] += val;
                }

                return *this;
            }

            //compare matrices element wise
            friend bool operator==<T, rows, cols> (const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

            //overload << operator to print matrix to std::out
            friend std::ostream& operator<<<T, rows, cols> (std::ostream &out, Matrix<T, rows, cols> &mat);
        };

        template <typename T, int rows, int cols>
        Matrix<T, rows, cols> operator+(const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2){
            Matrix<T, rows, cols> newMat;

            for(int i = 0; i < rows*cols; ++i){
                newMat.m_data[i] = m1.m_data[i] + m2.m_data[i];
            }     

            return newMat;
        }

        template <typename T, int rows, int cols>
        Matrix<T, rows, cols> operator+ (const Matrix<T, rows, cols> &mat, T val){
            Matrix<T, rows, cols> newMat{ mat };

            for(int i = 0; i < rows*cols; ++i){
                newMat.m_data[i] += val;
            }
            
            return newMat;
        }

        template <typename T, int rows, int cols>
        Matrix<T, rows, cols> operator+ (T val, const Matrix<T, rows, cols> &mat){
            Matrix<T, rows, cols> newMat{ mat };

            for(int i = 0; i < rows*cols; ++i){
                newMat.m_data[i] += val;
            }

            return newMat;
        }

        template <typename T, int rows, int cols>
        bool operator== (const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2){
            for(int i = 0; i < rows*cols; ++i){
                if(m1.m_data[i] != m2.m_data[i]){
                    return false;
                }
            }

            return true;
        }

        template <typename T, int rows, int cols>
        std::ostream& operator<< (std::ostream &out, Matrix<T, rows, cols> &mat){
            out << "[ ";

            for(int i = 0; i < rows; ++i){
                if(i == 0){
                    out << "[ " << mat.at(i, 0);
                }else{
                    out << ", [ " << mat.at(i, 0);
                }
                for(int j = 1; j < cols; ++j){
                    out << ", " << mat.at(i, j);
                }
                out << " ]";
            }

            out << " ]";

            return out;
        }
    }
}

#endif