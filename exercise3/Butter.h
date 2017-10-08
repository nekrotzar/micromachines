#ifndef Butter_h
#define Butter_h

#include "DynamicObject.h"

class Butter : public DynamicObject 
{
	protected:

	public:
		Butter();
		~Butter();
		void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId);
};

#endif /* Butter_h */
