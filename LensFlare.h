#ifndef LensFlare_h
#define LensFlare_h

#include <stdio.h>
#include "Object.h"


class LensFlare : public Object {
protected:
    float relativePositions[4] = {0.7f, 0.8f, 0.9f, 1.0f};
public:
    LensFlare();
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
    void render_flare(VSShaderLib shader, int lx, int ly, int cx, int cy, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};

#endif /* LensFlare_h */

