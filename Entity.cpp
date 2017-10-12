#include "Entity.h"

Entity::Entity(){
    _position = new btVector3(0.0f, 0.0f, 0.0f);
    _rotation = new btQuaternion();
}
Entity::~Entity(){
    delete _position;
}

btVector3 Entity::getPosition(){
    return * _position;
}

btQuaternion Entity::getRotation(){
    return * _rotation;
}

void Entity::setPosition(double x, double y, double z){
    _position->setValue(x, y, z);
}

void Entity::setPosition(const btVector3& position){
    _position->setValue(position.getX(), position.getY(), position.getZ());
}

void Entity::setRotation(double x, double y, double z, double angle){
    _rotation->setRotation(btVector3(x,y,z), btSin(angle));
}

void Entity::setRotation(const btQuaternion& rotation){
    _rotation->setRotation(rotation.getAxis(), rotation.getAngle());
}
