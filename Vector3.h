#ifndef Vector3_h
#define Vector3_h

#include <math.h>

class vec3{
protected:
    double _x;
    double _y;
    double _z;
public:
    vec3();
    vec3(double,double,double);
    ~vec3();
    bool operator==(const vec3& vec);
    vec3 operator=(const vec3& vec);
    vec3 operator*(const vec3& vec);
    vec3 operator+(const vec3& vec);
    vec3 operator-(const vec3& vec);
    vec3 operator-();
    vec3 operator*(double num);
    vec3 operator+(double num);
    vec3 cross(const vec3& vec);
    double dot(const vec3& vec);
    vec3 normalise();
    double length();
    double getX();
    double getY();
    double getZ();
    void set(double,double,double);
};

#endif /* Vector3_h */
