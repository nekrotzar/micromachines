#include "Butter.h"

Butter::Butter(double x, double z){
    Object::setRadius(0.9);
    Entity::setPosition(x, 0.0, z);
    
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/butter.tga", 0);
}

void Butter::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 2);
    
    // Load body mesh
	load(shader, 0);
	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	scale(MODEL, 1.0f, 0.8f, 0.6f);
	renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);
}
