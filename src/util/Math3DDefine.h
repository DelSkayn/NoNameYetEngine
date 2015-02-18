#include "Math3D.h"
#include <cmath>

#include <string>
#include <sstream>

//--------------Math-----------------------



//--------------Vector<T,I>-----------------

template<typename T,unsigned int I>
Vector<T,I>::Vector(){
    for(unsigned int i = 0; i < I;i++){
        (*this)[i] = 0;
    }
}

template<typename T,unsigned int I>
Vector<T,I>::Vector(const Vector<T,I> & other){
    for(unsigned int i = 0; i< I;i++){
        (*this)[i] = other[i];
    }
}

template<typename T,unsigned int I>
T Vector<T,I>::dot(const Vector<T,I> & other) const {
    T result = T(0);
    for(unsigned int i = 0;i < I;i++){
        result += (*this)[i] * other[i];
    }
    return result;
}

template<typename T,unsigned int I>
T Vector<T,I>::lengthSq() const {
    T result = T(0);
    for(unsigned int i = 0;i < I;i++){
        result += (*this)[i] * (*this)[i];
    }
    return result;
}

template<typename T,unsigned int I>
T Vector<T,I>::length()const {
    return sqrt(lengthSq());
}

template<typename T,unsigned int I>
Vector<T,I>& Vector<T,I>::normalize(){
    (*this) /= length();
    return *this;
}

template<typename T,unsigned int I>
Vector<T,I> Vector<T,I>::operator+(const Vector<T,I> & other) const{
    Vector<T,I> result;
    for(unsigned int i = 0;i < I;i++){
        result[i] = (*this)[i] + other[i]; 
    }
    return result;
}

template<typename T,unsigned int I>
Vector<T,I> Vector<T,I>::operator-(const Vector<T,I> & other) const{
    Vector<T,I> result;
    for(unsigned int i = 0;i < I;i++){
        result[i] = (*this)[i] - other[i]; 
    }
    return result;
}

template<typename T,unsigned int I>
Vector<T,I> Vector<T,I>::operator*(const T & value) const{
    Vector<T,I> result;
    for(unsigned int i = 0;i < I;i++){
        result[i] = (*this)[i] * value; 
    }
    return result;
}

template<typename T,unsigned int I>
Vector<T,I> Vector<T,I>::operator/(const T & value) const{
    Vector<T,I> result;
    for(unsigned int i = 0;i < I;i++){
        result[i] = (*this)[i] / value; 
    }
    return result;
}

template<typename T,unsigned int I>
Vector<T,I> & Vector<T,I>::operator+=(const Vector<T,I> & other){
    for(unsigned int i = 0;i < I;i++){
        (*this)[i] += other[i];
    }
    return(*this);
}
template<typename T,unsigned int I>
Vector<T,I> & Vector<T,I>::operator-=(const Vector<T,I> & other){
    for(unsigned int i = 0;i < I;i++){
        (*this)[i] -= other[i];
    }
    return(*this);
}

template<typename T,unsigned int I>
Vector<T,I> & Vector<T,I>::operator*=(const T & value){
    for(unsigned int i = 0;i < I;i++){
        (*this)[i] *= value;
    }
    return(*this);
}
template<typename T,unsigned int I>
Vector<T,I> & Vector<T,I>::operator/=(const T & value){
    for(unsigned int i = 0;i < I;i++){
        (*this)[i] /= value;
    }
    return(*this);
}

template<typename T,unsigned int I>
T& Vector<T,I>::operator[] (unsigned int i){
    return values[i];
}
template<typename T,unsigned int I>
T Vector<T,I>::operator[] (unsigned int i) const{
    return values[i];
}

template<typename T,unsigned int I>
bool Vector<T,I>::operator==(const Vector<T,I> & other) const{
    for(unsigned int i = 0;i < I;i++){
        if((*this)[i] != other[i]){
            return false;
        }
    }
    return true;
}
template<typename T,unsigned int I>
bool Vector<T,I>::operator!=(const Vector<T,I> & other) const{
    for(unsigned int i = 0;i < I;i++){
        if((*this)[i] != other[i]){
            return true;
        }
    }
    return false;
}

template<typename T,unsigned int I>
Vector<T,I> Vector<T,I>::normalize(const Vector<T,I> & other){
    return other / other.length();
}


//--------------Vector<T,I>-----------------
//--------------Vector2<T>-----------------


template<typename T>
Vector2<T>::Vector2(){
    (*this)[0] = T(0);
    (*this)[1] = T(0);
}

