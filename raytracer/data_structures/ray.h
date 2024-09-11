#pragma once
#include "vec4.h"
typedef struct ray{
	vec4 origin;
	vec4 dir;
	int x;
	int y;
}ray;
int ray_equals(ray a, ray b);