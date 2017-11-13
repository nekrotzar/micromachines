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

void DynamicObject::setAngle(double angle){
    _angle = angle;
}

void DynamicObject::setAcceleration(double acceleration){
    _acceleration = acceleration;
}

void DynamicObject::update(int delta_t) {
    
    vec3 position = getPosition();
    double angle = (_angle * 3.14) / 180;
    double acceleration = _acceleration;
    
    // update speed
    _speed = _speed + acceleration * delta_t;
    
    if (_speed < -0.0025 ) {
        _speed = -0.0025;
    } else if (_speed > 0.005) {
        _speed = 0.005;
    }
    
    // update position
    setPosition(_position.getX() + _speed * sin(angle) * delta_t ,
                _position.getY(),
                _position.getZ() + _speed * cos(angle) * delta_t);
}
