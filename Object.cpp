#include "Object.h"

void Object::assignMesh(struct MyMesh * mesh)
{
    _meshes.push_back(mesh);
}

void Object::renderMesh(GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, int myId)
{
    computeDerivedMatrix(PROJ_VIEW_MODEL);
    glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
    glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
    computeNormalMatrix3x3();
    glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);
    
    glBindVertexArray(_meshes[myId]->vao);
    glDrawElements(_meshes[myId]->type, _meshes[myId]->numIndexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
}

void Object::render(VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId){}

void Object::load(VSShaderLib shader, int myId){
    GLint loc;
    
    loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
    glUniform4fv(loc, 1, _meshes[myId]->mat.ambient);
    loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
    glUniform4fv(loc, 1, _meshes[myId]->mat.diffuse);
    loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
    glUniform4fv(loc, 1, _meshes[myId]->mat.specular);
    loc = glGetUniformLocation(shader.getProgramIndex(), "mat.shininess");
    glUniform1f(loc,_meshes[myId]->mat.shininess);
    
}
