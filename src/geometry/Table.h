#ifndef Table_h
#define Table_h

#include "StaticObject.h"

class Table : public StaticObject{
public:
	Table();
    void draw_tile(VSShaderLib shader,GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId , vec3 position, vec3 scale);
	void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};

#endif /* Table_h */
