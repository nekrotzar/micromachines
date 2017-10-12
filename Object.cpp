#include "Object.h"

Object::Object(btScalar mass, btCollisionShape* shape, const btVector3& position, const btQuaternion& rotation) : _mass(mass), _collisionShape(shape) {
    
    // Give box an initial position
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(position);
    transform.setRotation(rotation);
    
    // Create motion state
    _motionState = new btDefaultMotionState(transform);
    
    // Calculate the local inertia
    btVector3 localInertia(0,0,0);
    
    if (mass != 0.0f)
        _collisionShape->calculateLocalInertia(_mass, localInertia);
    
    // Create rigid body construction info with mass, motion state and shape.
    btRigidBody::btRigidBodyConstructionInfo rbCInfo(_mass, _motionState, _collisionShape, localInertia);
    
    // Create rigid body
    _rigidBody = new btRigidBody(rbCInfo);
}

Object::~Object(){

    delete _rigidBody;
    delete _motionState;
    delete _collisionShape;
    
    for (auto &meshi : _meshes) {
        delete meshi;
    }
}

void Object::assignMesh(struct MyMesh * mesh)
{
    _meshes.push_back(mesh);
}

btRigidBody* Object::getRigidBody(){
    return _rigidBody;
}

btMotionState* Object::getMotionState(){
    return _motionState;
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

void Object::render(btScalar* transform, VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId){}

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

void Object::update(int delta_t){
}
