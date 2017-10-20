#include "Car.h"

Car::Car(){
    DynamicObject::setAngle(90);
    DynamicObject::setSpeed(0.0);
    Entity::setPosition(1.4, 0.0, 9.8);
    Object::setRadius(1.15);
}
Car::~Car(){}

void Car::render(VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId){
    
    glUniform1i(texMode_uniformId, 0);
    
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    rotate(MODEL, getAngle(), 0, 1, 0);
    scale(MODEL, 0.45, 0.4, 0.65);
    
    load(shader, 1);    // Load wheel mesh
    pushMatrix(MODEL);
    translate(MODEL, 0.6f, 0.07f, 0.4f);
    scale(MODEL,1.0f, 1.0f, 1.0f);
    rotate(MODEL, 90, 0, 0, 90);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    pushMatrix(MODEL);
    translate(MODEL, -0.6f, 0.07f, 0.4f);
    scale(MODEL,1.0f, 1.0f, 1.0f);
    rotate(MODEL, 90, 0, 0, 90);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    pushMatrix(MODEL);
    translate(MODEL, 0.6f, 0.07f, -0.4f);
    scale(MODEL,1.0f, 1.0f, 1.0f);
    rotate(MODEL, 90, 0, 0, 90);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    pushMatrix(MODEL);
    translate(MODEL, -0.6, 0.07f, -0.4f);
    scale(MODEL,1.0f, 1.0f, 1.0f);
    rotate(MODEL, 90, 0, 0, 90);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    load(shader, 0);    // Load body mesh
    pushMatrix(MODEL);
    translate(MODEL, -0.5 , 0, -0.5);
    scale(MODEL, 1.0f, 1.0f, 1.0f);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
    popMatrix(MODEL);

    popMatrix(MODEL);
}

