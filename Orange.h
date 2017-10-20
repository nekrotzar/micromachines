#ifndef Orange_h
#define Orange_h
#define PI 3.14159265

#include "DynamicObject.h"

class Orange : public DynamicObject
{
protected:

public:
	Orange(double x, double z);
	~Orange();
	void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};

#endif /* Orange_h */
