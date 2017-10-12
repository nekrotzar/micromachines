#include "Orange.h"

Orange::Orange(double x, double z)
{
	Entity::setPosition(x, getPosition().getY(), z);
}
Orange::~Orange() {}

void Orange::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId) {
	load(shader, 0);
	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	rotate(MODEL, getAngle(), 0, 0, 1);
	
	//scale(MODEL, 1.0, 1.0, 1.0);

	    // Load orange mesh
	//pushMatrix(MODEL);
	//translate(MODEL, 4.0f, 0.5f, 1.0f);
	scale(MODEL, 0.5f, .5f, 0.5f);
	//rotate(MODEL, 90, 0, 0, 90);
	renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	//popMatrix(MODEL);

	popMatrix(MODEL);
}