template<typename T>
Vector2<T>::Vector2(const Vector<T,2> & other){
    (*this)[0] = other[0];
    (*this)[1] = other[1];
}

template<typename T>
Vector2<T>::Vector2(T x,T y){
    (*this)[0] = x;
    (*this)[1] = y;
}

template<typename T>
T Vector2<T>::cross(const Vector2<T> & other) const {
    return (*this)[0] * other[1] - (*this)[1] * other[0];
}

template<typename T>
T Vector2<T>::x() const {
    return (*this)[0];
}

template<typename T>
T Vector2<T>::y() const {
    return (*this)[1];
}

template<typename T>
void Vector2<T>::setX( const T x){
    (*this)[0] = x;
}

template<typename T>
void Vector2<T>::setY( const T y){
    (*this)[1] = y;
}

template<typename T>
void Vector2<T>::set(const T x,const T y){
    (*this)[0] = x;
    (*this)[1] = y;
}


//--------------Vector2<T>-----------------
//--------------Vector3<T>-----------------

template<typename T>
Vector3<T>::Vector3(){
    (*this)[0] = T(0);
    (*this)[1] = T(0);
    (*this)[2] = T(0);
}

template<typename T>
Vector3<T>::Vector3(const Vector<T,3> & other){
    (*this)[0] = other[0];
    (*this)[1] = other[1];
    (*this)[2] = other[2];
}

template<typename T>
Vector3<T>::Vector3(T x,T y,T z){
    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
}

template<typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T> & other) const {
    T x = (*this)[1] * other[2] - (*this)[2] * other[1];
    T y = (*this)[2] * other[0] - (*this)[0] * other[2];
    T z = (*this)[0] * other[1] - (*this)[1] * other[0];

    return Vector3<T>(x,y,z);
}

template<typename T>
T Vector3<T>::x() const {
    return (*this)[0];
}

template<typename T>
T Vector3<T>::y() const {
    return (*this)[1];
}

template<typename T>
T Vector3<T>::z() const {
    return (*this)[2];
}

template<typename T>
void Vector3<T>::setX(T x){
    (*this)[0] = x;
}

template<typename T>
void Vector3<T>::setY(T y){
    (*this)[1] = y;
}

template<typename T>
void Vector3<T>::setZ(T z){
    (*this)[2] = z;
}

template<typename T>
void Vector3<T>::set(const T x,const T y,const T z){
    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
}

//--------------Vector3<T>-----------------
//--------------Vector4<T>-----------------

template<typename T>
Vector4<T>::Vector4(){
    (*this)[0] = T(0);
    (*this)[1] = T(0);
    (*this)[2] = T(0);
    (*this)[3] = T(0);
}

template<typename T>
Vector4<T>::Vector4(const Vector<T,4> & other){
    (*this)[0] = other[0];
    (*this)[1] = other[1];
    (*this)[2] = other[2];
    (*this)[3] = other[3];
}

template<typename T>
Vector4<T>::Vector4(T w,T x,T y,T z){
    (*this)[0] = w;
    (*this)[1] = x;
    (*this)[2] = y;
    (*this)[3] = z;
}

template<typename T>
T Vector4<T>::x() const {
    return (*this)[1];
}

template<typename T>
T Vector4<T>::y() const {
    return (*this)[2];
}

template<typename T>
T Vector4<T>::z() const {
    return (*this)[3];
}

template<typename T>
T Vector4<T>::w() const {
    return (*this)[0];
}

template<typename T>
void Vector4<T>::setW(T w){
    (*this)[0] = w;
}

template<typename T>
void Vector4<T>::setX(T x){
    (*this)[1] = x;
}

template<typename T>
void Vector4<T>::setY(T y){
    (*this)[2] = y;
}

template<typename T>
void Vector4<T>::setZ(T z){
    (*this)[3] = z;
}

template<typename T>
void Vector4<T>::set(T w,T x,T y,T z){
    (*this)[0] = w;
    (*this)[1] = x;
    (*this)[2] = y;
    (*this)[3] = z;
}

//--------------Vector4<T>-----------------
//--------------Matrix<T,I>----------------

template<typename T,unsigned int I>
template<typename D>
Matrix<T,I>::Matrix(const Matrix<D,I> & other){
    for(unsigned int i = 0;i < I;i++){
        for(unsigned int j = 0;j < I;j++){
            (*this)[i][j] = (T)other[i][j];
        }
    }
}

template<typename T,unsigned int I>
Matrix<T,I>::Matrix(){
}

