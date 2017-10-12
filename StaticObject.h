#ifndef StaticObject_h
#define StaticObject_h

#include "Object.h"

class StaticObject : public Object{
public:
    StaticObject(btScalar mass, btCollisionShape * shape, const btVector3& position, const btQuaternion& rotation);
};

#endif /* StaticObject_h */
