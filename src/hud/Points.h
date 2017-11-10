#ifndef Points_h
#define Points_h

#include "Object.h"

class Points : public Object {
public:
    Points();
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};

#endif /* Points_h */
