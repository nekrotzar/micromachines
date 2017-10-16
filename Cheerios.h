#ifndef Cheerios_h
#define Cheerios_h

#include "StaticObject.h"

class Cheerios : public StaticObject
{
protected:

public:
	Cheerios(double x, double z);
	~Cheerios();
	void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId);
};

#endif /* Cheerios_h */
