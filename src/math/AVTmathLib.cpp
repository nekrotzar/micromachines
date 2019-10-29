/* --------------------------------------------------
AVT Math Lib 
 *
 * based on VSMathLib - Very Simple Matrix Library frm Lighthouse3D
 *
 *
 *
 * Full documentation at 
 * http://www.lighthouse3d.com/very-simple-libs

ALL resulting matrices are in COLUMN ORDER

Author: João Madeiras Pereira
----------------------------------------------------*/

#include "AVTmathLib.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#define M_PI       3.14159265358979323846f
#endif

static inline float 
DegToRad(float degrees) 
{ 
	return (float)(degrees * (M_PI / 180.0f));
};

/// Matrix stacks for all matrix types
std::vector<float *> mMatrixStack[COUNT_MATRICES];

/// The storage for matrices
float mMatrix[COUNT_MATRICES][16];
float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

/// The normal matrix
float mNormal3x3[9];

// glPushMatrix implementation
void pushMatrix(MatrixTypes aType) {

	float *aux = (float *)malloc(sizeof(float) * 16);
	memcpy(aux, mMatrix[aType], sizeof(float) * 16);
	mMatrixStack[aType].push_back(aux);
}

// glPopMatrix implementation
void popMatrix(MatrixTypes aType) {

	if (mMatrixStack[aType].size()-1 >= 0) {
		float *m = mMatrixStack[aType][mMatrixStack[aType].size()-1];
		memcpy(mMatrix[aType], m, sizeof(float) * 16);
		mMatrixStack[aType].pop_back();
		free(m);
	}
}

// glLoadIdentity implementation
void loadIdentity(MatrixTypes aType)
{
	setIdentityMatrix(mMatrix[aType]);
}

// glMultMatrix implementation
void multMatrix(MatrixTypes aType, float *aMatrix)
{
	
	float *a, *b, res[16];
	a = mMatrix[aType];
	b = aMatrix;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res[j*4 + i] = 0.0f;
			for (int k = 0; k < 4; ++k) {
				res[j*4 + i] += a[k*4 + i] * b[j*4 + k]; 
			}
		}
	}
	memcpy(mMatrix[aType], res, 16 * sizeof(float));
}

// aux function resMat = resMat * aMatrix
void multMatrix(float *resMat, float *aMatrix)
{
	
	float *a, *b, res[16];
	a = resMat;
	b = aMatrix;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res[j*4 + i] = 0.0f;
			for (int k = 0; k < 4; ++k) {
				res[j*4 + i] += a[k*4 + i] * b[j*4 + k]; 
			}
		}
	}
	memcpy(a, res, 16 * sizeof(float));
}


// glLoadMatrix implementation
void loadMatrix(MatrixTypes aType, float *aMatrix)
{
	memcpy(mMatrix[aType], aMatrix, 16 * sizeof(float));
}


// glTranslate implementation with matrix selection
void translate(MatrixTypes aType, float x, float y, float z) 
{
	float mat[16];

	setIdentityMatrix(mat);
	mat[12] = x;
	mat[13] = y;
	mat[14] = z;

	multMatrix(aType,mat);
}

// glScale implementation with matrix selection
void scale(MatrixTypes aType, float x, float y, float z) 
{
	float mat[16];

	setIdentityMatrix(mat,4);
	mat[0] = x;
	mat[5] = y;
	mat[10] = z;

	multMatrix(aType,mat);
}

// glRotate implementation with matrix selection
void rotate(MatrixTypes aType, float angle, float x, float y, float z)
{
	float mat[16];
	float v[3];

	v[0] = x;
	v[1] = y;
	v[2] = z;

	float radAngle = DegToRad(angle);
	float co = cos(radAngle);
	float si = sin(radAngle);
	normalize(v);
	float x2 = v[0]*v[0];
	float y2 = v[1]*v[1];
	float z2 = v[2]*v[2];

//	mat[0] = x2 + (y2 + z2) * co; 
	mat[0] = co + x2 * (1 - co);// + (y2 + z2) * co; 
	mat[4] = v[0] * v[1] * (1 - co) - v[2] * si;
	mat[8] = v[0] * v[2] * (1 - co) + v[1] * si;
	mat[12]= 0.0f;
	   
	mat[1] = v[0] * v[1] * (1 - co) + v[2] * si;
//	mat[5] = y2 + (x2 + z2) * co;
	mat[5] = co + y2 * (1 - co);
	mat[9] = v[1] * v[2] * (1 - co) - v[0] * si;
	mat[13]= 0.0f;
	   
	mat[2] = v[0] * v[2] * (1 - co) - v[1] * si;
	mat[6] = v[1] * v[2] * (1 - co) + v[0] * si;
//	mat[10]= z2 + (x2 + y2) * co;
	mat[10]= co + z2 * (1 - co);
	mat[14]= 0.0f;
	   
	mat[3] = 0.0f;
	mat[7] = 0.0f;
	mat[11]= 0.0f;
	mat[15]= 1.0f;

	multMatrix(aType,mat);
}

