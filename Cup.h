#ifndef Cup_h
#define Cup_h

#include "Object.h"

class Cup : public Object {
public:
    Cup();
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};

#endif /* Cup_h */
