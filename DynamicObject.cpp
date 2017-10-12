#include "DynamicObject.h"

DynamicObject::DynamicObject(btScalar mass, btCollisionShape * shape, const btVector3& position, const btQuaternion& rotation) : Object(mass, shape, position, rotation) {
}

void DynamicObject::setSpeed(double speed) {
    _speed = speed;
}

void DynamicObject::setAngle(double angle){
    _angle = angle;
}

void DynamicObject::setAcceleration(double acceleration){
    _acceleration = acceleration;
}

double DynamicObject::getSpeed() {
    return _speed;
}

double DynamicObject::getAngle() {
    return _angle;
}

void DynamicObject::update(int delta_t){
    _speed = _speed + _acceleration * delta_t;
    _rigidBody->setLinearVelocity(btVector3(_speed * cos(_angle) * delta_t, _rigidBody->getLinearVelocity().getY(), _speed * sin(_angle) * delta_t));
    _rigidBody->setAngularFactor(_angle);
    
    //getRotation().setRotation(btVector3(0,1,0),_angle);
    
    
}

