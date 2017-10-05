#include "OrthogonalCamera.h"

OrthogonalCamera::OrthogonalCamera(double left, double right, double bottom, double top, double near, double far){
    _left = left;
    _right = right;
    _bottom = bottom;
    _top = top;
    _near = near;
    _far = far;
}

OrthogonalCamera::~OrthogonalCamera(){}

void OrthogonalCamera::update(float ratio){
    lookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);
    
    if(ratio > 1){
        ortho(-5 * ratio, 5 * ratio, -5, 5, -10, 10);
    } else {
        ortho(-5, 5, -5 / ratio, 5 / ratio, -10, 10);
    }
}
