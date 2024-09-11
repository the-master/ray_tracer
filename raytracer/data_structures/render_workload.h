#pragma once
#include "ray.h"
#include "Tracable.h"
#include "screen.h"
typedef struct render_workload {
	int valid;
	ray r;
	Tracable T;
	screen s;
}render_workload;
void f(void* render_p);
