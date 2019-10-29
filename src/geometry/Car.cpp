#include "Car.h"

Car::Car(){
    DynamicObject::setAngle(90);
    DynamicObject::setSpeed(0.0);
    Entity::setPosition(1.4, 0.0, 9.8);
    Object::setRadius(1.15);
    
    setAmbient(0.0f, 0.0f, 0.0f, 1.0f);
    setDiffuse(1.0f, 0.1f, 0.1f, 1.0f);
    setSpecular(1.0f, 0.5f, 0.5f, 1.0f);
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(150.0f);
    
    _mesh = new Mesh();
    _mesh->createObject("data/models/Avent.obj");
}

void Car::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId){
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(texMode_uniformId, 0);
    
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    rotate(MODEL, getAngle() + 90, 0, 1, 0);
    scale(MODEL, 0.25, 0.25, 0.25);
    _mesh->renderMeshRecursive(shader,pvm_uniformId, vm_uniformId, normal_uniformdId, _mesh->getScene(), _mesh->getScene()->mRootNode);
    popMatrix(MODEL);
}

void Car::update(int delta_t){
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

