#ifndef Ground_h
#define Ground_h

#include "Object.h"

class Ground : public Object {
public:
    Ground();
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};


#endif /* Ground_h */