template<typename T,unsigned int I>
template<unsigned int D>
Matrix<T,I>::Matrix(const Matrix<T,D> & other){
    if(D < I){
        toIdentity();
    }
    for(unsigned int i = 0;i < D;i++){
        for(unsigned int j = 0;j < D;j++){
            m[i][j] = other.m[i][j];
        }
    }
}

template<typename T,unsigned int I>
Matrix<T,I> & Matrix<T,I>::toIdentity(){
    for(unsigned int i = 0;i < I;i++){
        for(unsigned int j = 0;j < I;j++){
            m[i][j] = T(0);
        }
    }
    for(unsigned int i = 0;i < I;i++){
        m[i][i] = T(1);
    }
    return (*this);
}

template<typename T,unsigned int I>
Matrix<T,I> & Matrix<T,I>::toScale(const Vector<T,I -1> & scale){
    for(unsigned int i = 0; i < I;  i++){
        for(unsigned int j = 0; j < I; j++){
            if(i == j && i != I-1){
                m[i][j] = scale[i];
            }else{
                m[i][j] = T(0);
            }
        }
    }

    m[I -1][I - 1] = T(1);
    return *this;
}
template<typename T,unsigned int I>
Matrix<T,I> & Matrix<T,I>::toTranslation(const Vector<T,I-1>& trans){
    toIdentity();
    for(unsigned int i = 0;i < I-1;i++){
        m[I-1][i] += trans[i];
    }
    return *this;
}

template<typename T,unsigned int I>
Matrix<T,I> Matrix<T,I>::operator*(const Matrix<T,I>& trans)const{
    Matrix<T,I> result;
    for(unsigned int i = 0;i<I;i++){

        for(unsigned int j = 0;j<I;j++){

            result.m[i][j] = T(0);
            for(unsigned int k = 0;k<I;k++){
                result.m[i][j] += m[k][j] * trans.m[i][k];
            }
        }
    }
    return result;
}

template<typename T,unsigned int I>
Matrix<T,I> & Matrix<T,I>::operator*=(const Matrix<T,I>& trans){
    Matrix<T,I> result;
    for(unsigned int i = 0;i<I;i++){
        for(unsigned int j = 0;j<I;j++){
            result.m[i][j] = T(0);
            for(unsigned int k = 0;k<I;k++){
                result.m[i][j] += m[k][j] * trans.m[i][k];
            }
        }
    }
    *this = result;
    return *this;
}

template<typename T,unsigned int I>
Vector<T,I> Matrix<T,I>::transform(const Vector<T,I>& trans) const{
    Vector<T,I> result;
    for(unsigned int i = 0;i<I;i++){
        result[i] = 0;
        for(unsigned int j = 0;j<I;j++){
            result += m[j][i] * trans[j];
        }
    }
    return result;
}
template<typename T,unsigned int I>
Vector<T,I-1> Matrix<T,I>::transform(const Vector<T,I-1>& trans) const{
    Vector<T,I> result;
    for(unsigned int i = 0;i<I-1;i++){
        result[i] = trans[i];
    }

    result[I-1] = T(1);

    result = transform(result);
    Vector<T,I-1> ret;

    for(unsigned int i = 0;i < I-1;i++){
        ret[i] = result[i];
    }
    return ret;
}

template<typename T,unsigned int I>
void Matrix<T,I>::set(unsigned int x,unsigned int y,T val){
    m[x][y] = val;
}

template<typename T,unsigned int I>
const T* Matrix<T,I>::operator[](unsigned int index) const{
    return m[index];
}

template<typename T,unsigned int I>
T* Matrix<T,I>::operator[](unsigned int index){
    return m[index];
}

//--------------Matrix<T,I>----------------
//--------------Matrix4<T>-----------------

template<typename T>
Matrix4<T>::Matrix4() : Matrix<T,4>(){
}

template<typename T>
Matrix4<T>::Matrix4(const Matrix<T,4> & other){
    for(unsigned int i = 0;i < 4;i++){
        for(unsigned int j = 0;j < 4;j++){
            (*this)[i][j] = other[i][j];
        }
    }
}

