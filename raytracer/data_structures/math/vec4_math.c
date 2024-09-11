#include "vec4_math.h"
vec4 vec4_add(vec4 left, vec4 right) {
	vec4 x = { .x = left.x + right.x, .y = left.y + right.y, .z = left.z + right.z, .a = 1 };
	return x;
}; vec4 vec4_sub(vec4 left, vec4 right) {
	vec4 x = { .x = left.x - right.x, .y = left.y - right.y, .z = left.z - right.z, .a = 1 };
	return x;
};
vec4 vec4_cross(vec4 left, vec4 right) {
	vec4 x = {
		.x = left.y * right.z - left.z * right.y
 		, .y = left.z * right.x - left.x * right.z
		, .z = left.x * right.y - left.y * right.x
		, .a = 1 };
	return x;
};
double vec4_distance(vec4 vec) {
	return sqrt(vec4_dot(vec,vec));
}
double vec4_dot(vec4 left, vec4 right) {
	return left.x* right.x + left.y * right.y
		+ left.z * right.z;
	
};
vec4 vec4_neg(vec4 left) {
	vec4 x = { .x = -left.x , .y = -left.y , .z = -left.z, .a = left.a };
	return x;

}
vec4 vec4_scale(vec4 left,double scale) {
	vec4 x = { .x = scale * left.x , .y = scale * left.y , .z = scale * left.z, .a = left.a };
	return x;

}
static double min(double x, double y) { return x < y ? x : y; }
static double max(double x, double y) { return x >= y ? x : y; }
vec4 vec4_min(vec4 a, vec4 b) {
	return (vec4) {
		.x = min(a.x, b.x),
		.y = min(a.y, b.y),
		.z = min(a.z, b.z),
		.a = 1.0
	};
}
vec4 vec4_max(vec4 a, vec4 b) {
	return (vec4) {
		.x = max(a.x, b.x),
		.y = max(a.y, b.y),
		.z = max(a.z, b.z),
		.a = 1.0
	};
}
vec4 vec4_normalize(vec4 v) {
	double len=sqrt(vec4_dot(v, v));
	return vec4_scale(v, 1.0 / len);
}

