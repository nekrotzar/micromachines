#include "Candle.h"

Candle::Candle(double height){
    _height = height;
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, "textures/candle.tga", 0);
}
Candle::~Candle(){}

void Candle::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId){
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 2);
    
    
    load(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
    popMatrix(MODEL);
}
