#include "Life.h"

Life::Life() {
    setPosition(-10, -10.0, 0.0);
    
    setAmbient(1.0f, 1.0f, 1.0f, 1.0f );
    setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    setSpecular(0.0f, 0.0f, 0.0f, 1.0f );
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(10.0f);
    
    _mesh = new Mesh();
    _mesh->createCube();
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
    
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/hud/life.tga", 0);
}

void Life::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId) {
    glEnable(GL_BLEND);
    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 3);
    
    _mesh->loadMeshMaterial(shader, 0);

    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    scale(MODEL, 1.0, 1.0, 1.0);
    _mesh->renderMesh(shader,pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
    popMatrix(MODEL);
    glDisable(GL_BLEND);
    
}
