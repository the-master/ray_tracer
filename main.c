#include <stdio.h>
#include <time.h>
#include <threads.h>
#include <windows.h>
#include "raytracer/data_structures/data_structs.h"
#include "arraylist_vec4.h"
#include "arraylist_triangle.h"
#include "arraylist_tracable.h"
#include "screen/screen.h"
#include "camera.h"
#include "raytracer/models/simple_triangle_mesh.h"
#include "parsing/simple_obj_parser.h"
#include "float.h"
#include "threadsafe_workset.h"
#include "trace_result.h"
#define _USE_MATH_DEFINES 1
#include "math.h"
#include "bounding_box.h"
#include "kd_tree.h"
#include "Tracable.h"
#define THREAD_COUNT 4

static clock_t start;
double tic() {
	start=clock();
	printf("\r\ntimer started\r\n");
}
double toc() {
	printf("\r\ntimer finished after:\t%ims\r\n",clock() - start);
}
trace_result arraylist_Tracable_trace(ray r, arraylist_Tracable* list) {
	trace_result rv = { .distance = DBL_MAX };
	for (int i = 0; i < list->n; i++) {
		trace_result res =list->content->trace(r, list->content[i].model);
		
		if (res.distance < rv.distance) {
			rv = res;
		}
	}
	return rv;
}
Tracable tracalbe_arraylist_wrapper(arraylist_Tracable list) {
	Tracable rv = {
		.type = -99,
		.model = malloc(sizeof(arraylist_Tracable)),
		.trace = arraylist_Tracable_trace
	};
	*((arraylist_Tracable*)rv.model) = list;
	return rv;
}

int render(camera c, Tracable tree, screen s);
int main() {
#ifdef __STDC_NO_ATOMICS__
	printf("__STDC_NO_ATOMICS__\r\n");
#endif // __STDC_NO_ATOMICS__



	srand(clock());
	screen a_screen = screen_new(1000, 1000);
	screen_draw_screen(a_screen);
	return;
	camera c = { .origin = {0,1,8,1},.direction = {0,0,-1,1},.up = {0,-1,0,1} };
	//a simple obj model with only vertices & faces
	obj_model o = simple_parse("C:\\Users\\diete\\Documents\\raytracer_in\\teapot.obj");
	simple_triangle_mesh scene = simple_triangle_mesh_new();
	
	scene.content = o.faces;
	printds(calculate_bb(&scene));

	printf("faces: %i", o.faces.n);
	for (int i = 0; i < scene.content.n; i++) {
		int ra = rand() % 3;
		scene.content.content[i].color = (color){((ra % 3) == 0) * 200, ((ra % 3) == 1) * 200, ((ra % 3) == 2) * 200};
	}
	kd_tree tree = kd_tree_create(scene);

	//render(c, tree, a_screen);
	Tracable SC = traceable_kd_tree_wrapper(tree);
	SC = tracable_wrap(SC, matrix_gen_rotate_x(0),1);
	
	Tracable SCSC = tracable_wrap(SC, matrix_gen_rotate_x(M_PI),1);
	vec4 arg = (vec4){ 0,1,0,0 };
	SC = tracable_wrap(SC, matrix_gen_translate(arg), 0);
	SC = tracable_wrap(SC, matrix_gen_rotate_x(M_PI / 8), 1);
	SC = tracable_wrap(SC, matrix_gen_rotate_y(M_PI / 8), 1);

	arraylist_Tracable list = new_arraylist_Tracable();

	insert_Tracable(&list, list.n, SCSC);
	insert_Tracable(&list, list.n, SC);
	int teapot_count = 0;
	arg = (vec4){ 4,5,-.5,0 };
	Tracable pot = tracable_wrap(SC, matrix_gen_translate(arg), 0);
	while (teapot_count--) {
		pot = tracable_wrap(pot, matrix_gen_translate(arg), 0);
		pot = tracable_wrap(pot, matrix_gen_rotate_x(M_PI/10), 1);
		insert_Tracable(&list, list.n, pot);
	}
	Tracable main = tracalbe_arraylist_wrapper(list);

	tic();
	render2(c,main , a_screen);
	toc();
	screen_draw_image(a_screen, "C:\\Users\\diete\\Documents\\raytracer_out\\test.tga");
	
	return 0;
}
int intersect2(ray r, bounding_box b) {
	// r.dir is unit direction vector of ray
	vec4 dirfrac;
	dirfrac.x = 1.0f / r.dir.x;
	dirfrac.y = 1.0f / r.dir.y;
	dirfrac.z = 1.0f / r.dir.z;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (b.BL.x - r.origin.x) * dirfrac.x;
	float t2 = (b.TR.x - r.origin.x) * dirfrac.x;
	float t3 = (b.BL.y - r.origin.y) * dirfrac.y;
	float t4 = (b.TR.y - r.origin.y) * dirfrac.y;
	float t5 = (b.BL.z - r.origin.z) * dirfrac.z;
	float t6 = (b.TR.z - r.origin.z) * dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		return 0;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return 0;
	}

	return 1;
}

int render(camera c, Tracable tracable, screen s) {
	arraylist_ray rays = camera_gen_rays(c, s.width, s.height);
	printf("done generating rays\r\n");
	for (int i = 0; i < rays.n; i++) {
		ray r = rays.content[i];

		trace_result result = tracable.trace(r, tracable.model);
		if (result.is_hit)
		{
			s.content[r.x + r.y * s.height] = result.target.color;
		}
	}
	return 0;
}



int worker_render_payload(void* work_collection) {
	threadsafe_workset* workset = (threadsafe_workset*)work_collection;
	while (1) {
	//	printf("waiting\r\n");
	render_workload p = threadsafe_workset_get_next_workload(workset);
	//printds(p.r);
	//printf("\tconsumed\r\n");
	
		if (!p.valid) {
			return 1;
		}
		ray r = p.r;
		trace_result result = p.T.trace(r, p.T.model);
		if (result.is_hit) {
			p.s.content[r.x + r.y * p.s.height] = result.target.color;
		}

	}
}
int render2(camera c, Tracable tracable, screen s) {
	arraylist_ray rays = camera_gen_rays(c, s.width, s.height);
	arraylist_render_workload work = new_arraylist_render_workload();

	

	printf("done generating rays\r\n");
	for (int i = 0; i < rays.n; i++) {
		render_workload workload = {
			.s = s,
			.r = rays.content[i],
			.T = tracable,
			.valid = 1
		};
		insert_render_workload(&work, work.n, workload);
	}
	threadsafe_workset workset = new_threadsafe_workset(work);

	thrd_t pool[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++) {
		thrd_create(&pool[i], worker_render_payload, &workset);
	}
	for (int i = 0; i < THREAD_COUNT; i++) {
		int res;
		thrd_join(pool[i],&res);
	}

	return 0;
}