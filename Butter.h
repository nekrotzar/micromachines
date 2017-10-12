#ifndef Butter_h
#define Butter_h

#include "StaticObject.h"

class Butter : public StaticObject
{
	protected:

	public:
    Butter(const btVector3& position, const btQuaternion& rotation);
    Butter(btScalar mass, btCollisionShape * shape, const btVector3& position, const btQuaternion& rotation);
    ~Butter();
		void render(btScalar * transform, VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId);
};

#endif /* Butter_h */
