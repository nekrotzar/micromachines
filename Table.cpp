#include "Table.h"
#define PI 3.14159265

Table::Table(const btVector3& position) : StaticObject(0, new btBoxShape(btVector3(20.0f, 1.0f, 20.0f)), position, btQuaternion(0,0,0,1)){}

Table::~Table() {}

void Table::render(btScalar * transform, VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId) {
    
    int angle = 0, angle1 = 0, i = 0, j = 0;
    float x = 0, x1 = 0;
    float y = 0, y1 = 0;
    
    pushMatrix(MODEL);
    multMatrix(MODEL, transform);
    translate(MODEL, -10, -1.0f, -10.0f);

    load(shader, 0);    // Load table mesh
	pushMatrix(MODEL);

	scale(MODEL, 40.0f, 2.0f, 40.0f);
	renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);
    
    //======= Exterior Elipse ======
    while (i<40) {
        x = 4.8 * cos((angle * PI) / 180);
        y = 4.8 * sin((angle * PI) / 180);
        load(shader, 1);    // Load table mesh
        pushMatrix(MODEL);
        translate(MODEL, 0, 1.0f, 0.0f);
        translate(MODEL, 8 + x, 0.07f + 1, 8 + y);
        scale(MODEL, 1.0f, 1.0f, 1.0f);
        rotate(MODEL, 0, 0, 0, 90);
        renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
        popMatrix(MODEL);
        angle += 9;
        i++;
    }
    //======= Interior Elipse ======
    while (j < 36) {
        x1 = 6.5 * cos((angle1 * PI) / 180);
        y1 = 6.5 * sin((angle1 * PI) / 180);
        load(shader, 1);    // Load table mesh
        pushMatrix(MODEL);
        translate(MODEL, 0, 1.0f, 0.0f);
        translate(MODEL, 8 + x1, 0.07f + 1, 8 + y1);
        scale(MODEL, 1.0f, 1.0f, 1.0f);
        rotate(MODEL, 0, 0, 0, 90);
        renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
        popMatrix(MODEL);
        angle1 += 10;
        j++;
    }
    
    popMatrix(MODEL);
}
