#ifndef CG_FRAMEWORK_MATH_QUATERNION_QUATERNION_H
#define CG_FRAMEWORK_MATH_QUATERNION_QUATERNION_H

#include <math/math.h>

namespace CG{

    class Quaternion{
    protected:
        Vector3 m_imaginary{ 0.0, 0.0, 0.0 };
        float m_real{ 1.0 };

    public:
        Quaternion();
        Quaternion(const Vector3 &imaginary, float real);
        Quaternion(float qx, float qy, float qz, float qw);
        Quaternion(const Quaternion &other);

        Quaternion& operator= (const Quaternion &other);

        void setReal(float val);
        void setImaginary(Vector3 &vec);
        void setImaginary(float qx, float qy, float qz);

        float getReal() const;
        Vector3& getImaginary();

        Quaternion& operator*= (const Quaternion &other);
        Quaternion& operator*= (float s);
        Quaternion& operator+= (const Quaternion &other);

        Quaternion conjugate() const;
        float norm() const;
        Quaternion& normalize();
        Quaternion inverse() const;
        Quaternion& invert();

        friend Quaternion operator* (const Quaternion &q1, const Quaternion &q2);
        friend Quaternion operator* (const Quaternion, float s);
        friend Quaternion operator* (float s, const Quaternion);
        friend Quaternion operator+ (const Quaternion &q1, const Quaternion &q2);

        friend Quaternion slerp (const Quaternion &q1, const Quaternion &q2, float fraction);

        friend std::ostream& operator<< (std::ostream &out, const Quaternion &q);
    };

    Quaternion operator* (const Quaternion &q1, const Quaternion &q2);
    Quaternion operator* (const Quaternion q, float s);
    Quaternion operator* (float s, const Quaternion q);
    Quaternion operator+ (const Quaternion &q1, const Quaternion &q2);

    std::ostream& operator<< (std::ostream &out, const Quaternion &q);

    //computes an interpolated quaternion that is q1 for fraction = 0 and q2 for fraction = 1
    Quaternion slerp (const Quaternion &q1, const Quaternion &q2, float fraction);

    //creates a rotation matrix using a unit quaternion
    Matrix4 createRotationMatrix(Quaternion &q);

}


#endif