template<typename T>
Matrix4<T> & Matrix4<T>::toRotation(T x,T y,T z){
    Matrix4<T> rx, ry, rz;

    rx[0][0] = T(1);   rx[1][0] = T(0);   rx[2][0] = T(0);    rx[3][0] = T(0);
    rx[0][1] = T(0);   rx[1][1] = cos(x); rx[2][1] = -sin(x); rx[3][1] = T(0);
    rx[0][2] = T(0);   rx[1][2] = sin(x); rx[2][2] = cos(x);  rx[3][2] = T(0);
    rx[0][3] = T(0);   rx[1][3] = T(0);   rx[2][3] = T(0);    rx[3][3] = T(1);

    ry[0][0] = cos(y); rx[1][0] = T(0);   rx[2][0] = -sin(y); rx[3][0] = T(0);
    ry[0][1] = T(0);   rx[1][1] = T(1);   rx[2][1] = T(0);    rx[3][1] = T(0);
    ry[0][2] = sin(y); rx[1][2] = T(0);   rx[2][2] = cos(y);  rx[3][2] = T(0);
    ry[0][3] = T(0);   rx[1][3] = T(0);   rx[2][3] = T(0);    rx[3][3] = T(1);

    rz[0][0] = cos(z); rx[1][0] = -sin(z); rx[2][0] = T(0);    rx[3][0] = T(0);
    rz[0][1] = sin(z); rx[1][1] = cos(z);  rx[2][1] = T(0);    rx[3][1] = T(0);
    rz[0][2] = T(0);   rx[1][2] = T(0);    rx[2][2] = T(1);    rx[3][2] = T(0);
    rz[0][3] = T(0);   rx[1][3] = T(0);    rx[2][3] = T(0);    rx[3][3] = T(1);

    *this = rz * ry * rx;

    return *this;
}
template<typename T>
Matrix4<T> & Matrix4<T>::toRotation(const Vector3<T> & n,const Vector3<T> & v,const Vector3<T> & u){
    (*this)[0][0] = u.x(); (*this)[1][0] = u.y(); (*this)[2][0] = u.z(); (*this)[3][0] = T(0);
    (*this)[0][1] = v.x(); (*this)[1][1] = v.y(); (*this)[2][1] = v.z(); (*this)[3][1] = T(0);
    (*this)[0][2] = n.x(); (*this)[1][2] = n.y(); (*this)[2][2] = n.z(); (*this)[3][2] = T(0);
    (*this)[0][3] =  T(0); (*this)[1][3] = T(0);  (*this)[2][3] = T(0);  (*this)[3][3] = T(1);

    return *this;
}

template<typename T>
Matrix4<T> & Matrix4<T>::toRotation(const Vector3<T> & forward, const Vector3<T> & up){
    Vector3<T> n = Vector3<T>::normalize(forward);
    Vector3<T> u = Vector3<T>::normalize(up).cross(n);
    Vector3<T> v = n.cross(u);

    return toRotation(n,v,u);
}

template<typename T>
Matrix4<T> & Matrix4<T>::toPerspective(T fov, T aspectRatio, T zNear,T zFar){
    const T zRange = zFar-zNear;
    const T tanHalfFov = tanf(fov / T(2));

    (*this)[0][0] =  T(1)/(tanHalfFov * aspectRatio); (*this)[1][0] = T(0);            (*this)[2][0] = T(0);  (*this)[3][0] = T(0);
    (*this)[0][1] =  T(0);                            (*this)[1][1] = T(1)/tanHalfFov; (*this)[2][1] = T(0);  (*this)[3][1] = T(0);
    (*this)[0][2] =  T(0);                            (*this)[1][2] = T(0);            (*this)[2][2] = (-zNear - zFar)/zRange;  (*this)[3][2] = T(2)*-zFar*zNear/zRange;
    (*this)[0][3] =  T(0);                            (*this)[1][3] = T(0);            (*this)[2][3] = T(-1); (*this)[3][3] = T(0);

    return * this;
}

template<typename T>
Matrix4<T> & Matrix4<T>::toOrthographic(T left,T right,T bottom,T top,T near,T far){
    const T width = (right - left);
    const T height = (top - bottom);
    const T depth = (far - near);

    (*this)[0][0] =  T(2)/width; (*this)[1][0] = T(0);       (*this)[2][0] = T(0);        (*this)[3][0] = -(right + left)/width;
    (*this)[0][1] =  T(0);       (*this)[1][1] = T(2)/width; (*this)[2][1] = T(0);        (*this)[3][1] = -(top + bottom)/height;
    (*this)[0][2] =  T(0);       (*this)[1][2] = T(0);       (*this)[2][2] = T(-2)/depth; (*this)[3][2] = -(far + near)/depth;
    (*this)[0][3] =  T(0);       (*this)[1][3] = T(0);       (*this)[2][3] = T(0);        (*this)[3][3] = T(1);

    return *this;
}

