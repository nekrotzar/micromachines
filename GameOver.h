#ifndef GameOver_h
#define GameOver_h

#include "Object.h"

class GameOver : public Object {
public:
    GameOver();
    ~GameOver();
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};


#endif /* GameOver_h */
