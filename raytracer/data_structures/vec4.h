#pragma once
typedef struct vec4 {
	union {
		struct {
			double x, y, z, a;
		};
		struct {
			double vec[4];
		};
	};
}vec4;

int vec4_equal(vec4 a, vec4 b);