template<typename T>
Matrix4<T> & Matrix4<T>::invert(){
    Matrix4<T> temp;

    temp[0][0] = (*this)[1][1] * (*this)[2][2] * (*this)[3][3] -
        (*this)[1][1] * (*this)[2][3] * (*this)[3][2] -
        (*this)[2][1] * (*this)[1][2] * (*this)[3][3] +
        (*this)[2][1] * (*this)[1][3] * (*this)[3][2] +
        (*this)[3][1] * (*this)[1][2] * (*this)[2][3] -
        (*this)[3][1] * (*this)[1][3] * (*this)[2][2] ;

    temp[1][0] = -(*this)[1][0] * (*this)[2][2] * (*this)[3][3] +
        (*this)[1][0] * (*this)[2][3] * (*this)[3][2] +
        (*this)[2][0] * (*this)[1][2] * (*this)[3][3] -
        (*this)[2][0] * (*this)[1][3] * (*this)[3][2] -
        (*this)[3][0] * (*this)[1][2] * (*this)[2][3] +
        (*this)[3][0] * (*this)[1][3] * (*this)[2][2] ;

    temp[2][0] = (*this)[1][0] * (*this)[2][1] * (*this)[3][3] -
        (*this)[1][0] * (*this)[2][3] * (*this)[3][1] -
        (*this)[2][0] * (*this)[1][1] * (*this)[3][3] +
        (*this)[2][0] * (*this)[1][3] * (*this)[3][1] +
        (*this)[3][0] * (*this)[1][1] * (*this)[2][3] -
        (*this)[3][0] * (*this)[1][3] * (*this)[2][1] ;

    //Oh (*this)y god

    temp[3][0] = -(*this)[1][0] * (*this)[2][1] * (*this)[3][2] +
        (*this)[1][0] * (*this)[2][2] * (*this)[3][1] +
        (*this)[2][0] * (*this)[1][1] * (*this)[3][2] -
        (*this)[2][0] * (*this)[1][2] * (*this)[3][1] -
        (*this)[3][0] * (*this)[1][1] * (*this)[2][2] +
        (*this)[3][0] * (*this)[1][2] * (*this)[2][1] ;

    temp[0][1] = -(*this)[0][1] * (*this)[2][2] * (*this)[3][3] +
        (*this)[0][1] * (*this)[2][3] * (*this)[3][2] +
        (*this)[2][1] * (*this)[0][2] * (*this)[3][3] -
        (*this)[2][1] * (*this)[0][3] * (*this)[3][2] -
        (*this)[3][1] * (*this)[0][2] * (*this)[2][3] +
        (*this)[3][1] * (*this)[0][3] * (*this)[2][2] ;

    temp[1][1] = (*this)[0][0] * (*this)[2][2] * (*this)[3][3] -
        (*this)[0][0] * (*this)[2][3] * (*this)[3][2] -
        (*this)[2][0] * (*this)[0][2] * (*this)[3][3] +
        (*this)[2][0] * (*this)[0][3] * (*this)[3][2] +
        (*this)[3][0] * (*this)[0][2] * (*this)[2][3] -
        (*this)[3][0] * (*this)[0][3] * (*this)[2][2] ;

    //it keeps going on

    temp[2][1] = -(*this)[0][0] * (*this)[2][1] * (*this)[3][3] +
        (*this)[0][0] * (*this)[2][3] * (*this)[3][1] +
        (*this)[2][0] * (*this)[0][1] * (*this)[3][3] -
        (*this)[2][0] * (*this)[0][3] * (*this)[3][1] -
        (*this)[3][0] * (*this)[0][1] * (*this)[2][3] +
        (*this)[3][0] * (*this)[0][3] * (*this)[2][1] ;

    temp[3][1] = (*this)[0][0] * (*this)[2][1] * (*this)[3][2] -
        (*this)[0][0] * (*this)[2][2] * (*this)[3][1] -
        (*this)[2][0] * (*this)[0][1] * (*this)[3][2] +
        (*this)[2][0] * (*this)[0][2] * (*this)[3][1] +
        (*this)[3][0] * (*this)[0][1] * (*this)[2][2] -
        (*this)[3][0] * (*this)[0][2] * (*this)[2][1] ;

    temp[0][2] = (*this)[0][1] * (*this)[1][2] * (*this)[3][3] -
        (*this)[0][1] * (*this)[1][3] * (*this)[3][2] -
        (*this)[1][1] * (*this)[0][2] * (*this)[3][3] +
        (*this)[1][1] * (*this)[0][3] * (*this)[3][2] +
        (*this)[3][1] * (*this)[0][2] * (*this)[1][3] -
        (*this)[3][1] * (*this)[0][3] * (*this)[1][2] ;

    //is there an end to this (*this)adness?

    temp[1][2] = -(*this)[0][0] * (*this)[1][2] * (*this)[3][3] +
        (*this)[0][0] * (*this)[1][3] * (*this)[3][2] +
        (*this)[1][0] * (*this)[0][2] * (*this)[3][3] -
        (*this)[1][0] * (*this)[0][3] * (*this)[3][2] -
        (*this)[3][0] * (*this)[0][2] * (*this)[1][3] +
        (*this)[3][0] * (*this)[0][3] * (*this)[1][2] ;

    temp[2][2] = (*this)[0][0] * (*this)[1][1] * (*this)[3][3] -
        (*this)[0][0] * (*this)[1][3] * (*this)[3][1] -
        (*this)[1][0] * (*this)[0][1] * (*this)[3][3] +
        (*this)[1][0] * (*this)[0][3] * (*this)[3][1] +
        (*this)[3][0] * (*this)[0][1] * (*this)[1][3] -
        (*this)[3][0] * (*this)[0][3] * (*this)[1][1] ;

    temp[3][2] = -(*this)[0][0] * (*this)[1][1] * (*this)[3][2] +
        (*this)[0][0] * (*this)[1][2] * (*this)[3][1] +
        (*this)[1][0] * (*this)[0][1] * (*this)[3][2] -
        (*this)[1][0] * (*this)[0][2] * (*this)[3][1] -
        (*this)[3][0] * (*this)[0][1] * (*this)[1][2] +
        (*this)[3][0] * (*this)[0][2] * (*this)[1][1] ;

    //it is horrible

    temp[0][3] = -(*this)[0][1] * (*this)[1][2] * (*this)[2][3] +
        (*this)[0][1] * (*this)[1][3] * (*this)[2][2] +
        (*this)[1][1] * (*this)[0][2] * (*this)[2][3] -
        (*this)[1][1] * (*this)[0][3] * (*this)[2][2] -
        (*this)[2][1] * (*this)[0][2] * (*this)[1][3] +
        (*this)[2][1] * (*this)[0][3] * (*this)[1][2] ;

    temp[1][3] = (*this)[0][0] * (*this)[1][2] * (*this)[2][3] -
        (*this)[0][0] * (*this)[1][3] * (*this)[2][2] -
        (*this)[1][0] * (*this)[0][2] * (*this)[2][3] +
        (*this)[1][0] * (*this)[0][3] * (*this)[2][2] +
        (*this)[2][0] * (*this)[0][2] * (*this)[1][3] -
        (*this)[2][0] * (*this)[0][3] * (*this)[1][2] ;

    //I need to last, salvation is near

    temp[2][3] = -(*this)[0][0] * (*this)[1][1] * (*this)[2][3] +
        (*this)[0][0] * (*this)[1][3] * (*this)[2][1] +
        (*this)[1][0] * (*this)[0][1] * (*this)[2][3] -
        (*this)[1][0] * (*this)[0][3] * (*this)[2][1] -
        (*this)[2][0] * (*this)[0][1] * (*this)[1][3] +
        (*this)[2][0] * (*this)[0][3] * (*this)[1][1] ;

    temp[3][3] = (*this)[0][0] * (*this)[1][1] * (*this)[2][2] -
        (*this)[0][0] * (*this)[1][2] * (*this)[2][1] -
        (*this)[1][0] * (*this)[0][1] * (*this)[2][2] +
        (*this)[1][0] * (*this)[0][2] * (*this)[2][1] +
        (*this)[2][0] * (*this)[0][1] * (*this)[1][2] -
        (*this)[2][0] * (*this)[0][2] * (*this)[1][1] ;

    //god that was horrible

    float det = (*this)[0][0] * temp[0][0] + (*this)[0][1] * temp[1][0] + (*this)[0][2] * temp[2][0] + (*this)[0][3] * temp[3][0];

    if (det == 0)
        return *this;

    det = 1.0 / det;

    for (unsigned int i = 0; i < 4; i++)
    {
        for(unsigned int j = 0;j < 4;j++){
            (*this)[i][j] = temp[i][j] * det;
        }
    }
    return *this;

}

