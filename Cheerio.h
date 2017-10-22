#ifndef Cheerio_h
#define Cheerio_h

#include "StaticObject.h"

class Cheerio : public StaticObject
{
protected:

public:
	Cheerio(double x, double z);
	~Cheerio();
	void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};

#endif /* Cheerio_h */