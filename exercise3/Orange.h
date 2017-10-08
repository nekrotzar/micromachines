#ifndef Orange_h
#define Orange_h

#include "DynamicObject.h"

class Orange : public DynamicObject
{
protected:

public:
	Orange();
	~Orange();
	void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId);
};

#endif /* Orange_h */
