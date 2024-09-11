#pragma once
#include "arraylist_triangle.h"
#include "trace_result.h"
#include "ray.h"
#include "float.h"
#include "vec4_math.h"
#include "bounding_box.h"
typedef struct simple_triangle_mesh {
	arraylist_triangle content;
	bounding_box bb;
}simple_triangle_mesh;
simple_triangle_mesh simple_triangle_mesh_new();
trace_result simple_triangle_mesh_trace(ray);
bounding_box calculate_bb(simple_triangle_mesh*);