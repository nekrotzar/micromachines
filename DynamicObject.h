#ifndef DynamicObject_h
#define DynamicObject_h

#include "Object.h"

class DynamicObject : public Object
{
private:
    double _angle = 0.0;
    double _speed = 0.0;
    double _acceleration = 0.0;
    
public:
    DynamicObject(btScalar mass, btCollisionShape * shape, const btVector3& position, const btQuaternion& rotation);
    void setSpeed(double speed);
    void setAngle(double angle);
    void setAcceleration(double acceleration);
    double getSpeed();
    double getAngle();
    void update(int delta_t);
};

#endif /* DynamicObject_h */
