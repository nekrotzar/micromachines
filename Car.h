#ifndef Car_h
#define Car_h

#include "DynamicObject.h"

#define MAX_SPEED 0.05

class Car : public DynamicObject
{
protected:
    btSliderConstraint * m_forkSlider;
public:
    Car(const btVector3& position, const btQuaternion& rotation);
    Car(btScalar mass, btCollisionShape * shape, const btVector3& position, const btQuaternion& rotation);
    ~Car();
    void render(btScalar * transform, VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId);
};

#endif /* Car_h */
