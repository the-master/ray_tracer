#pragma once
#include "vec4.h"
#include "vec4_math.h"
#include "arraylist_ray.h"
typedef struct camera {
	vec4 origin;
	vec4 direction;
	vec4 up;
}camera;
arraylist_ray camera_gen_rays(camera c, int width, int heigth);


