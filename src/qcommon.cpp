#pragma once
#include "qcommon.h"
#define _USE_MATH_DEFINES // for M_PI
#include <cfloat>
#include <cmath>

float	AngleMod(float a) {
	a = (360.0 / 65536) * ((int)(a*(65536 / 360.0)) & 65535);
	return a;
}


/*
=================
AngleNormalize360

returns angle normalized to the range [0 <= angle < 360]
=================
*/
float AngleNormalize360(float angle) {
	return (360.0 / 65536) * ((int)(angle * (65536 / 360.0)) & 65535);
}

/*
=================
AngleNormalize180

returns angle normalized to the range [-180 < angle <= 180]
=================
*/
float AngleNormalize180(float angle) {
	angle = AngleNormalize360(angle);
	if (angle > 180.0) {
		angle -= 360.0;
	}
	return angle;
}



/*
=================
AnglesToAxis
=================
*/
void AnglesToAxis(const vec3_t angles, vec3_t axis[3]) {
	float		angle;
	static float		sr, sp, sy, cr, cp, cy;
	// static to help MS compiler fp bugs

	angle = angles[YAW] * (M_PI * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[PITCH] * (M_PI * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[ROLL] * (M_PI * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	axis[0][0] = cp * cy;
	axis[0][1] = cp * sy;
	axis[0][2] = -sp;

	axis[1][0] = (sr*sp*cy + cr * -sy);
	axis[1][1] = (sr*sp*sy + cr * cy);
	axis[1][2] = sr * cp;

	axis[2][0] = (cr*sp*cy + -sr * -sy);
	axis[2][1] = (cr*sp*sy + -sr * cy);
	axis[2][2] = cr * cp;
}

void MatToQuat
(
	float srcMatrix[3][3],
	float destQuat[4]
)

{
	double  	trace, s;
	int     	i, j, k;
	static int 	next[3] = { Y_IND, Z_IND, X_IND };

	trace = srcMatrix[X_IND][X_IND] + srcMatrix[Y_IND][Y_IND] + srcMatrix[Z_IND][Z_IND];

	if (trace > 0.0)
	{
		s = sqrt(trace + 1.0);
		destQuat[W_IND] = s * 0.5;
		s = 0.5 / s;

		destQuat[X_IND] = (srcMatrix[Z_IND][Y_IND] - srcMatrix[Y_IND][Z_IND]) * s;
		destQuat[Y_IND] = (srcMatrix[X_IND][Z_IND] - srcMatrix[Z_IND][X_IND]) * s;
		destQuat[Z_IND] = (srcMatrix[Y_IND][X_IND] - srcMatrix[X_IND][Y_IND]) * s;
	}
	else
	{
		i = X_IND;
		if (srcMatrix[Y_IND][Y_IND] > srcMatrix[X_IND][X_IND])
			i = Y_IND;
		if (srcMatrix[Z_IND][Z_IND] > srcMatrix[i][i])
			i = Z_IND;
		j = next[i];
		k = next[j];

		s = sqrt((srcMatrix[i][i] - (srcMatrix[j][j] + srcMatrix[k][k])) + 1.0);
		destQuat[i] = s * 0.5;

		s = 0.5 / s;

		destQuat[W_IND] = (srcMatrix[k][j] - srcMatrix[j][k]) * s;
		destQuat[j] = (srcMatrix[j][i] + srcMatrix[i][j]) * s;
		destQuat[k] = (srcMatrix[k][i] + srcMatrix[i][k]) * s;
	}
}
void EulerToQuat
(
	float ang[3],
	float q[4]
)

{
	float mat[3][3];
	int *i;

	i = (int *)ang;
	if (!i[0] && !i[1] && !i[2])
	{
		q[0] = 0;
		q[1] = 0;
		q[2] = 0;
		q[3] = 1.0f;
	}
	else
	{
		AnglesToAxis(ang, mat);
		MatToQuat(mat, q);
	}
}


void MatrixToEulerAngles
(
	const float mat[3][3],
	vec3_t ang
)

{
	double theta;
	double cp;
	double sp;

	sp = mat[0][2];

	// cap off our sin value so that we don't get any NANs
	if (sp > 1.0)
	{
		sp = 1.0;
	}
	if (sp < -1.0)
	{
		sp = -1.0;
	}

	theta = -asin(sp);
	cp = cos(theta);

	if (cp > 8192 * FLT_EPSILON)
	{
		ang[0] = theta * 180 / M_PI;
		ang[1] = atan2(mat[0][1], mat[0][0]) * 180 / M_PI;
		ang[2] = atan2(mat[1][2], mat[2][2]) * 180 / M_PI;
	}
	else
	{
		ang[0] = theta * 180 / M_PI;
		ang[1] = -atan2(mat[1][0], mat[1][1]) * 180 / M_PI;
		ang[2] = 0;
	}
}


void QuatToMat
(
	const float q[4],
	float m[3][3]
)

{
	float wx, wy, wz;
	float xx, yy, yz;
	float xy, xz, zz;
	float x2, y2, z2;

	x2 = q[X_IND] + q[X_IND];
	y2 = q[Y_IND] + q[Y_IND];
	z2 = q[Z_IND] + q[Z_IND];

	xx = q[X_IND] * x2;
	xy = q[X_IND] * y2;
	xz = q[X_IND] * z2;

	yy = q[Y_IND] * y2;
	yz = q[Y_IND] * z2;
	zz = q[Z_IND] * z2;

	wx = q[W_IND] * x2;
	wy = q[W_IND] * y2;
	wz = q[W_IND] * z2;

	m[0][0] = 1.0 - (yy + zz);
	m[0][1] = xy - wz;
	m[0][2] = xz + wy;

	m[1][0] = xy + wz;
	m[1][1] = 1.0 - (xx + zz);
	m[1][2] = yz - wx;

	m[2][0] = xz - wy;
	m[2][1] = yz + wx;
	m[2][2] = 1.0 - (xx + yy);
}