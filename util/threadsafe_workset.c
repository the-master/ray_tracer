#pragma once
#include "threadsafe_workset.h"
/*
void add_work(threadsafe_workset* set, render_payload payload, int final_flag) {
	int read_state = mtx_trylock(&set->read_lock);
	int waiting_for_data = mtx_trylock(&set->waiting_for_data);

	

	mtx_lock(&set->write_lock);
	insert_render_payload(&set->work, set->work.n, payload);
	mtx_unlock(&set->write_lock);
	mtx_unlock(&set->waiting_for_data);
}*/
threadsafe_workset new_threadsafe_workset(arraylist_render_workload work) {
	threadsafe_workset rv;
	rv.work = work;
	mtx_init(&rv.read_lock,mtx_plain);
	return rv;
}
render_workload threadsafe_workset_get_next_workload(threadsafe_workset* set) {
	
	mtx_lock(&set->read_lock);
	if (set->work.n <= 0) {
		mtx_unlock(&set->read_lock);
		return (render_workload) { 0 };
	}
		
	render_workload workload = set->work.content[set->work.n - 1];
	set->work.n--;
	mtx_unlock(&set->read_lock);
	return workload;
}