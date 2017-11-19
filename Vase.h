#ifndef Vase_h
#define Vase_h

#include "Object.h"
#include "l3DBillboard.h"
#include <string.h>
#include <stdlib.h>

class Vase : public Object {
public:
    Vase();
    void renderBillboard(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId, float camPos[], int type);
};


#endif /* Vase_h */