vec4 matrix_vec4_mult(matrix x, vec4 v) {
	
	vec4 rv;
	rv.x = v.x * x.content[0][0] + v.y * x.content[0][1] + v.z * x.content[0][2] + v.a*x.content[0][3];
	rv.y = v.x * x.content[1][0] + v.y * x.content[1][1] + v.z * x.content[1][2] + v.a * x.content[1][3];
	rv.z = v.x * x.content[2][0] + v.y * x.content[2][1] + v.z* x.content[2][2] + v.a * x.content[2][3];
	rv.a = 1;
	return rv;
}
matrix matrix_matrix_mult(matrix x, matrix v){
	matrix rv = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			double sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += x.content[i][k] * v.content[k][j];
			}
			rv.content[i][j] = sum;
		}
	}
	
	return rv;
}
matrix matrix_gen_diag(double value){
	matrix rv = { 0 };
	rv.content[0][0] = value;
	rv.content[1][1] = value;
	rv.content[2][2] = value;
	rv.content[3][3] = value;
	return rv;
}
matrix matrix_gen_translate(vec4 direction) {
	matrix rv = matrix_gen_diag(1.0);
	rv.content[0][3] = direction.x;
	rv.content[1][3] = direction.y;
	rv.content[2][3] = direction.z;
	rv.content[3][3] = 1;
	return rv;
}
matrix matrix_gen_rotate_x(double angle) {
	matrix rv = matrix_gen_diag(1);
	rv.content[1][1] = cos(angle);
	rv.content[2][1] = sin(angle);
	rv.content[1][2] = -sin(angle);
	rv.content[2][2] = cos(angle);
	return rv;
}
matrix matrix_gen_rotate_y(double angle) {
	matrix rv = matrix_gen_diag(1);

	rv.content[0][0] = cos(angle);
	rv.content[0][2] = sin(angle);
	rv.content[2][0] = -sin(angle);
	rv.content[2][2] = cos(angle);
	return rv;
}
matrix matrix_gen_rotate_z(double angle) {
	matrix rv = matrix_gen_diag(1);

	rv.content[0][0] = cos(angle);
	rv.content[1][0] = sin(angle);
	rv.content[0][1] = -sin(angle);
	rv.content[0][2] = cos(angle);
	return rv;
}
matrix matrix_inverse(matrix m) {
	double A2323 = m.content[2][2] * m.content[3][3] - m.content[2][3] * m.content[3][2];
	double A1323 = m.content[2][1] * m.content[3][3] - m.content[2][3] * m.content[3][1];
	double A1223 = m.content[2][1] * m.content[3][2] - m.content[2][2] * m.content[3][1];
	double A0323 = m.content[2][0] * m.content[3][3] - m.content[2][3] * m.content[3][0];
	double A0223 = m.content[2][0] * m.content[3][2] - m.content[2][2] * m.content[3][0];
	double A0123 = m.content[2][0] * m.content[3][1] - m.content[2][1] * m.content[3][0];
	double A2313 = m.content[1][2] * m.content[3][3] - m.content[1][3] * m.content[3][2];
	double A1313 = m.content[1][1] * m.content[3][3] - m.content[1][3] * m.content[3][1];
	double A1213 = m.content[1][1] * m.content[3][2] - m.content[1][2] * m.content[3][1];
	double A2312 = m.content[1][2] * m.content[2][3] - m.content[1][3] * m.content[2][2];
	double A1312 = m.content[1][1] * m.content[2][3] - m.content[1][3] * m.content[2][1];
	double A1212 = m.content[1][1] * m.content[2][2] - m.content[1][2] * m.content[2][1];
	double A0313 = m.content[1][0] * m.content[3][3] - m.content[1][3] * m.content[3][0];
	double A0213 = m.content[1][0] * m.content[3][2] - m.content[1][2] * m.content[3][0];
	double A0312 = m.content[1][0] * m.content[2][3] - m.content[1][3] * m.content[2][0];
	double A0212 = m.content[1][0] * m.content[2][2] - m.content[1][2] * m.content[2][0];
	double A0113 = m.content[1][0] * m.content[3][1] - m.content[1][1] * m.content[3][0];
	double A0112 = m.content[1][0] * m.content[2][1] - m.content[1][1] * m.content[2][0];

	double det = m.content[0][0] * (m.content[1][1] * A2323 - m.content[1][2] * A1323 + m.content[1][3] * A1223)
		- m.content[0][1] * (m.content[1][0] * A2323 - m.content[1][2] * A0323 + m.content[1][3] * A0223)
		+ m.content[0][2] * (m.content[1][0] * A1323 - m.content[1][1] * A0323 + m.content[1][3] * A0123)
		- m.content[0][3] * (m.content[1][0] * A1223 - m.content[1][1] * A0223 + m.content[1][2] * A0123);
	det = 1 / det;

	return (matrix) {
		.content[0][0] = det * (m.content[1][1] * A2323 - m.content[1][2] * A1323 + m.content[1][3] * A1223),
			.content[0][1] = det * -(m.content[0][1] * A2323 - m.content[0][2] * A1323 + m.content[0][3] * A1223),
			.content[0][2] = det * (m.content[0][1] * A2313 - m.content[0][2] * A1313 + m.content[0][3] * A1213),
			.content[0][3] = det * -(m.content[0][1] * A2312 - m.content[0][2] * A1312 + m.content[0][3] * A1212),
			.content[1][0] = det * -(m.content[1][0] * A2323 - m.content[1][2] * A0323 + m.content[1][3] * A0223),
			.content[1][1] = det * (m.content[0][0] * A2323 - m.content[0][2] * A0323 + m.content[0][3] * A0223),
			.content[1][2] = det * -(m.content[0][0] * A2313 - m.content[0][2] * A0313 + m.content[0][3] * A0213),
			.content[1][3] = det * (m.content[0][0] * A2312 - m.content[0][2] * A0312 + m.content[0][3] * A0212),
			.content[2][0] = det * (m.content[1][0] * A1323 - m.content[1][1] * A0323 + m.content[1][3] * A0123),
			.content[2][1] = det * -(m.content[0][0] * A1323 - m.content[0][1] * A0323 + m.content[0][3] * A0123),
			.content[2][2] = det * (m.content[0][0] * A1313 - m.content[0][1] * A0313 + m.content[0][3] * A0113),
			.content[2][3] = det * -(m.content[0][0] * A1312 - m.content[0][1] * A0312 + m.content[0][3] * A0112),
			.content[3][0] = det * -(m.content[1][0] * A1223 - m.content[1][1] * A0223 + m.content[1][2] * A0123),
			.content[3][1] = det * (m.content[0][0] * A1223 - m.content[0][1] * A0223 + m.content[0][2] * A0123),
			.content[3][2] = det * -(m.content[0][0] * A1213 - m.content[0][1] * A0213 + m.content[0][2] * A0113),
			.content[3][3] = det * (m.content[0][0] * A1212 - m.content[0][1] * A0212 + m.content[0][2] * A0112),
	};

}