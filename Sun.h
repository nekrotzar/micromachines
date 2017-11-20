#ifndef Sun_h
#define Sun_h

#include "Object.h"
#include "l3DBillboard.h"

class Sun : public Object {
public:
    Sun();
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId,float camPos[], int type);
};

#endif /* Sun_h */
