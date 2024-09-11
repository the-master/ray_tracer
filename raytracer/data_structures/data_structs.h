#pragma once
#include "matrix.h"
#include "ray.h"
#include "triangle.h"
#include "vec4.h"
#include "bounding_box.h"
#include "math/vec4_math.h"
#include <stdio.h>
int print_vec4(vec4 in);
int print_ray(ray in);
int print_matrix(matrix in);
int print_triangle(triangle in);
int print_bb(bounding_box in);
#define printds(X) _Generic((X), \
				vec4: print_vec4, \
				ray: print_ray, \
				matrix: print_matrix, \
				triangle: print_triangle, \
				bounding_box: print_bb \
				)(X)