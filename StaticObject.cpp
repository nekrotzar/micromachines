#include "StaticObject.h"

StaticObject::StaticObject(btScalar mass, btCollisionShape * shape, const btVector3& position, const btQuaternion& rotation) : Object(mass, shape, position, rotation){}
