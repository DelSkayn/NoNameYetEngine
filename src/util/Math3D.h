#ifndef MATH3I_H 
#define MATH3I_H

#include <string>

#define MATH_PI 3.1415926535897932384626433832795

class Math{ template<typename T> static inline T abs(T & value); };

template<typename T,unsigned int I>
class Vector{
    protected:
        T values[I];
    public:
        inline Vector();
        inline Vector(const Vector<T, I>& other);

        template<typename D>
        inline Vector(const Vector<D, I>& other);

        inline T dot(const Vector<T, I>& other) const;

        inline T lengthSq() const;
        inline T length() const;

        inline Vector<T,I> & normalize();
        inline Vector<T,I> Lerp(const Vector<T,I>& r, T lerpFactor) const;

        inline Vector<T,I> reflect(const Vector<T,I>& normal) const;

        inline Vector<T,I> operator+(const Vector<T,I> & other) const;
        inline Vector<T,I> operator-(const Vector<T,I> & other) const;

        inline Vector<T,I> operator*(const T & value) const;
        inline Vector<T,I> operator/(const T & value) const;

        inline Vector<T,I> & operator+=(const Vector<T,I> & other);
        inline Vector<T,I> & operator-=(const Vector<T,I> & other);

        inline Vector<T,I> & operator*=(const T & value);
        inline Vector<T,I> & operator/=(const T & value);

        inline T& operator[] (unsigned int i);
        inline T operator[] (unsigned int i) const;

        inline bool operator==(const Vector<T,I> & other) const;
        inline bool operator!=(const Vector<T,I> & other) const;

        inline static Vector<T,I> normalize(const Vector<T,I> & );
        inline static Vector<T,I> random();

};

template<typename T>
class Vector2 :public Vector<T,2>{
    public:
        inline Vector2();
        inline Vector2(const Vector<T,2> & r);
        inline Vector2(T x, T y);

        inline T cross(const Vector2<T>& r) const;

        inline T x() const;
        inline T y() const;

        inline void setX(const T x);
        inline void setY(const T y);

        inline void set(const T x,const T y);
};

template<typename T>
class Vector3 : public Vector<T,3>{
    public:
        inline Vector3();
        inline Vector3(const Vector<T,3> & other);
        inline Vector3(const T x,const T y,const T z);

        inline Vector3<T> cross(const Vector3<T> & other) const;

        inline T x() const;
        inline T y() const;
        inline T z() const;


        inline void setX(T x);
        inline void setY(T Y);
        inline void setZ(T Z);

        inline void set(T x,T y,T z);
};

template<typename T>
class Vector4 : public Vector<T,4>{
    public:
        inline Vector4();
        inline Vector4(const Vector<T,4> & other);
        inline Vector4(T w,T x,T y,T z);

        inline T x() const;
        inline T y() const;
        inline T z() const;
        inline T w() const;

        inline void setX(T x);
        inline void setY(T Y);
        inline void setZ(T Z);
        inline void setW(T W);

        inline void set(T w,T x,T y,T z);
};

template<typename T, unsigned int I>
class Matrix{
    private:
        T m[I][I];
    public:
        inline Matrix();

        template<typename D>
        inline Matrix(const Matrix<D,I> & other);

        template<unsigned int D>
        inline Matrix(const Matrix<T,D> & other);

        inline Matrix<T,I> & toIdentity();
        inline Matrix<T,I> & toScale( const Vector<T,I -1> & scale);
        inline Matrix<T,I> & toTranslation(const Vector<T,I -1> & trans);

        inline Matrix<T,I> operator*(const Matrix<T,I> & other)const;
        inline Matrix<T,I> & operator*=(const Matrix<T,I> & other);

        inline Vector<T,I> transform(const Vector<T,I> & vec)const;
        inline Vector<T,I-1> transform(const Vector<T,I-1> & vec)const;

        inline void set(unsigned int x,unsigned int y,T val);

        inline const T* operator[](unsigned int index)const;
        inline T* operator[](unsigned int index);

};

template<typename T>
class Matrix4 : public Matrix<T,4>{
    public:
        inline Matrix4();
        inline Matrix4(const Matrix<T,4> & other);

        inline Matrix4<T> & toRotation(T x,T y,T z);
        inline Matrix4<T> & toRotation(const Vector3<T>& n,const Vector3<T>& v,const Vector3<T>& u);
        inline Matrix4<T> & toRotation(const Vector3<T> & forward, const Vector3<T> & up);

        inline static Matrix4<T> look_at(Vector3<T> eye,Vector3<T> direction,Vector3<T> up);

        inline Matrix4<T> & toPerspective(T fov, T aspectRatio, T zNear, T zFar);
        inline Matrix4<T> & toOrthographic(T left,T right,T bottom,T top,T near,T far);

        inline Matrix4<T> & invert();

};

template<typename T>
class Quaternion : public Vector4<T>{
    public:
        inline Quaternion(T w = 1,T x = 0,T y = 0,T z = 0);
        inline Quaternion(const Vector4<T> & vec);
        inline Quaternion(const Vector3<T> & axis,T angle);
        inline Quaternion(const Matrix4<T>& m);

        inline Quaternion<T> & toIdentity();

        inline Quaternion<T> rotate(const Vector3<T> & axis, T angle);

        inline Quaternion<T> NLerp(const Quaternion& r, T lerpFactor, bool shortestPath) const;
        inline Quaternion<T> SLerp(const Quaternion& r, T lerpFactor, bool shortestPath) const;

        inline Matrix4<T> toMatrix()const;

        inline Vector3<T> forward() const;
        inline Vector3<T> up() const;
        inline Vector3<T> down() const;
        inline Vector3<T> back() const;
        inline Vector3<T> right() const;
        inline Vector3<T> left() const;

        inline Quaternion<T> conjugate() const;

        inline Quaternion<T> operator*(const Quaternion& r) const;
        inline Quaternion<T> & operator*=(const Quaternion& r);
        inline Quaternion<T>  operator*(const Vector3<T>& r) const;
        inline Quaternion<T> & operator*=(const Vector3<T>& r);

        inline Vector3<T> rotateVec(const Vector3<T> & vec) const;

    private:
};

class MathUtil{
    public:
    template<typename T,unsigned int I>
    static std::string matrixToStr(const Matrix<T,I> & mat);

    template<typename T,unsigned int I>
    static std::string vectorToStr(const Vector<T,I> & mat);
};

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;

typedef Matrix4<float> Matrix4f;
typedef Matrix4<double> Matrix4d;

typedef Quaternion<float> Quaternionf;
typedef Quaternion<double> Quaterniond;


#include "Math3DDefine.h"

#endif /* MATH3I_H */
