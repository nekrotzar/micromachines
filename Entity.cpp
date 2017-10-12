#include "Entity.h"

Entity::Entity(){
    setPosition(0, 0, 0);
}
Entity::~Entity(){}

vec3 Entity::getPosition()
{
    return _position;
}

void Entity::setPosition(double x, double y, double z)
{
    _position.set(x, y, z);
}

void Entity::setPosition(const vec3& position)
{
    _position = position;
}
