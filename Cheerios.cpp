//#include "Cheerios.h"
//#define PI 3.14159265
//
//Cheerios::Cheerios(double x, double z) {
//}
//Cheerios::~Cheerios() {}
//
//void Cheerios::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId) {
//
//	int angle = 0, angle1 = 0, i = 0, j = 0;
//	float x = 0, x1 = 0;
//	float y = 0, y1 = 0;
//
//	pushMatrix(MODEL);
//	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
//	scale(MODEL, 1.0, 1.0, 1.0);
//
//	//======= Exterior Elipse ======
//	while (i<40) {
//		x = 4.8 * cos((angle * PI) / 180);
//		y = 4.8 * sin((angle * PI) / 180);
//		load(shader, 0);    // Load table mesh
//		pushMatrix(MODEL);
//		translate(MODEL, 6.0 + x, 0.07f, 8.5 + y);
//		scale(MODEL, 1.0f, 1.0f, 1.0f);
//		rotate(MODEL, 0, 0, 0, 90);
//		renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
//		popMatrix(MODEL);
//		angle += 9;
//		i++;
//	}
//	//======= Interior Elipse ======
//	while (j < 36) {
//		x1 = 6.5 * cos((angle1 * PI) / 180);
//		y1 = 6.5 * sin((angle1 * PI) / 180);
//		load(shader, 0);    // Load table mesh
//		pushMatrix(MODEL);
//		translate(MODEL, 6.0 + x1, 0.07f, 8.5 + y1);
//		scale(MODEL, 1.0f, 1.0f, 1.0f);
//		rotate(MODEL, 0, 0, 0, 90);
//		renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 1);
//		popMatrix(MODEL);
//		angle1 += 10;
//		j++;
//	}
//
//	popMatrix(MODEL);
//}
//
