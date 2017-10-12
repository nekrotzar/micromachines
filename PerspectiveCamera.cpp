#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float near, float far)
{
    _fov = fov;
    _near = near;
    _far = far;
}

PerspectiveCamera::~PerspectiveCamera(){}

void PerspectiveCamera::update(float ratio)
{
    loadIdentity(PROJECTION);
    perspective(_fov, ratio, _near, _far);
}
