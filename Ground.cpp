#include "Ground.h"

Ground::Ground() {
    Entity::setPosition(0.0, 0.0, 0.0);
    
    setAmbient(0.1f, 0.1f, 0.1f, 1.0f);
    setDiffuse(0.1f, 0.5f, 0.1f, 1.0f);
    setSpecular(0.1f, 0.1f, 0.1f, 1.0f);
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(100.0f);
    
    _mesh = new Mesh();
    _mesh->createQuad(30, 30);
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
    
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/wood.tga", 0);
}

void Ground::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    
    glUniform1i(texMode_uniformId, 1);
    
    // Load body mesh
    _mesh->loadMeshMaterial(shader, 0);
    pushMatrix(MODEL);
    rotate(MODEL, 90, -1, 0, 0 );
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    
    _mesh->renderMesh(shader ,pvm_uniformId,  vm_uniformId, normal_uniformdId, 0);
    popMatrix(MODEL);
    
}
