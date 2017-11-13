#ifndef DynamicObject_h
#define DynamicObject_h

#include "Object.h"

class DynamicObject : public Object {
private:
    double _angle = 0.0;
    double _speed = 0.0;
    double _acceleration = 0.0;
public:
    DynamicObject();
    double getAngle();
    double getSpeed();
    void setAngle(double angle);
    void setSpeed(double speed);
    void setAcceleration(double acceleration);
    void update(int delta_t);
};

#endif /* DynamicObject_h */