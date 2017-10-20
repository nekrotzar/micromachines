#ifndef Candle_h
#define Candle_h

#include "StaticObject.h"

class Candle : public StaticObject {
protected:
    double _height;
public:
    Candle(double height);
    ~Candle();
    void render(VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
};

#endif /* Candle_h */
