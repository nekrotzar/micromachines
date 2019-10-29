#define false	0
#define true	1

#define FLOOR(a)	((float)((long)(a) - ((a)<0.0)))
#define FLOOR2(a)	(((temp)=(a))>0.0?((long)(temp) - 1L):long(temp)

/* Computes the inner product between vectors v and q */ 

#define mathsInnerProduct(v,q) \
	((v)[0] * (q)[0] + \
	(v)[1] * (q)[1] + \
	(v)[2] * (q)[2])	


/* a = b x c */

#define mathsCrossProduct(a,b,c) \
	(a)[0] = (b)[1] * (c)[2] - (c)[1] * (b)[2]; \
	(a)[1] = (b)[2] * (c)[0] - (c)[2] * (b)[0]; \
	(a)[2] = (b)[0] * (c)[1] - (c)[0] * (b)[1];


/* vector a = b - c, where b and c represent points*/

#define mathsVector(a,b,c) \
	(a)[0] = (b)[0] - (c)[0];	\
	(a)[1] = (b)[1] - (c)[1];	\
	(a)[2] = (b)[2] - (c)[2];
	


/* Intersection routines */
int mathsRayIntersectsTriangle(float *p, float *d, float *v0, float *v1, float *v2);

/* Interpolation routines */

double mathsCosineInterpolation(float x,float v1,float v2);
double mathsCosineInterpolation2D(float x,float y,float v0,float v1, float v2, float v3);



#define M11	 0.0	
#define M12	 1.0
#define M13	 0.0
#define M14	 0.0
#define M21	-0.5
#define M22	 0.0
#define M23	 0.5
#define M24	 0.0
#define M31	 1.0
#define M32	-2.5
#define M33	 2.0
#define M34	-0.5
#define M41	-0.5
#define M42	 1.5
#define M43	-1.5
#define M44	 0.5

double mathsCatmullRomSpline(float x, float v1,float v2,float v3,float v4);

inline void mathsNormalize(float *v) {
	float d = (sqrt((v[0]*v[0]) + (v[1]*v[1]) + (v[2]*v[2])));
	v[0] = v[0] / d;
	v[1] = v[1] / d;
	v[2] = v[2] / d;
}
