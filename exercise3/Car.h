#ifndef Car_h
#define Car_h

#include "DynamicObject.h"
#define PI 3.14159265

class Car : public DynamicObject
{
protected:
    
public:
    Car();
    ~Car();
    void render(VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId);

};

#endif /* Car_h */
