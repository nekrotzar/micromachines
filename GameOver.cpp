#include "GameOver.h"

GameOver::GameOver() {
    
    setPosition(8.0, 10.0, -8.0);
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, "hud/gameover.tga", 0);
    
}

GameOver::~GameOver(){}

void GameOver::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId) {
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 1);
    
    load(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    scale(MODEL, 15.0, 0.1, 15.0);
    rotate(MODEL, -90, 0, 1, 0);
    renderMesh(pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
    popMatrix(MODEL);
    
}
