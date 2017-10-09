#include "DynamicObject.h"

DynamicObject::DynamicObject() {
    
}

void DynamicObject::setSpeed(double speed) {
    _speed = speed;
}

double DynamicObject::getSpeed() {
    return _speed;
}

double DynamicObject::getAngle() {
    return _angle;
}

void DynamicObject::setAngle(double angle) {
    _angle = angle;
}
