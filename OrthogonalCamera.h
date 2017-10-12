#ifndef OrthogonalCamera_h
#define OrthogonalCamera_h

#include "Camera.h"
#include "AVTmathLib.h"

class OrthogonalCamera : public Camera{
protected:
    double _left;
    double _right;
    double _bottom;
    double _top;
public:
    OrthogonalCamera(double left, double right, double bottom, double top, double near, double far);
    ~OrthogonalCamera();
    void update(float ratio);
};

#endif /* OrthogonalCamera_h */
