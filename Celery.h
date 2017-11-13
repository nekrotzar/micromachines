#ifndef Celery_h
#define Celery_h

#include "Object.h"
#include "l3DBillboard.h"

class Celery : public Object {
public:
    Celery();
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};


#endif /* Celery_h */
