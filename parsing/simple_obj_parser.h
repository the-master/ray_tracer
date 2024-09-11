#include <stdio.h>
#include <float.h>
#include "vec4.h"
#include "arraylist_vec4.h"
#include "arraylist_triangle.h"
typedef struct obj_model {
	arraylist_vec4 vertices;
	arraylist_triangle faces;
}obj_model;


obj_model simple_parse(char* location);