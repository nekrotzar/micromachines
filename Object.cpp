#include "Object.h"

float * Object::getAmbient(){return _ambient;}
float * Object::getDiffuse(){return _diffuse;}
float * Object::getSpecular(){return _specular;}
float * Object::getEmissive(){return _emissive;}
float Object::getShininess(){return _shininess;}

void Object::setAmbient(float r, float g, float b, float a){
    _ambient[0] = r;
    _ambient[1] = g;
    _ambient[2] = b;
    _ambient[3] = a;
}
void Object::setDiffuse(float r, float g, float b, float a){
    _diffuse[0] = r;
    _diffuse[1] = g;
    _diffuse[2] = b;
    _diffuse[3] = a;
}
void Object::setSpecular(float r, float g, float b, float a){
    _specular[0] = r;
    _specular[1] = g;
    _specular[2] = b;
    _specular[3] = a;
}
void Object::setEmissive(float r, float g, float b, float a){
    _emissive[0] = r;
    _emissive[1] = g;
    _emissive[2] = b;
    _emissive[3] = a;
}
void Object::setShininess(float shininess){
    _shininess = shininess;
}

void Object::render(VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId){}

void Object::setRadius(double radius){
    _radius = radius;
}

double Object::getRadius(){
    return _radius;
}
