#ifndef Entity_h
#define Entity_h

#include "Vector3.h"
#include "AVTmathLib.h"

class Entity {
protected:
    vec3 _position;
public:
    Entity();
    ~Entity();
    vec3 getPosition();
    void setPosition(double, double, double);
    void setPosition(const vec3& vec);
};

#endif /* Entity_h */
