#ifndef Orange_h
#define Orange_h

#include "DynamicObject.h"

class Orange : public DynamicObject
{
protected:

public:
    Orange(btScalar mass, btCollisionShape* shape, const btVector3& position, const btQuaternion& rotation);
    Orange(const btVector3& position, const btQuaternion& rotation);
	~Orange();
	void render(btScalar * transform, VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId);
};

#endif /* Orange_h */
