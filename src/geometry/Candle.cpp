#include "Candle.h"

Candle::Candle(){
    
    setAmbient(0.8f, 0.8f, 0.9f, 1.0f);
    setDiffuse(1.0f, 1.0f, 0.9f, 1.0f);
    setSpecular(1.0f, 1.0f, 0.5f, 1.0f);
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(10.0f);
    
    _mesh = new Mesh();
    _mesh->createCylinder(3, .3f, 50);
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
    
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/candle.tga", 0);
}

void Candle::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    
    glUniform1i(texMode_uniformId, 2);
    _mesh->loadMeshMaterial(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    _mesh->renderMesh(shader,pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
    
    glUniform1i(texMode_uniformId, 2);
    _mesh->loadMeshMaterial(shader, 0);
    translate(MODEL, 0.0f, 1.5f, 0.0f);
    scale(MODEL, 0.05f, 0.25f, 0.05f);
    _mesh->renderMesh(shader,pvm_uniformId, vm_uniformId, normal_uniformdId, 0);

    popMatrix(MODEL);
}
