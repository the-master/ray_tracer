#include "data_structs.h"
int print_vec4(vec4 in) {
	return printf("{%f\t%f\t%f\t}", in.x, in.y, in.z, in.a);
}
int print_ray(ray in) {
	printf("[");
	print_vec4(in.origin);
	print_vec4(in.dir);
	return printf("]");
}
int print_matrix(matrix in) {
	printf("#");
	print_vec4(in.rows[0]);
	print_vec4(in.rows[1]);
	print_vec4(in.rows[2]);
	print_vec4(in.rows[3]);
}
int print_triangle(triangle in) {
	printf(">");
	print_vec4(in.origin);
	print_vec4(in.left);
	print_vec4(in.right);
	print_vec4(in.normal);
}
int print_bb(bounding_box in) {
	printf("[BL]");
	print_vec4(in.BL);
	printf("\r\n");
	printf("[TR]");
	print_vec4(in.TR);
	printf("\r\n");
}