#ifndef DynamicObject_h
#define DynamicObject_h

#include "Object.h"

class DynamicObject : public Object {
private:
    double _angle = 0.0;
    double _speed = 0.0;
public:
    DynamicObject();
    double getAngle();
    double getSpeed();
    void setAngle(double angle);
    void setSpeed(double speed);
};

#endif /* DynamicObject_h */
