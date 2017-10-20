#include "Orange.h"

Orange::Orange(double x, double z)
{
	Entity::setPosition(x, getPosition().getY() + 0.4, z);

    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, "textures/orange.tga", 0);
}
Orange::~Orange() {}

void Orange::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId) {
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 2);
    
	load(shader, 0);
	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	rotate(MODEL, 90.0, 0.0, 0.0, 1);
	scale(MODEL, 0.5f, .5f, 0.5f);
	renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);
}
