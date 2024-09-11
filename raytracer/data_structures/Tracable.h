#pragma once
#include "ray.h"
#include "vec4_math.h"
#include "trace_result.h"
#include "simple_triangle_mesh.h"
#include "float.h"
#include "math.h"
#include "vec4_math.h"
#include "kd_tree.h"

typedef enum enum_tracables  {triangle_traceable_type,simple_triangle_mesh_traceable_type, traceable_kd_tree_type, traceable_node_type,enum_tracables_count }enum_tracables;

typedef struct Tracable {
	enum_tracables type;
	void* model;
	trace_result (*trace)(ray,struct Tracable*);
}Tracable;

trace_result triangle_trace(ray, triangle*);
trace_result simple_triangle_mesh_trace(ray,simple_triangle_mesh*);
trace_result kd_tree_trace(ray r, kd_tree* tree);
	
Tracable traceable_kd_tree_wrapper(kd_tree t);
Tracable tri_wrapper(triangle t);
Tracable mesh_wrapper(simple_triangle_mesh m);
typedef struct node {
	Tracable cont;
	matrix m;
	matrix m_inverse;
	int change_dir;
}node;
 
trace_result node_trace(ray r, node* temp);
Tracable tracable_wrap(Tracable T, matrix m,int);
#define to_tracable(X) _Generic((X), \
				triangle: tri_wrapper, \
				simple_triangle_mesh: mesh_wrapper, \
				)(X)