// gluLookAt implementation
void lookAt(float xPos, float yPos, float zPos,
					float xLook, float yLook, float zLook,
					float xUp, float yUp, float zUp)
{
	float dir[3], right[3], up[3];

	up[0] = xUp;	up[1] = yUp;	up[2] = zUp;

	dir[0] =  (xLook - xPos);
	dir[1] =  (yLook - yPos);
	dir[2] =  (zLook - zPos);
	normalize(dir);

	crossProduct(dir,up,right);
	normalize(right);

	crossProduct(right,dir,up);
	normalize(up);

	float m1[16],m2[16];

	m1[0]  = right[0];
	m1[4]  = right[1];
	m1[8]  = right[2];
	m1[12] = 0.0f;

	m1[1]  = up[0];
	m1[5]  = up[1];
	m1[9]  = up[2];
	m1[13] = 0.0f;

	m1[2]  = -dir[0];
	m1[6]  = -dir[1];
	m1[10] = -dir[2];
	m1[14] =  0.0f;

	m1[3]  = 0.0f;
	m1[7]  = 0.0f;
	m1[11] = 0.0f;
	m1[15] = 1.0f;

	setIdentityMatrix(m2,4);
	m2[12] = -xPos;
	m2[13] = -yPos;
	m2[14] = -zPos;

	multMatrix(VIEW, m1);
	multMatrix(VIEW, m2);
}

// gluPerspective implementation
void perspective(float fov, float ratio, float nearp, float farp)
{
	float projMatrix[16];

	float f = 1.0f / tan (fov * (M_PI / 360.0f));

	setIdentityMatrix(projMatrix,4);

	projMatrix[0] = f / ratio;
	projMatrix[1 * 4 + 1] = f;
	projMatrix[2 * 4 + 2] = (farp + nearp) / (nearp - farp);
	projMatrix[3 * 4 + 2] = (2.0f * farp * nearp) / (nearp - farp);
	projMatrix[2 * 4 + 3] = -1.0f;
	projMatrix[3 * 4 + 3] = 0.0f;

	multMatrix(PROJECTION, projMatrix);
}


// glOrtho implementation
void ortho(float left, float right, 
			float bottom, float top, 
			float nearp, float farp)
{
	float m[16];

	setIdentityMatrix(m,4);

	m[0 * 4 + 0] = 2 / (right - left);
	m[1 * 4 + 1] = 2 / (top - bottom);	
	m[2 * 4 + 2] = -2 / (farp - nearp);
	m[3 * 4 + 0] = -(right + left) / (right - left);
	m[3 * 4 + 1] = -(top + bottom) / (top - bottom);
	m[3 * 4 + 2] = -(farp + nearp) / (farp - nearp);

	multMatrix(PROJECTION, m);
}


// glFrustum implementation
void frustum(float left, float right, 
			float bottom, float top, 
			float nearp, float farp)
{
	float m[16];

	setIdentityMatrix(m,4);

	m[0 * 4 + 0] = 2 * nearp / (right-left);
	m[1 * 4 + 1] = 2 * nearp / (top - bottom);
	m[2 * 4 + 0] = (right + left) / (right - left);
	m[2 * 4 + 1] = (top + bottom) / (top - bottom);
	m[2 * 4 + 2] = - (farp + nearp) / (farp - nearp);
	m[2 * 4 + 3] = -1.0f;
	m[3 * 4 + 2] = - 2 * farp * nearp / (farp-nearp);
	m[3 * 4 + 3] = 0.0f;

	multMatrix(PROJECTION, m);
}

// returns a pointer to the requested matrix
float *get(MatrixTypes aType)
{
	return mMatrix[aType];
}
/*
// returns a pointer to the requested matrix
float *get(ComputedMatrixTypes aType)
{
	
			computeDerivedMatrix(aType);
			return mCompMatrix[aType]; 

	
}
*/

// sets the square matrix mat to the identity matrix,
// size refers to the number of rows (or columns)
void setIdentityMatrix( float *mat, int size) {

	// fill matrix with 0s
	for (int i = 0; i < size * size; ++i)
			mat[i] = 0.0f;

	// fill diagonal with 1s
	for (int i = 0; i < size; ++i)
		mat[i + i * size] = 1.0f;
}

// Compute res = M * point
void multMatrixPoint(MatrixTypes aType, float *point, float *res) {

	for (int i = 0; i < 4; ++i) {

		res[i] = 0.0f;
	
		for (int j = 0; j < 4; j++) {
		
			res[i] += point[j] * mMatrix[aType][j*4 + i];
		} 
	}
}

