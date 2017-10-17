#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "LightSource.h"

class DirectionalLight : public LightSource {
protected:
public:
    void draw(VSShaderLib shader, GLint lPos_uniformId);
};



#endif /* DirectionalLight_h */
