#ifndef CG_FRAMEWORK_MATH_QUATERNION_QUATERNION_H
#define CG_FRAMEWORK_MATH_QUATERNION_QUATERNION_H

#include <math/math.h>

namespace CG{

    class Quaternion{
    protected:
        Vector3 m_imaginary{ 0.0, 0.0, 0.0 };
        GLfloat m_real{ 1.0 };

    public:
        Quaternion();
        Quaternion(const Vector3 &imaginary, GLfloat real);
        Quaternion(GLfloat qx, GLfloat qy, GLfloat qz, GLfloat qw);
        Quaternion(const Quaternion &other);

        Quaternion& operator= (const Quaternion &other);

        void setReal(GLfloat val);
        void setImaginary(Vector3 &vec);
        void setImaginary(GLfloat qx, GLfloat qy, GLfloat qz);

        GLfloat getReal() const;
        Vector3& getImaginary();

        Quaternion& operator*= (const Quaternion &other);
        Quaternion& operator*= (GLfloat s);
        Quaternion& operator+= (const Quaternion &other);

        Quaternion conjugate() const;
        GLfloat norm() const;
        void normalize();
        Quaternion inverse() const;
        Quaternion& invert();

        friend Quaternion operator* (const Quaternion &q1, const Quaternion &q2);
        friend Quaternion operator* (const Quaternion, GLfloat s);
        friend Quaternion operator* (GLfloat s, const Quaternion);
        friend Quaternion operator+ (const Quaternion &q1, const Quaternion &q2);

        friend Quaternion slerp (const Quaternion &q1, const Quaternion &q2, GLfloat fraction);

        friend std::ostream& operator<< (std::ostream &out, const Quaternion &q);
    };

    Quaternion operator* (const Quaternion &q1, const Quaternion &q2);
    Quaternion operator* (const Quaternion q, GLfloat s);
    Quaternion operator* (GLfloat s, const Quaternion q);
    Quaternion operator+ (const Quaternion &q1, const Quaternion &q2);

    std::ostream& operator<< (std::ostream &out, const Quaternion &q);

    //computes an interpolated quaternion that is q1 for fraction = 0 and q2 for fraction = 1
    Quaternion slerp (const Quaternion &q1, const Quaternion &q2, GLfloat fraction);

    //creates a rotation matrix using a unit quaternion
    Matrix4 createRotationMatrix(Quaternion &q);

}


#endif