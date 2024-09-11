#pragma once
#include <threads.h>
#include "arraylist_render_workload.h"
typedef struct threadsafe_workset {
	arraylist_render_workload work;
	mtx_t read_lock;
	int final_work_done;
}threadsafe_workset;
threadsafe_workset new_threadsafe_workset(arraylist_render_workload work);
render_workload threadsafe_workset_get_next_workload(threadsafe_workset* set);