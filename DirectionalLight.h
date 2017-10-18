#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "LightSource.h"

class DirectionalLight : public LightSource {
protected:
public:
    DirectionalLight(vec3 direction);
    void draw(VSShaderLib shader, int num);
};



#endif /* DirectionalLight_h */
