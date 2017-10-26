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
    loadIdentity(PROJECTION);
    
    if(ratio > 1){
        ortho(_bottom * ratio, _top * ratio, _bottom, _top , _near, _far);
    } else if (ratio < 1) {
        ortho(_left, _right, _right / ratio, _left / ratio, _near, _far);
    }
}