// res = a cross b;
void  crossProduct( float *a, float *b, float *res) {

	res[0] = a[1] * b[2]  -  b[1] * a[2];
	res[1] = a[2] * b[0]  -  b[2] * a[0];
	res[2] = a[0] * b[1]  -  b[0] * a[1];
}

// returns a . b
float dotProduct(float *a, float *b) {

	float res = a[0] * b[0]  +  a[1] * b[1]  +  a[2] * b[2];

	return res;
}

// Normalize a vec3
void normalize(float *a) {

	float mag = sqrt(a[0] * a[0]  +  a[1] * a[1]  +  a[2] * a[2]);

	a[0] /= mag;
	a[1] /= mag;
	a[2] /= mag;
}

// res = b - a
void subtract(float *a, float *b, float *res) {

	res[0] = b[0] - a[0];
	res[1] = b[1] - a[1];
	res[2] = b[2] - a[2];
}

// res = a + b
void add(float *a, float *b, float *res) {

	res[0] = b[0] + a[0];
	res[1] = b[1] + a[1];
	res[2] = b[2] + a[2];
}

// returns |a|
float length(float *a) {

	return(sqrt(a[0] * a[0]  +  a[1] * a[1]  +  a[2] * a[2]));

}
// Computes derived matrices
void computeDerivedMatrix(ComputedMatrixTypes aType) {
	
	memcpy(mCompMatrix[VIEW_MODEL], mMatrix[VIEW], 16 * sizeof(float));
	multMatrix(mCompMatrix[VIEW_MODEL], mMatrix[MODEL]);

	if (aType == PROJ_VIEW_MODEL) {
		memcpy(mCompMatrix[PROJ_VIEW_MODEL], mMatrix[PROJECTION], 16 * sizeof(float));
		multMatrix(mCompMatrix[PROJ_VIEW_MODEL], mCompMatrix[VIEW_MODEL]);
	}
}

// It calculates only the PVM matrix. Just an auxiliary function to be used in billboad demo: it implies that VIEW_MODEL was already calculated
void computeDerivedMatrix_PVM(){   
	
	memcpy(mCompMatrix[PROJ_VIEW_MODEL], mMatrix[PROJECTION], 16 * sizeof(float));
	multMatrix(mCompMatrix[PROJ_VIEW_MODEL], mCompMatrix[VIEW_MODEL]);
}


// computes the derived normal matrix - should be used after computeDerivedMatrix
void computeNormalMatrix3x3() {

	float mMat3x3[9];

	mMat3x3[0] = mCompMatrix[VIEW_MODEL][0];
	mMat3x3[1] = mCompMatrix[VIEW_MODEL][1];
	mMat3x3[2] = mCompMatrix[VIEW_MODEL][2];

	mMat3x3[3] = mCompMatrix[VIEW_MODEL][4];
	mMat3x3[4] = mCompMatrix[VIEW_MODEL][5];
	mMat3x3[5] = mCompMatrix[VIEW_MODEL][6];

	mMat3x3[6] = mCompMatrix[VIEW_MODEL][8];
	mMat3x3[7] = mCompMatrix[VIEW_MODEL][9];
	mMat3x3[8] = mCompMatrix[VIEW_MODEL][10];

	float det, invDet;

	det = mMat3x3[0] * (mMat3x3[4] * mMat3x3[8] - mMat3x3[5] * mMat3x3[7]) +
		  mMat3x3[1] * (mMat3x3[5] * mMat3x3[6] - mMat3x3[8] * mMat3x3[3]) +
		  mMat3x3[2] * (mMat3x3[3] * mMat3x3[7] - mMat3x3[4] * mMat3x3[6]);

	invDet = 1.0f/det;

	mNormal3x3[0] = (mMat3x3[4] * mMat3x3[8] - mMat3x3[5] * mMat3x3[7]) * invDet;
	mNormal3x3[1] = (mMat3x3[5] * mMat3x3[6] - mMat3x3[8] * mMat3x3[3]) * invDet;
	mNormal3x3[2] = (mMat3x3[3] * mMat3x3[7] - mMat3x3[4] * mMat3x3[6]) * invDet;
	mNormal3x3[3] = (mMat3x3[2] * mMat3x3[7] - mMat3x3[1] * mMat3x3[8]) * invDet;
	mNormal3x3[4] = (mMat3x3[0] * mMat3x3[8] - mMat3x3[2] * mMat3x3[6]) * invDet;
	mNormal3x3[5] = (mMat3x3[1] * mMat3x3[6] - mMat3x3[7] * mMat3x3[0]) * invDet;
	mNormal3x3[6] = (mMat3x3[1] * mMat3x3[5] - mMat3x3[4] * mMat3x3[2]) * invDet;
	mNormal3x3[7] = (mMat3x3[2] * mMat3x3[3] - mMat3x3[0] * mMat3x3[5]) * invDet;
	mNormal3x3[8] = (mMat3x3[0] * mMat3x3[4] - mMat3x3[3] * mMat3x3[1]) * invDet;
}