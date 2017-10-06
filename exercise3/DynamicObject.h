#ifndef DynamicObject_h
#define DynamicObject_h

#include "Object.h"

class DynamicObject : public Object
{
private:
    double _angle;
public:
    DynamicObject();
    double getAngle();
};

#endif /* DynamicObject_h */
