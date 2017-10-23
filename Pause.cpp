#include "Pause.h"

Pause::Pause() {
    
    setPosition(0.0, 0.0, 0.0);
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, "hud/pause.tga", 0);
 
}

Pause::~Pause(){}

void Pause::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId) {

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
        glUniform1i(texMode_uniformId, 1);
        
        load(shader, 0);
        pushMatrix(MODEL);
        translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
        scale(MODEL, 5.0, 5.0, 5.0);
        rotate(MODEL, -90, 0, 1, 0);
        renderMesh(pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
        popMatrix(MODEL);

}
