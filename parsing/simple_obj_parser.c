#include "simple_obj_parser.h"
static obj_model obj_model_new() {
	obj_model rv;
	rv.vertices = new_arraylist_vec4();
	rv.faces = new_arraylist_triangle();
	return rv;
}
obj_model simple_parse(char* location) {
	printf("Begin reading %s\r\n", location);
	obj_model rv = obj_model_new();
 	FILE* fp = fopen(location, "r");
	if (fp == 0) {
		fprintf(stderr, "can't open %s: %s\n", location, strerror(errno));
		return (obj_model){ 0 };
	}
	char buff[1000] = { 0 };
	char* buffer = buff;
	while (fgets(buffer, 1000, fp)) {
		if (*buffer == 'v') {
			buffer = strtok(buffer, "\r");
			buffer = strtok(buffer, "\n");
			buffer = strtok(buffer, " ");
			vec4 vert;
			char* str = strtok(0, " ");

			vert.x = atof(str);
			str = strtok(0, " ");
			vert.y = atof(str);
			str = strtok(0, " ");
				vert.z = atof(str);
				vert.a = 1;
			
			rv.vertices.insert(&rv.vertices, rv.vertices.n, vert);
		}
	}
	rewind(fp);
	while (fgets(buffer, 1000, fp)) {
		if (*buffer == 'f') {
			buffer = strtok(buffer, "\r");
			buffer = strtok(buffer, "\n");
			buffer = strtok(buffer, " ");
			triangle face;
			char* str = strtok(0, " ");
			face.origin = rv.vertices.content[atoi(str) - 1];
			str = strtok(0, " ");
			face.left = rv.vertices.content[atoi(str) - 1];
			str = strtok(0, " ");
			face.right = rv.vertices.content[atoi(str) - 1];
			

			rv.faces.insert(&rv.faces, rv.faces.n, face);
		}
	}

	printf("Finished reading %s\r\n", location);

	return rv;
}