#pragma once
#include "vec4.h"
#include "bounding_box.h"
#include "color.h"

typedef struct triangle {
	vec4 origin;
	vec4 left;
	vec4 right;
	vec4 normal;
	bounding_box bb;
	color color;
}triangle;

int triangle_equals(triangle a, triangle b);
