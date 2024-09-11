#include "render_workload.h"
void f(void* render_p) {
	render_workload* payload = render_p;
	trace_result result = payload->T.trace(payload->r, payload->T.model);
	if (result.is_hit)
	{
		payload->s.content[payload->r.x + payload->r.y * payload->s.height] = result.target.color;
	}

}