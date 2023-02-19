#pragma once
// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

typedef float vec2_t[2];
typedef float vec3_t[3];
typedef float vec4_t[4];
typedef float vec5_t[5];

#define X_IND 0
#define Y_IND 1
#define Z_IND 2
#define W_IND 3

float	AngleMod(float a);

float AngleNormalize360(float angle);
float AngleNormalize180(float angle);

void AnglesToAxis(const vec3_t angles, vec3_t axis[3]);

void MatToQuat(float srcMatrix[3][3], float destQuat[4]);

void EulerToQuat(float ang[3], float q[4]);


void MatrixToEulerAngles(const float mat[3][3], vec3_t ang);

void QuatToMat(const float q[4],float m[3][3]);