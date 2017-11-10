#include "Points.h"

Points::Points() {
    setPosition(-9,7, 0.0);
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/hud/font.tga", 0);
}

void Points::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId)
{
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 1);
    
    load(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    scale(MODEL, 1.0, 1.0, 1.0);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
    popMatrix(MODEL);
    
    glDisable(GL_BLEND);
    
}
