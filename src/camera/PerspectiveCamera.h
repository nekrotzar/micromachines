#ifndef PerspectiveCamera_h
#define PerspectiveCamera_h

#include "Camera.h"
#include "AVTmathLib.h"

class PerspectiveCamera : public Camera
{
protected:
    float _fov;
public:
    PerspectiveCamera(float fov, float near, float far);
    ~PerspectiveCamera();
    void update(float ratio);
};

#endif /* PerspectiveCamera_h */
