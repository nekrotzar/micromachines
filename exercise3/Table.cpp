#include "Table.h"
#define PI 3.14159265

Table::Table() {}
Table::~Table() {}

void Table::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId) {

    int angle = 0, angle1 = 0, i = 0, j = 0;
    float x = 0, x1 = 0;
    float y = 0, y1 = 0;
    
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
    
    //======= Exterior Elipse ======
    while (i<40) {
        x = 5.0 * cos((angle * PI) / 180);
        y = 5.0 * sin((angle * PI) / 180);
        load(shader, 1);    // Load table mesh
        pushMatrix(MODEL);
        translate(MODEL, 6.0 + x, 0.07f, 6.0 + y);
        scale(MODEL, 1.0f, 1.0f, 1.0f);
        rotate(MODEL, 0, 0, 0, 90);
        renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
        popMatrix(MODEL);
        angle += 9;
        i++;
    }
    //======= Interior Elipse ======
    while (j < 36) {
        x1 = 6.0 * cos((angle1 * PI) / 180);
        y1 = 6.0 * sin((angle1 * PI) / 180);
        load(shader, 1);    // Load table mesh
        pushMatrix(MODEL);
        translate(MODEL, 6.0 + x1, 0.07f, 6.0 + y1);
        scale(MODEL, 1.0f, 1.0f, 1.0f);
        rotate(MODEL, 0, 0, 0, 90);
        renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
        popMatrix(MODEL);
        angle1 += 10;
        j++;
    }

	popMatrix(MODEL);
}

