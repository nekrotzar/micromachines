#ifndef Camera_h
#define Camera_h

#include "Entity.h"

class Camera{
protected:
    double _near;
    double _far;
    btVector3 _up;
    btVector3 _center;
    btVector3 _at;
public:
    Camera();
    ~Camera();
    virtual void update(float ratio);
    virtual void setAt(float x, float y, float z);
};

#endif /* Camera_h */
