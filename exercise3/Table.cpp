#include "Table.h"

Table::Table() {}
Table::~Table() {}

void Table::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId) {

	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	//rotate(MODEL, 30.0, 0, 0, 1);
	scale(MODEL, 1.0, 1.0, 1.0);

	load(shader, 0);    // Load table mesh
	pushMatrix(MODEL);
	translate(MODEL, -1.5, -0.17, -1.5);
	scale(MODEL, 15.0f, 0.1f, 15.0f);
	renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);

	popMatrix(MODEL);
}

