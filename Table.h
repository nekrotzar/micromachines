#ifndef Table_h
#define Table_h

#include "StaticObject.h"

class Table : public StaticObject
{
protected:

public:
    Table(const btVector3& position);
    ~Table();
	void render(btScalar * transform, VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId);
};

#endif /* Table_h */
