#ifndef MATHEMATICS_MATRIX_H
#define MATHEMATICS_MATRIX_H
#include <iostream>
#include <vector>
#include <initializer_list>
#include <cassert>
#include <math.h>
#include <util/util.h>
#include <LinAlg/vector/vector.h>

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
    Matrix<T, rows, cols> operator-(const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator-(const Matrix<T, rows, cols> &mat, T val);   

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator-(T val, const Matrix<T, rows, cols> &mat);

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator*(const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator*(const Matrix<T, rows, cols> &mat, T val);   

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator*(T val, const Matrix<T, rows, cols> &mat);

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator/(const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator/(const Matrix<T, rows, cols> &mat, T val);   

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator/(T val, const Matrix<T, rows, cols> &mat);

    template <typename T, int rows, int cols>
    Matrix<T, cols, rows> transpose(const Matrix<T, rows, cols> &mat);

    template <typename T, int rows, int cols>
    class Matrix
    {
    protected:
        //T m_data[rows*cols]; //array with all matrix elements in column major order; PROBLEM: memory allocated on stack; make dynamic
        std::vector<T> m_data;

    public:
        //Constructor: creates matrix but doesn't initialize any values
        Matrix()
        {
            m_data.resize(rows*cols);
        }

        //Constructor: creates Matrix and initializes with values from initializer lists
        Matrix(const std::initializer_list<std::initializer_list<T>> &list) : Matrix()
        {

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
        Matrix(const Matrix &other) : Matrix()
        {
            for(int i = 0; i < rows*cols; ++i){
                m_data[i] = other.m_data[i];
            }
        }

        //destructor: delete dynamically allocated memory
        ~Matrix() {}

        //overload assignment operator to set the entries of this matrix to the ones of the other matrix
        Matrix<T, rows, cols>& operator= (const Matrix<T, rows, cols> &other)
        {
            for(int i = 0; i < rows*cols; ++i){
                m_data[i] = other.m_data[i];
            }

            return *this;
        }

        //overload T* typecast to make matrix decay to m_data if necessary
        T* data(){
            return m_data.data();
        }

        //function to access an element at a certain matrix position; behaves as if matrix was in row major order
        T& at(int row, int col){
            return m_data[rows*col+row];
        }
        
        //converts this matrix to the identity matrix
        Matrix<T, rows, cols>& setIdentity() {
            assert(rows == cols);

            for(int col = 0; col < cols; ++col){
                for(int row = 0; row < rows; ++row){
                    m_data[col * rows + row] = (row == col) ? 1 : 0;
                }
            }

            return *this;
        }

        //creates new matrix that is the transpose of given matrix and returns it
        friend Matrix<T, cols, rows> transpose<T, rows, cols>(const Matrix<T, rows, cols> &mat);
        friend Matrix<T, rows, cols> transpose<T, cols, rows>(const Matrix<T, cols, rows> &mat);

        //sets square matrix to the transpose of itself 
        Matrix<T, rows, cols>& transpose(){
            assert(rows == cols);

            for(int col = 1; col < cols; ++col){
                for(int row = 0; row < col; ++row){
                    T temp = m_data[col * rows + row];
                    m_data[col * rows + row] = m_data[row * cols + col];
                    m_data[row * cols + col] = temp;
                }
            }

            return *this;
        }

        //function that computes the trace of a square matrix and returns it
        T trace() const{
            assert(rows == cols);

            T sum{ 0 };

            for(int i{ 0 }; i < rows; ++i){
                sum += m_data[i*rows+i];
            }

            return sum;
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

        //overload - to return a new matrix that is the difference of the two given matrices
        friend Matrix<T, rows, cols> operator-<T, rows, cols> (const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

        //overload -= to subtract the other matrix from this one and return reference to this matrix
        Matrix<T, rows, cols>& operator-= (const Matrix<T, rows, cols> &other){

            for(int i = 0; i < rows * cols; ++i){
                m_data[i] -= other.m_data[i];
            }

            return *this;
        }

        //overload - to subtract the given value from all entries of the given matrix and return new matrix by value
        friend Matrix<T, rows, cols> operator-<T, rows, cols> (const Matrix<T, rows, cols> &mat, T val);
        //overload - to return a new matrix that is equal to difference of the given value and each matrix entry
        friend Matrix<T, rows, cols> operator-<T, rows, cols> (T val, const Matrix<T, rows, cols> &mat);

        //overload -= to subtract a value from every entry of the matrix
        Matrix<T, rows, cols>& operator-= (T val){

            for(int i = 0; i < rows * cols; ++i){
                m_data[i] -= val;
            }

            return *this;
        }

        //overload unary - operator to return inverse of given matrix
        Matrix<T, rows, cols> operator- () const{
            Matrix<T, rows, cols> newMat{ *this };

            for(int i = 0; i < rows * cols; ++i){
                newMat.m_data[i] *= -1;
            }

            return newMat;    
        }

        //overload * to do element wise multiplication and return the resulting matrix
        friend Matrix<T, rows, cols> operator*<T, rows, cols> (const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

        //overload * set this matrix to result of element wise multiplication with given matrix and return reference to it
        Matrix<T, rows, cols>& operator*= (const Matrix<T, rows, cols> &other){

            for(int i = 0; i < rows * cols; ++i){
                m_data[i] *= other.m_data[i];
            }

            return *this;
        } 

        //overload * to return a matrix that is equal to this matrix multiplied by a scalar
        friend Matrix<T, rows, cols> operator*<T, rows, cols> (const Matrix<T, rows, cols> &mat, T val);
        friend Matrix<T, rows, cols> operator*<T, rows, cols> (T val, const Matrix<T, rows, cols> &mat);

        //overload *= to multiply every entry of the matrix with a given value
        Matrix<T, rows, cols>& operator*= (T val){

            for(int i = 0; i < rows * cols; ++i){
                m_data[i] *= val;
            }

            return *this;
        }

        //overload / to do element wise division and return the resulting matrix
        friend Matrix<T, rows, cols> operator/<T, rows, cols> (const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

        //overload / set this matrix to result of element wise division with given matrix and return reference to it
        Matrix<T, rows, cols>& operator/= (const Matrix<T, rows, cols> &other){
            for(int i = 0; i < rows * cols; ++i){
                m_data[i] /= other.m_data[i];
            }

            return *this;
        } 

        //overload / to return a matrix that is equal to (this matrix divided by a scalar)/(a scalar divided by this matrix)
        friend Matrix<T, rows, cols> operator/<T, rows, cols> (const Matrix<T, rows, cols> &mat, T val);
        friend Matrix<T, rows, cols> operator/<T, rows, cols> (T val, const Matrix<T, rows, cols> &mat);

        //overload /= to divide every entry of the matrix by a given value
        Matrix<T, rows, cols>& operator/= (T val){

            for(int i = 0; i < rows * cols; ++i){
                m_data[i] /= val;
            }

            return *this;
        }

        //compare matrices element wise
        friend bool operator==<T, rows, cols> (const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2);

        //overload << operator to print matrix to std::out
        friend std::ostream& operator<<<T, rows, cols> (std::ostream &out, Matrix<T, rows, cols> &mat);
    };

    //computes matrix matrix multiplication and returns the resulting matrix
    template <typename T, int rowM1, int colM1rowM2, int colM2>
    Matrix<T, rowM1, colM2> dot(Matrix<T, rowM1, colM1rowM2> &m1, Matrix<T, colM1rowM2, colM2> &m2){
        Matrix<T, rowM1, colM2> res;

        for(int col{ 0 }; col < colM2; ++col){
            for(int row{ 0 }; row < rowM1; ++row){
                T sum{ 0 };
                for(int i{ 0 }; i < colM1rowM2; ++i){
                    sum += m1.at(row, i) * m2.at(i, col);
                }
                res.at(row, col) = sum;
            }
        }

        return res;
    }

    //computes matrix vector multiplication and returns resulting vector
    template <typename T, int rows, int cols>
    Vector<T, rows> dot(Matrix<T, rows, cols> &mat, Vector<T, cols> &vec){
        Vector<T, rows> res;

        for(int row{ 0 }; row < rows; ++row){
            T sum{ 0 };
            for(int i{ 0 }; i < cols; ++i){
                sum += mat.at(row, i) * vec.at(i);
            }
            res.at(row) = sum;
        }

        return res;
    }

    template <typename T, int rows, int cols>
    Matrix<T, cols, rows> transpose(const Matrix<T, rows, cols> &mat){
        Matrix<T, cols, rows> trans;

        for(int col = 0; col < cols; ++col){
            for(int row = 0; row < rows; ++row){
                trans.m_data[row * cols + col] = mat.m_data[col * rows + row];
            }
        }

        return trans;
    }        

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
    Matrix<T, rows, cols> operator-(const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2){
        Matrix<T, rows, cols> newMat;

        for(int i = 0; i < rows * cols; ++i){
            newMat.m_data[i] = m1.m_data[i] - m2.m_data[i];
        }     

        return newMat;
    }

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator- (const Matrix<T, rows, cols> &mat, T val){
        Matrix<T, rows, cols> newMat{ mat };

        for(int i = 0; i < rows * cols; ++i){
            newMat.m_data[i] -= val;
        }

        return newMat;
    }

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator- (T val, const Matrix<T, rows, cols> &mat){
        Matrix<T, rows, cols> newMat;

        for(int i = 0; i < rows * cols; ++i){
            newMat.m_data[i] = val - mat.m_data[i];
        }

        return newMat;
    }

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator*(const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2){
        Matrix<T, rows, cols> newMat;

        for(int i = 0; i < rows * cols; ++i){
            newMat.m_data[i] = m1.m_data[i] * m2.m_data[i];
        }     

        return newMat;
    }

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator* (const Matrix<T, rows, cols> &mat, T val){
        Matrix<T, rows, cols> newMat{ mat };

        for(int i = 0; i < rows * cols; ++i){
            newMat.m_data[i] *= val;
        }

        return newMat;
    }

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator* (T val, const Matrix<T, rows, cols> &mat){
        Matrix<T, rows, cols> newMat{ mat };

        for(int i = 0; i < rows * cols; ++i){
            newMat.m_data[i] *= val;
        }

        return newMat;
    }



    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator/(const Matrix<T, rows, cols> &m1, const Matrix<T, rows, cols> &m2){
        Matrix<T, rows, cols> newMat;

        for(int i = 0; i < rows * cols; ++i){
            newMat.m_data[i] = m1.m_data[i] / m2.m_data[i];
        }     

        return newMat;
    }

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator/ (const Matrix<T, rows, cols> &mat, T val){
        Matrix<T, rows, cols> newMat{ mat };

        for(int i = 0; i < rows * cols; ++i){
            newMat.m_data[i] /= val;
        }

        return newMat;
    }

    template <typename T, int rows, int cols>
    Matrix<T, rows, cols> operator/ (T val, const Matrix<T, rows, cols> &mat){
        Matrix<T, rows, cols> newMat;

        for(int i = 0; i < rows * cols; ++i){
            newMat.m_data[i] = val / mat.m_data[i];
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




#endif