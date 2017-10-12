#include "Butter.h"

Butter::Butter(const btVector3& position, const btQuaternion& rotation) : StaticObject(1.0f, new btBoxShape(btVector3(0.5,0.5,0.5)), position, rotation) {}

Butter::Butter(btScalar mass, btCollisionShape * shape, const btVector3& position, const btQuaternion& rotation) : StaticObject(mass, shape, position, rotation) {
}


Butter::~Butter() {}

void Butter::render(btScalar * transform, VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId)
{
    load(shader, 0);    // Load body mesh

    pushMatrix(MODEL);
    multMatrix(MODEL, transform);
    translate(MODEL, -0.5, -0.5, -0.5);

    scale(MODEL, 1.0f, 1.0f, 1.0f);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);

}