//--------------Matrix4<T>-----------------
//--------------Quaternion-----------------

template<typename T>
Quaternion<T>::Quaternion(T w,T x,T y,T z){
    (*this)[0] = w;
    (*this)[1] = x;
    (*this)[2] = y;
    (*this)[3] = z;
}

template<typename T>
Quaternion<T>::Quaternion(const Vector4<T> & vec){
    (*this)[0] = vec[0];
    (*this)[1] = vec[1];
    (*this)[2] = vec[2];
    (*this)[3] = vec[3];
}

template<typename T>
Quaternion<T>::Quaternion(const Vector3<T> & axis,T angle){
    const T sinus = std::sin(angle/2);
    const T cosin = std::cos(angle/2);

    (*this)[1] = axis.x() * sinus; 
    (*this)[2] = axis.y() * sinus;  
    (*this)[3] = axis.z() * sinus;  
    (*this)[0] = cosin;
}

template<typename T>
Quaternion<T>::Quaternion(const Matrix4<T>& m){
    T trace = m[0][0] + m[1][1] + m[2][2];

    if(trace > 0){
        T s = 0.5 / sqrt(trace + 1);
        (*this)[0] = 0.25 /s;
        (*this)[1] = (m[1][2] - m[2][1]) * s;
        (*this)[2] = (m[2][0] - m[0][2]) * s;
        (*this)[3] = (m[0][1] - m[1][0]) * s;
    }else if(m[0][0] > m[1][1] && m[0][0] > m[2][2]){
        T s = 2 * sqrt(1 + m[0][0] - m[1][1] - m[2][2]);
        (*this)[0] = (m[1][2] - m[2][1]) /s;
        (*this)[1] = 0.25 * s;
        (*this)[2] = (m[1][0] - m[0][1]) /s;
        (*this)[3] = (m[2][0] - m[0][2]) /s;
    }
    else if(m[1][1] > m[2][2]){
        T s = 2 * sqrt(1 + m[1][1] - m[0][0] - m[2][2]);
        (*this)[0] = (m[2][0] - m[0][2]) /s;
        (*this)[1] = (m[1][0] - m[0][1]) /s;
        (*this)[2] = 0.25 * s;
        (*this)[3] = (m[2][1] - m[1][2]) /s;
    }else{
        T s = 2 * sqrt(1 + m[2][2] - m[1][1] - m[0][0]);
        (*this)[0] = (m[0][1] - m[1][0]) /s;
        (*this)[1] = (m[2][0] - m[0][2]) /s;
        (*this)[2] = (m[1][2] - m[2][1]) /s;
        (*this)[3] = 0.25 * s;
    }

    this->normalize();
}

