#ifndef Car_h
#define Car_h

#include "DynamicObject.h"

class Car : public DynamicObject {
public:
    Car();
    void render(VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
    void update(int delta_t);
};

#endif /* Car_h */
