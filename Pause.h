#ifndef Pause_h
#define Pause_h

#include "Object.h"

class Pause : public Object {
public:
    Pause();
    ~Pause();
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};

#endif /* Pause_h */
