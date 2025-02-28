#ifndef Butter_h
#define Butter_h

#include "DynamicObject.h"

class Butter : public DynamicObject {
public:
    Butter(double x, double z);
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};

#endif /* Butter_h */
