#include "simple_triangle_mesh.h"
simple_triangle_mesh simple_triangle_mesh_new() {
	simple_triangle_mesh rv;
	rv.content = new_arraylist_triangle();
	return rv;
}
bounding_box calculate_bb(simple_triangle_mesh* mesh) {
	bounding_box rv = { 
		.BL = {DBL_MAX,DBL_MAX,DBL_MAX,1},
		.TR = {-DBL_MAX,-DBL_MAX,-DBL_MAX,1}
	};
	for (int i = 0; i < mesh->content.n; i++) {
		rv.BL = vec4_min(rv.BL, mesh->content.content[i].origin);
		rv.TR = vec4_max(rv.TR, mesh->content.content[i].origin);

		rv.BL = vec4_min(rv.BL, mesh->content.content[i].left);
		rv.TR = vec4_max(rv.TR, mesh->content.content[i].left);

		rv.BL = vec4_min(rv.BL, mesh->content.content[i].right);
		rv.TR = vec4_max(rv.TR, mesh->content.content[i].right);

		mesh->content.content[i].bb.BL = vec4_min(vec4_min(mesh->content.content[i].origin, mesh->content.content[i].left), mesh->content.content[i].right);
		mesh->content.content[i].bb.TR = vec4_max(vec4_max(mesh->content.content[i].origin, mesh->content.content[i].left), mesh->content.content[i].right);
	}
	mesh->bb = rv;
	return rv;
}
/*

simple_triangle_mesh simple_triangle_mesh_new() {
	simple_triangle_mesh rv;
	rv.content = new_arraylist_triangle();
	rv.colors = new_arraylist_color();
	Tracable O;
	O.type = simple_triangle_mesh_trace;
	O.model= malloc(sizeof(simple_triangle_mesh));
	*((simple_triangle_mesh*)O.model) = rv;
	return O;
}*/