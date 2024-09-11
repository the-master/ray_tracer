#include <math.h>
#include "../vec4.h"
#include "../matrix.h"
#include "math.h"
double vec4_distance(vec4 vec);
vec4 vec4_add(vec4 left, vec4 right);
vec4 vec4_sub(vec4 left, vec4 right);
vec4 vec4_neg(vec4 left);
vec4 vec4_cross(vec4 left, vec4 right);
double vec4_dot(vec4 left, vec4 right);
vec4 vec4_scale(vec4 left, double right);
vec4 vec4_min(vec4, vec4);
vec4 vec4_max(vec4, vec4);
vec4 vec4_normalize(vec4);

vec4 matrix_vec4_mult(matrix x, vec4 v);
matrix matrix_matrix_mult(matrix x, matrix v);
matrix matrix_inverse(matrix );
matrix matrix_gen_diag(double value);
matrix matrix_gen_translate(vec4 direction);


matrix matrix_gen_translate(vec4 direction);
matrix matrix_gen_rotate_x(double angle);
matrix matrix_gen_rotate_y(double angle);
matrix matrix_gen_rotate_z(double angle);