template<typename T>
Matrix4<T> Quaternion<T>::toMatrix() const{

    Vector3<T> forward = Vector3<T>(2 * ((*this)[1] * (*this)[3] - (*this)[0] * (*this)[2])
            ,2 * ((*this)[2] * (*this)[3] + (*this)[0] * (*this)[1])
            ,1 - 2 * ((*this)[1] * (*this)[1] + (*this)[2] * (*this)[2]));

    Vector3<T> up = Vector3<T>(2 * ((*this)[1] * (*this)[2] + (*this)[0] * (*this)[3])
            ,1 - 2 * ((*this)[1] * (*this)[1] + (*this)[3] * (*this)[3])
            ,2 * ((*this)[2] * (*this)[3] - (*this)[0] * (*this)[1]));

    Vector3<T> right = Vector3<T>(1 - 2 * ((*this)[2] * (*this)[2] + (*this)[3] * (*this)[3])
            ,2 * ((*this)[1] * (*this)[2] - (*this)[0] * (*this)[3])
            ,2 * ((*this)[1] * (*this)[3] + (*this)[0] * (*this)[2]));

    return Matrix4<T>().toRotation(forward,up,right);
}

template<typename T>
Quaternion<T> Quaternion<T>::conjugate() const{
    return Quaternion<T>((*this)[0], -(*this)[1], -(*this)[2], -(*this)[3]);
}

template<typename T>
Vector3<T> Quaternion<T>::rotateVec(const Vector3<T> & vec) const{
    Quaternion w = (*this) * vec * conjugate();
    Vector3<T> ret(w[1],w[2],w[3]);
    return ret;
}

