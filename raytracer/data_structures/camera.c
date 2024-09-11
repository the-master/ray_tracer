#include "camera.h"
#include "data_structs.h"
arraylist_ray camera_gen_rays(camera c, int width, int heigth) {
	arraylist_ray rv = new_arraylist_ray();
	vec4 target = vec4_add(c.origin, c.direction);
	vec4 cross = vec4_cross(c.direction, c.up);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < heigth; j++)
		{

			vec4 displacement = vec4_add(vec4_scale(cross, (i - width/2.0)/width),vec4_scale(c.up, (j - heigth / 2.0)/heigth));
			vec4 raytarget = vec4_add(target, displacement);
			ray R = {
				.origin = c.origin,
				.dir = vec4_normalize(vec4_sub(raytarget,c.origin)),
				.x = i,
				.y = j
			};
			insert_ray(&rv, rv.n, R);
		}
	}
	return rv;
}