#include "Candle.h"

Candle::Candle(){
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/candle.tga", 0);
}

void Candle::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId){
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 2);
    
    load(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
    
    glUniform1i(texMode_uniformId, 0);
    
    load(shader, 0);
    translate(MODEL, 0.0f, 1.5f, 0.0f);
    scale(MODEL, 0.05f, 0.25f, 0.05f);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
    
    popMatrix(MODEL);
}
