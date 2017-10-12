#include "Orange.h"

Orange::Orange(btScalar mass, btCollisionShape* shape, const btVector3& position, const btQuaternion& rotation) : DynamicObject(mass, shape, position, rotation){}

Orange::Orange(const btVector3& position, const btQuaternion& rotation) : DynamicObject(2.0f, new btSphereShape(1.0f), position, rotation){}

Orange::~Orange() {}

void Orange::render(btScalar * transform, VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId){
    load(shader, 0);
    pushMatrix(MODEL);
    multMatrix(MODEL, transform);
	renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);
}
