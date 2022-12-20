# ifndef MATRIX_H
# define MATRIX_H

#include "vector.h"

typedef struct {
	float m[4][4];
} mat4_t;


mat4_t mat4_identity(void);
mat4_t mat4_create_scale(float sx, float sy, float sz);
mat4_t mat4_create_translation(float tx, float ty, float tz);
mat4_t mat4_create_rotation_x(float x);
mat4_t mat4_create_rotation_y(float x);
mat4_t mat4_create_rotation_z(float x);


vec4_t mat4_mult_vec4(mat4_t m, vec4_t v);

// utils

void print_mat4(mat4_t);

# endif