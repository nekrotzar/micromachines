#ifndef Table_h
#define Table_h

#include "StaticObject.h"

class Table : public StaticObject
{
protected:

public:
	Table();
	~Table();
	void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId);
};

#endif /* Table_h */
