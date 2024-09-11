#pragma once
#include "Tracable.h"
trace_result triangle_trace(ray r, triangle* t) {
	double epsilon = 0.000002;

	vec4 edge1 = vec4_add(t->left, vec4_neg(t->origin));
	vec4 edge2 = vec4_add(t->right, vec4_neg(t->origin));

	vec4 ray_cross_e2 = vec4_cross(r.dir, edge2);
	double det = vec4_dot(edge1, ray_cross_e2);

	if (det > -epsilon && det < epsilon)
		return (trace_result) { .distance = DBL_MAX };    // This ray is parallel to this triangle.

	float inv_det = 1.0 / det;
	vec4 s = vec4_add(r.origin, vec4_neg(t->origin));
	float u = inv_det * vec4_dot(s, ray_cross_e2);

	if (u < 0 || u > 1)
		return (trace_result) { .distance = DBL_MAX };

	vec4 s_cross_e1 = vec4_cross(s, edge1);
	float v = inv_det * vec4_dot(r.dir, s_cross_e1);

	if (v < 0 || u + v > 1)
		return (trace_result) { .distance = DBL_MAX };


	// At this stage we can compute t to find out where the intersection point is on the line.
	double T = inv_det * vec4_dot(edge2, s_cross_e1);
	vec4 L = vec4_add(t->left, vec4_scale(t->origin, -1));
	vec4 R = vec4_add(t->right, vec4_scale(t->origin, -1));
	return (trace_result) {
		.is_hit = T > epsilon,
			.u = u,
			.v = v,
			.hit_location = vec4_add(vec4_scale(L, u), vec4_scale(R, v)),
			.distance = sqrt((t->origin.x - r.origin.x) * (t->origin.x - r.origin.x) + (t->origin.y - r.origin.y) * (t->origin.y - r.origin.y) + (t->origin.z - r.origin.z) * (t->origin.z - r.origin.z)),
			.target = *t
	};  // ray intersection
}
static int intersect2(ray r, bounding_box b) {
	// r.dir is unit direction vector of ray
	vec4 dirfrac;
	dirfrac.x = 1.0f / r.dir.x;
	dirfrac.y = 1.0f / r.dir.y;
	dirfrac.z = 1.0f / r.dir.z;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (b.BL.x - r.origin.x) * dirfrac.x;
	float t2 = (b.TR.x - r.origin.x) * dirfrac.x;
	float t3 = (b.BL.y - r.origin.y) * dirfrac.y;
	float t4 = (b.TR.y - r.origin.y) * dirfrac.y;
	float t5 = (b.BL.z - r.origin.z) * dirfrac.z;
	float t6 = (b.TR.z - r.origin.z) * dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		return 0;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return 0;
	}

	return 1;
}
trace_result simple_triangle_mesh_trace(ray r, simple_triangle_mesh* m) {
	trace_result best_result = { .distance = DBL_MAX };
	for (int j = 0; j < m->content.n; j++) {
		if (!intersect2(r, m->content.content[j].bb))
		{
			continue;
		}
		trace_result result = triangle_trace(r, &m->content.content[j]);
		if (result.distance < best_result.distance)
		{
			best_result = result;
		}
	}
	return best_result;
}
trace_result kd_tree_trace(ray r,kd_tree* tree) {
	if (!intersect2(r, tree->bb)) {
		return (trace_result) { .distance = DBL_MAX };
	}
	if (tree->is_leaf) {
		return simple_triangle_mesh_trace(r, &tree->content);
	}

	trace_result left = kd_tree_trace(r, tree->left);
	trace_result right = kd_tree_trace(r, tree->right);

	return left.distance < right.distance ? left : right;
}

Tracable traceable_kd_tree_wrapper(kd_tree tree) {

	Tracable rv = {
		.type = traceable_kd_tree_type,
		.model = malloc(sizeof(kd_tree)),
		.trace = kd_tree_trace
	};
	*((kd_tree*)rv.model) = tree;

	return rv;
}
Tracable tri_wrapper(triangle t) {

	Tracable rv = {
		.type = triangle_traceable_type,
		.model = malloc(sizeof(triangle)),
		.trace = triangle_trace
	};
	*((triangle*)rv.model) = t;

	return rv;
}
Tracable mesh_wrapper(simple_triangle_mesh m) {
	Tracable rv = {
		.type = simple_triangle_mesh_traceable_type,
		.model = malloc(sizeof(simple_triangle_mesh)),
		.trace = triangle_trace
	};
	*((simple_triangle_mesh*)rv.model) = m;
	return rv;
}
trace_result node_trace(ray r, node* node) {

	r.origin = matrix_vec4_mult(node->m, r.origin);
	if(node->change_dir)
		r.dir = matrix_vec4_mult(node->m, r.dir);
	trace_result result = node->cont.trace(r, node->cont.model);
	result.hit_location = matrix_vec4_mult(node->m_inverse, result.hit_location);
	return result;
}
Tracable tracable_wrap(Tracable T, matrix m,int change_camera_dir) {
	node t ;
	t.cont = T;
	t.m_inverse = m;
	t.m = matrix_inverse(m);
	t.change_dir = change_camera_dir;
	Tracable rv = {
		.type = traceable_node_type,
		.model = malloc(sizeof(node)),
		.trace = node_trace
	};

	*((node*)rv.model) = t;
	return rv;
}