template<typename T>
Quaternion<T> Quaternion<T>::operator*(const Quaternion<T> & other) const{
    const T w = ((*this)[0] * other[0]) - ((*this)[1] * other[1]) - ((*this)[2] * other[2]) - ((*this)[3] * other[3]);
    const T x = ((*this)[1] * other[0]) + ((*this)[0] * other[1]) + ((*this)[2] * other[3]) - ((*this)[3] * other[2]);
    const T y = ((*this)[2] * other[0]) + ((*this)[0] * other[2]) + ((*this)[3] * other[1]) - ((*this)[1] * other[3]);
    const T z = ((*this)[3] * other[0]) + ((*this)[0] * other[3]) + ((*this)[1] * other[2]) - ((*this)[2] * other[1]);

    return Quaternion<T>(w,x,y,z);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator*(const Vector3<T> & other) const{
    const T w = ((*this)[1] * other[0]) - ((*this)[2] * other[1]) - ((*this)[3] * other[2]);
    const T x = ((*this)[0] * other[0]) + ((*this)[2] * other[2]) - ((*this)[3] * other[1]);
    const T y = ((*this)[0] * other[1]) + ((*this)[3] * other[0]) - ((*this)[1] * other[2]);
    const T z = ((*this)[0] * other[2]) + ((*this)[1] * other[1]) - ((*this)[2] * other[0]);

    return Quaternion<T>(w,x,y,z);
}

template<typename T>
Quaternion<T> & Quaternion<T>::operator*=(const Quaternion<T> & other){
    const T w = ((*this)[0] * other[0]) - ((*this)[1] * other[1]) - ((*this)[2] * other[2]) - ((*this)[3] * other[3]);
    const T x = ((*this)[1] * other[0]) + ((*this)[0] * other[1]) + ((*this)[2] * other[3]) - ((*this)[3] * other[2]);
    const T y = ((*this)[2] * other[0]) + ((*this)[0] * other[2]) + ((*this)[3] * other[1]) - ((*this)[1] * other[3]);
    const T z = ((*this)[3] * other[0]) + ((*this)[0] * other[3]) + ((*this)[1] * other[2]) - ((*this)[2] * other[1]);
    this->set(w,x,y,z);
    return (*this);
}

template<typename T>
Quaternion<T> & Quaternion<T>::operator*=(const Vector3<T> & other){
    const T w = ((*this)[1] * other[0]) - ((*this)[2] * other[1]) - ((*this)[3] * other[2]);
    const T x = ((*this)[0] * other[0]) + ((*this)[2] * other[2]) - ((*this)[3] * other[1]);
    const T y = ((*this)[0] * other[1]) + ((*this)[3] * other[0]) - ((*this)[1] * other[2]);
    const T z = ((*this)[0] * other[2]) + ((*this)[1] * other[1]) - ((*this)[2] * other[0]);

    this->set(w,x,y,z);

    return (*this);
}

template<typename T>
Vector3<T> Quaternion<T>::forward() const {
    return rotateVec(Vector3<T>(0,0,1));
}

template<typename T>
Vector3<T> Quaternion<T>::back() const {
    return rotateVec(Vector3<T>(0,0,-1));
}

template<typename T>
Vector3<T> Quaternion<T>::down() const {
    return rotateVec(Vector3<T>(0,-1,0));
}

template<typename T>
Vector3<T> Quaternion<T>::up() const {
    return rotateVec(Vector3<T>(0,1,0));
}

template<typename T>
Vector3<T> Quaternion<T>::left() const {
    return rotateVec(Vector3<T>(-1,0,0));
}

template<typename T>
Vector3<T> Quaternion<T>::right() const {
    return rotateVec(Vector3<T>(1,0,0));
}

template<typename T>
Quaternion<T> & Quaternion<T>::toIdentity(){
    (*this)[0] = 1;
    (*this)[1] = 0;
    (*this)[2] = 0;
    (*this)[3] = 0;
    return(*this);
}

template<typename T,unsigned int I>
std::string MathUtil::matrixToStr(const Matrix<T,I> & mat){
    std::stringstream ss;
    ss.precision(3);
    ss << std::fixed;
    for (unsigned int i = 0;i < I;i++){
        ss << "|";
        for (unsigned int j = 0;j < I;j++){
            ss << mat[i][j] << "|";
        }
        ss << std::endl;
    }
    return ss.str();
}

template<typename T,unsigned int I>
std::string MathUtil::vectorToStr(const Vector<T,I> & vec){
    std::stringstream ss;
    ss.precision(3);
    ss << std::fixed;
    ss << "|";
    for (unsigned int i = 0;i < I;i++){
        ss << vec[i] << "|";
        ss << std::endl;
    }
    return ss.str();
}
