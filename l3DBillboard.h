void l3dBillboardGetRightVector(float *right);
void l3dBillboardGetUpRightVector(float *up, float *right);
void l3dBillboardLocalToWorld(float *cam, float *worldPos);
void l3dBillboardCylindricalBegin(float *cam, float *worldPos);
void l3dBillboardSphericalBegin(float *cam, float *worldPos);
void BillboardCheatSphericalBegin();
void BillboardCheatCylindricalBegin();
void BillboardEnd(float *m);
