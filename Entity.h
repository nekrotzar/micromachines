#ifndef Entity_h
#define Entity_h

#include "Vector3.h"
#include "AVTmathLib.h"

#include <btBulletDynamicsCommon.h>

extern struct MyMesh mesh[];

class Entity {
protected:
    btVector3 * _position;
    btQuaternion * _rotation;
public:
    Entity();
    ~Entity();
    btVector3 getPosition();
    btQuaternion getRotation();
    void setPosition(double, double, double);
    void setPosition(const btVector3& position);
    void setRotation(double, double, double, double);
    void setRotation(const btQuaternion& rotation);
};

#endif /* Entity_h */
