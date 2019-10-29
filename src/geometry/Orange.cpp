#include "Orange.h"

Orange::Orange(double x, double z){
	Entity::setPosition(x, getPosition().getY() + 0.4, z);
    
    setAmbient(0.2f, 0.15f, 0.1f, 1.0f);
    setDiffuse(1.0f, 0.5f, 0.0f, 1.0f);
    setSpecular(1.0f, 0.5f, 0.0f, 1.0f);
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(100.0f);
    
    _mesh = new Mesh();
    _mesh->createSphere(1.0, 200);
    _mesh->createCube();
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
    
    setAmbient(0.1f, 0.7f, 0.1f, 1.0f);
    setDiffuse(0.5f, 0.9f, 0.5f, 1.0f);
    setSpecular(0.4f, 0.7f, 0.4f, 1.0f);
    _mesh->setMeshMaterial(1, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 0);
    
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
    rotate(MODEL, _angle, 0, 1, 0);
	rotate(MODEL, _rotationAngle,1, 0, 1);
	scale(MODEL, 0.5f, .5f, 0.5f);
    
    pushMatrix(MODEL);
    _mesh->renderMesh(shader,pvm_uniformId, vm_uniformId, normal_uniformId, 0);
    popMatrix(MODEL);
    
    glUniform1i(texMode_uniformId, 0);
    pushMatrix(MODEL);
    translate(MODEL, 0, 1.0, 0);
    scale(MODEL, 0.1, 0.1, 0.1);
    _mesh->loadMeshMaterial(shader, 1);
    _mesh->renderMesh(shader,pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
	popMatrix(MODEL);
}

void Orange::update(int delta_t){
    vec3 position = getPosition();
    
    
    if (1000 * _acceleration * delta_t > 1) {
        _rotationAngle = _rotationAngle + 1;
    } else {
        _rotationAngle = _rotationAngle + 1000000 * _acceleration * delta_t;

    }
    
    double angle = (_angle * 3.14) / 180;
    double acceleration = _acceleration;
    
    
    // restrict acceleration
    if (_acceleration > MAX_ACCELERATION) {
        _acceleration = MAX_ACCELERATION;
    }
    
    // update speed
    _speed = _speed + acceleration * delta_t;
    
   if (_speed > MAX_SPEED) {
        _speed = MAX_SPEED;
    }
    
    // update position
    setPosition(_position.getX() + _speed * sin(angle) * delta_t ,
                _position.getY(),
                _position.getZ() + _speed * cos(angle) * delta_t);
}
