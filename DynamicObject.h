#ifndef DynamicObject_h
#define DynamicObject_h

#include "Object.h"

class DynamicObject : public Object
{
private:
    double _angle = 0.0;
    double _speed;
    
public:
    DynamicObject();
    void setSpeed(double speed);
    double getSpeed();
    void setAngle(double angle);
    double getAngle();
};

#endif /* DynamicObject_h */
