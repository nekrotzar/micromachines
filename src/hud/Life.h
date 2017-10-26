#ifndef Life_h
#define Life_h

#include "Object.h"

class Life : public Object {
public:
    Life();
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};

#endif /* Life_h */
