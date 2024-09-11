#include "kd_tree.h"
/*
static int sort_x(triangle* a, triangle* b) {

	return (a->bb.BL.x + a->bb.TR.x) / 2 <= (b->bb.BL.x + b->bb.TR.x) / 2 ? -1 : 1;
}
static int sort_y(triangle* a, triangle* b) {
	return (a->bb.BL.y + a->bb.TR.y) / 2 <= (b->bb.BL.y + b->bb.TR.y) / 2 ? -1 : 1;
}
static int sort_z(triangle* a, triangle* b) {
	return (a->bb.BL.z + a->bb.TR.z) / 2 <= (b->bb.BL.z + b->bb.TR.z) / 2 ? -1 : 1;
}
*/
static int sort_x(triangle* a, triangle* b) {
	return a->bb.BL.x <= b->bb.BL.x?-1:1;
}
static int sort_y(triangle* a, triangle* b) {
	return a->bb.BL.y <= b->bb.BL.y ? -1 : 1;
}
static int sort_z(triangle* a, triangle* b) {
	return a->bb.BL.z <= b->bb.BL.z ? -1 : 1;
}
static int (*plane_sort[3])(triangle, triangle) = {sort_x,sort_y,sort_z};
kd_tree kd_tree_create_internal(simple_triangle_mesh mesh,int plane) {
	if ((mesh.content.n) < 50) {

		color random_color = (color){ rand() % 255,rand() % 255, rand() % 255 };
		for (int i = 0; i < mesh.content.n; i++)
			mesh.content.content[i].color = random_color;
		return (kd_tree) { .content = mesh,.bb=mesh.bb, .is_leaf = 1 };
	}
 	qsort(mesh.content.content, mesh.content.n, sizeof(triangle), plane_sort[plane]);
	simple_triangle_mesh left_mesh = {
			.content.content = mesh.content.content,
			.content.n = mesh.content.n / 2
	};
	calculate_bb(&left_mesh);
	simple_triangle_mesh right_mesh = {
			.content.content = &mesh.content.content[mesh.content.n / 2],
			.content.n = mesh.content.n - mesh.content.n / 2
	};
	calculate_bb(&right_mesh);
	kd_tree left = kd_tree_create_internal(left_mesh, (plane + 1) % 3);
	kd_tree right = kd_tree_create_internal(right_mesh, (plane + 1) % 3);
	kd_tree rv = (kd_tree){
		.left = malloc(sizeof(kd_tree)),
		.right = malloc(sizeof(kd_tree)),
		.content=mesh,
		.bb=mesh.bb
	};
	rv.bb=calculate_bb(&rv.content);
	*(rv.left)= left;
	*(rv.right) = right;

	return rv;
}
kd_tree kd_tree_create(simple_triangle_mesh mesh) {
	return kd_tree_create_internal(mesh,0);
}
void kd_tree_del(kd_tree tree) {

}