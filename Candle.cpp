#include "Candle.h"

Candle::Candle(double height){
    _height = height;
}
Candle::~Candle(){}

void Candle::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId){
    
    load(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
    popMatrix(MODEL);
}
