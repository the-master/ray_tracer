#include "vec4.h"
int vec4_equal(vec4 a, vec4 b) {
	return a.x == b.x && a.y == b.y && a.z == b.z && a.a == b.a;
}