#ifndef Object_h
#define Object_h

#include "Entity.h"
#include "vsShaderLib.h"
#include "basic_geometry.h"

extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];
extern float mNormal3x3[9];

class Object : public Entity{
protected:
    std::vector<struct MyMesh*> _meshes;
    
    btScalar _mass;
    
    /* Collision shape - volume of the object in space.
     * Interact with other shapes.
     * Define size when creating.*/
    btCollisionShape * _collisionShape;
    
    /* Motion state - object current position and rotation.
     * Pass the transform to the rendering system to display movement (update). Isolation
     */
    btDefaultMotionState * _motionState;
    
    /* Collision object - mantain object physical properties.
     * Obtain the transform. No deformation from collisions, opposed to soft bodies.
     * Require rigid body construction info -> physical properties like mass, friction, restutition ...
     */
    btRigidBody * _rigidBody;
    
public:
    Object(btScalar mass, btCollisionShape * shape, const btVector3& position, const btQuaternion& rotation );
    ~Object();
    btRigidBody * getRigidBody();
    btMotionState * getMotionState();
    void assignMesh(struct MyMesh* mesh);
    void load(VSShaderLib shader, int myId);
    void renderMesh(GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, int myId);
    virtual void update(int delta_t);
    virtual void render(btScalar* transform, VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId);
};


#endif /* Object_h */
