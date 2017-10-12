#include "Car.h"

Car::Car(const btVector3& position, const btQuaternion& rotation) : DynamicObject(10.0f, new btBoxShape(btVector3(0.5f,0.5f,0.5f)), position, rotation){
    _rigidBody->setAngularFactor(btVector3(0,1,0));
}

Car::Car(btScalar mass, btCollisionShape * shape, const btVector3& position, const btQuaternion& rotation) : DynamicObject(mass, shape, position, rotation){}

Car::~Car(){}

void Car::render(btScalar * transform, VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformId){
    
    //pushMatrix(MODEL);
    //translate(MODEL, getPosition().getX() - 0.5, getPosition().getY() - 0.5 + 0.07, getPosition().getZ() - 0.5);
    //rotate(;

    pushMatrix(MODEL);
    multMatrix(MODEL, transform);
    translate(MODEL, -0.5, -0.5, -0.5);

    scale(MODEL, 1.0f, 1.0f, 1.0f);
    
    load(shader, 0);    // Load body mesh
    pushMatrix(MODEL);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
    popMatrix(MODEL);
    
    load(shader, 1);    // Load wheel mesh
    pushMatrix(MODEL);
    translate(MODEL, 0, 0.07f, 1);
    scale(MODEL,1.0f, 1.0f, 1.0f);
    rotate(MODEL, 90, 0, 0, 1);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    pushMatrix(MODEL);
    translate(MODEL, 1, 0.07f, 1);
    scale(MODEL,1.0f, 1.0f, 1.0f);
    rotate(MODEL, 90, 0, 0, 1);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    pushMatrix(MODEL);
    translate(MODEL, 1, 0.07f, 0);
    scale(MODEL,1.0f, 1.0f, 1.0f);
    rotate(MODEL, 90, 0, 0, 1);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    pushMatrix(MODEL);
    translate(MODEL, 0, 0.07f, 0);
    scale(MODEL,1.0f, 1.0f, 1.0f);
    rotate(MODEL, 90, 0, 0, 90);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
   popMatrix(MODEL);
}

