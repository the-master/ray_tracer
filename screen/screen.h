#pragma once
#include "color.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

typedef struct screen{
	int width;
	int height;
	color* content;
}screen ;
screen screen_new(int width, int height);
void screen_draw_image(screen s, char* path);
void screen_draw_screen(screen s);

