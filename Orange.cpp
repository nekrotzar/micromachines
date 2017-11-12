#include "Orange.h"

Orange::Orange(double x, double z){
	Entity::setPosition(x, getPosition().getY() + 0.4, z);
    
    setAmbient(0.2f, 0.15f, 0.1f, 1.0f);
    setDiffuse(1.0f, 0.5f, 0.0f, 1.0f);
    setSpecular(1.0f, 0.5f, 0.0f, 1.0f);
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(100.0f);
    
    _mesh = new Mesh();
    _mesh->createSphere(1.0, 70);
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
    
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/orange.tga", 0);
}

void Orange::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 2);
    
    _mesh->loadMeshMaterial(shader, 0);
	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	rotate(MODEL, 90.0, 0.0, 0.0, 1);
	scale(MODEL, 0.5f, .5f, 0.5f);
    _mesh->renderMesh(shader,pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);
}
