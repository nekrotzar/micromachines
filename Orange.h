#ifndef Orange_h
#define Orange_h
#define PI 3.14159265

#include "DynamicObject.h"

#define MAX_SPEED 0.01
#define MAX_ACCELERATION 0.0005

class Orange : public DynamicObject {
public:
    double _rotationAngle = 0.0;
public:
	Orange(double x, double z);
	void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
    void update(int delta_t);
};

#endif /* Orange_h */
