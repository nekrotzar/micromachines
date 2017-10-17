#ifndef PointLight_h
#define PointLight_h

#include "LightSource.h"

class PointLight : public LightSource {
    protected:
    public:
    PointLight(vec3 position);
    ~PointLight();
    void draw(VSShaderLib shader, GLint lPos_uniformId, int num);
};


#endif /* PointLight_h */
