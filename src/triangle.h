#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

typedef struct {
	int a;
	int b;
	int c;
} face_t;


typedef struct {
	vec2_t point[3];
} triangle_t;

#endif