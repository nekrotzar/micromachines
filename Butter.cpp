#include "Butter.h"

Butter::Butter() {
    Object::setRadius(0.9);
    Object::setPosition(3.0, 0.0, 3.0);
}
Butter::~Butter() {}

void Butter::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId)
{

	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	//rotate(MODEL, getAngle(), 0, 0, 1);
	//scale(MODEL, 1.0, 1.0, 1.0);

	load(shader, 0);    // Load body mesh
	pushMatrix(MODEL);
	//translate(MODEL, 1.5, 0, 1.5);
	scale(MODEL, 1.0f, 0.8f, 0.6f);
	renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);

	popMatrix(MODEL);
}
