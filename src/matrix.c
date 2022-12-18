#include "matrix.h"

mat4_t mat4_identity(void) 
{
    mat4_t m = { {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    } };


	return m;
};


mat4_t mat4_create_scale(float sx, float sy, float sz) 
{
	mat4_t m = mat4_identity();
	m.m[0][0] = sx;
	m.m[1][1] = sy;
	m.m[2][2] = sz;

	return m;
};


vec4_t mat4_mult_vec4(mat4_t mat, vec4_t vec)
{
	vec4_t result;

	result.x = vec.x * mat.m[0][0] + vec.y * mat.m[0][1] + vec.z * mat.m[0][2] + vec.w * mat.m[0][3];
	result.y = vec.x * mat.m[1][0] + vec.y * mat.m[1][1] + vec.z * mat.m[1][2] + vec.w * mat.m[1][3];
	result.z = vec.x * mat.m[2][0] + vec.y * mat.m[2][1] + vec.z * mat.m[2][2] + vec.w * mat.m[2][3];
	result.w = vec.x * mat.m[3][0] + vec.y * mat.m[3][1] + vec.z * mat.m[3][2] + vec.w * mat.m[3][3];

	return result;
};


void print_mat4(mat4_t mat) 
{
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++ )
        {
            printf("%.5f ", mat.m[r][c]);
        }
        printf("\n");
        
    }
    printf("\n");
}
