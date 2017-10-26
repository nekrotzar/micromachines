#ifndef PointLight_h
#define PointLight_h

#include "LightSource.h"

class PointLight : public LightSource {
protected:
    float _linear, _constant, _quadratic;
public:
    PointLight(vec3 position);
    ~PointLight();
    float getConstantAttenuation();
    float getLinearAttenuation();
    float getQuadraticAttenuation();
    

    void draw(VSShaderLib shader, int num);
};


#endif /* PointLight_h */
