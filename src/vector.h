#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	float x;
	float y;
} vec2_t;

typedef struct {
	float x;
	float y;
	float z;
} vec3_t;

typedef struct {
	vec3_t position;
	vec3_t rotation;
	float fov_angle;
} camera_t;

// TODO: add function to manipulate vectors

vec3_t vec3_rotate_x(vec3_t, float);
vec3_t vec3_rotate_y(vec3_t, float);
vec3_t vec3_rotate_z(vec3_t, float);

float vec2_len(vec2_t);
float vec3_len(vec3_t);

vec2_t vec2_add(vec2_t, vec2_t);
vec3_t vec3_add(vec3_t, vec3_t);

vec2_t vec2_sub(vec2_t v, vec2_t w);
vec3_t vec3_sub(vec3_t v, vec3_t w);

vec2_t vec2_mult(vec2_t, float);
vec3_t vec3_mult(vec3_t, float);

vec2_t vec2_div(vec2_t, float);
vec3_t vec3_div(vec3_t, float);

vec3_t vec3_cross_prod(vec3_t, vec3_t);
void vec3_normalize(vec3_t*);
float vec3_dot(vec3_t a, vec3_t b);

#endif