#include "Cheerios.h"

Cheerios::Cheerios(double x, double z) {
	Entity::setPosition(x, getPosition().getY(), z);
}
Cheerios::~Cheerios() {}

void Cheerios::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId) {	

	load(shader, 0);
	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	scale(MODEL, 1.1, 1.1, 1.1);
	renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);

}

