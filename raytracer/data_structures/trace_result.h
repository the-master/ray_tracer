#pragma once
#include "vec4.h"

#include "triangle.h"
#include "color.h"
typedef struct trace_result{
	int is_hit;
	triangle target;
	vec4 hit_location;
	color color;
	double u;
	double v;
	double distance;
}trace_result;
