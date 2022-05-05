#include "vector.h"
#include <math.h>

vec3_t vec3_rotate_x(vec3_t v, float angle) 
{
	vec3_t rotated_vector = {
		.x = v.x,
		.y = v.y * cos(angle) - v.z * sin(angle),
		.z = v.y * sin(angle) + v.z * cos(angle),
	};

	return rotated_vector;
};

vec3_t vec3_rotate_z(vec3_t v, float angle) 
{
	vec3_t rotated_vector = {
		.x = v.x * cos(angle) - v.y * sin(angle),
		.y = v.x * sin(angle) + v.y * cos(angle),
		.z = v.z
	};

	return rotated_vector;
};

vec3_t vec3_rotate_y(vec3_t v, float angle) 
{
	vec3_t rotated_vector = {
		.x = v.x * cos(angle) - v.z * sin(angle),
		.y = v.y,
		.z = v.x * sin(angle) + v.z * cos(angle)
	};

	return rotated_vector;
};

float vec2_len(vec2_t v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}

float vec3_len(vec3_t v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

vec2_t vec2_add(vec2_t v, vec2_t w)
{
	vec2_t result = {.x = v.x + w.x, .y = v.y + w.y};
	return result;
}

vec3_t vec3_add(vec3_t v, vec3_t w)
{
	vec3_t result = {.x = v.x + w.x, .y = v.y + w.y, .z = v.z + w.z};
	return result;
}

vec2_t vec2_sub(vec2_t v, vec2_t w)
{
	vec2_t result = {.x = v.x - w.x, .y = v.y - w.y};
	return result;
}

vec3_t vec3_sub(vec3_t v, vec3_t w)
{
	vec3_t result = {.x = v.x - w.x, .y = v.y - w.y, .z = v.z - w.z};
	return result;
}

vec2_t vec2_mult(vec2_t v, float a) 
{
	vec2_t res = {.x = v.x * a, .y = v.y * a};
	return res;
}
vec3_t vec3_mult(vec3_t v, float a)
{
	vec3_t res = {.x = v.x * a, .y = v.y * a, .z = v.z * a};
	return res;
}

vec2_t vec2_div(vec2_t v, float a) 
{
	vec2_t res = {.x = v.x / a, .y = v.y / a};
	return res;
}
vec3_t vec3_div(vec3_t v, float a)
{
	vec3_t res = {.x = v.x / a, .y = v.y / a, .z = v.z / a};
	return res;
}

vec3_t vec3_cross_prod(vec2_t a, vec2_t a) 
{
	vec3_t res = {
		.x = a.y * b.z - a.z * b.y, 
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	};

	return res;

}