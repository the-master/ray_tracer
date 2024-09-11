#pragma once
#include <stdlib.h>
#include "simple_triangle_mesh.h"
#include "bounding_box.h"
typedef struct kd_tree {
	struct kd_tree* left;
	struct kd_tree* right;
	simple_triangle_mesh content;
	int plane;//0:x  1:y    2:z
	int is_leaf;
	bounding_box bb;
}kd_tree;
kd_tree kd_tree_create(simple_triangle_mesh mesh);
void kd_tree_del(kd_tree);