#include "DynamicObject.h"

DynamicObject::DynamicObject(){
}

void DynamicObject::setSpeed(double speed){
    _speed = speed;
}

double DynamicObject::getSpeed(){
    return _speed;
}

double DynamicObject::getAngle(){
    return _angle;
}

double DynamicObject::getAcceleration(){
    return _acceleration;
}

void DynamicObject::setAngle(double angle){
    _angle = angle;
}

void DynamicObject::setAcceleration(double acceleration){
    _acceleration = acceleration;
}

void DynamicObject::update(int delta_t) {}
