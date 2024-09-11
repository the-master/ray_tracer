#pragma once
#include "vec4.h"
typedef struct matrix{
	union {
		struct {
			double content[4][4];
		};
		struct {
			double raw[16];
		};
		struct {
			vec4 rows[4];
		};
	};
}matrix;