#include "Vector3.h"

vec3::vec3(){
    vec3(0,0,0);
}

vec3::vec3(double x, double y, double z){
    _x = x;
    _y = y;
    _z = z;
}

vec3::~vec3(){}

bool vec3::operator==(const vec3& vec){
    return (_x == vec._x && _y == vec._y && _z == vec._z);
}

vec3 vec3::operator=(const vec3& vec){
    _x = vec._x;
    _y = vec._y;
    _z = vec._z;
    return *this;
}

vec3 vec3::operator*(const vec3& vec){
    return vec3(_x * vec._x, _y * vec._y, _z * vec._z);
}

vec3 vec3::operator+(const vec3& vec){
    return vec3(_x + vec._x, _y + vec._y, _z -+vec._z);
}

vec3 vec3::operator-(const vec3& vec){
        return vec3(_x - vec._x, _y - vec._y, _z - vec._z);
}

vec3 vec3::operator-(){
    return vec3(-_x,-_y,-_z);
}

vec3 vec3::operator*(double scalar){
    return vec3(_x * scalar, _y * scalar, _z * scalar);
}

vec3 vec3::operator+(double scalar){
    return vec3(_x + scalar, _y + scalar, _z + scalar);
}

/**
 Calculates the cross product between two vectors.
 @param vec Right side vector of cross product operation.
 @return The resulting vector of the cross product.
 */
vec3 vec3::cross(const vec3& vec){
    return vec3(_y * vec._z - _z * vec._y, _z * vec._x - _x * vec._z, _x * vec._y - _y * vec._x);
}

/**
 Calculates the dot product between two vectors.
 @param vec Right side vector of dot product operation.
 @return The value of the dot product.
 */
double vec3::dot(const vec3& vec){
    return (_x * vec._x + _y * vec._y + _z * vec._z);
}

/**
 Calculates the normalised vector.
 @return The normalised vector.
 */
vec3 vec3::normalise(){
    return vec3(_x / length(), _y / length(), _z / length() );
}

/**
 Calculates the length of a vector.
 @return The length of the vector.
 */
double vec3::length(){
    return abs(sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2)));
}

/**
 Get the x coordinate of the vector.
 @return The x value of the vector.
 */
double vec3::getX(){
    return _x;
}

/**
 Get the y coordinate of the vector.
 @return The y value of the vector.
 */
double vec3::getY(){
    return _y;
}

/**
 Get the z coordinate of the vector.
 @return The z value of the vector.
 */
double vec3::getZ(){
    return _z;
}

void vec3::set(double x, double y, double z){
    _x = x;
    _y = y;
    _z = z;
}
