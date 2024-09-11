#include "screen.h"
screen screen_new(int width, int height) {
	screen rv;
	rv.width = width;
	rv.height = height;
	rv.content = (color*)malloc(sizeof(color) * width * height);
	for (int i = 0; i < width * height; i++){
		//  rv.content[i] = (color){ i%130 ,50+i%200,i%155};//default color
		rv.content[i] = (color){ 255,255,255 };// i % 130, 50 + i % 200, i % 155}
}//default color
    return rv;
}
void screen_draw_image(screen s, char* filename) 
{
	uint32_t width = s.width;
	uint32_t height = s.height;
	uint8_t* dataBGRA = s.content;
	uint8_t dataChannels = 3;
	uint8_t fileChannels = 3;
		FILE* fp = NULL;
		// MSVC prefers fopen_s, but it's not portable
		//fp = fopen(filename, "wb");
		fopen_s(&fp, filename, "wb");
		if (fp == NULL) return;

		// You can find details about TGA headers here: http://www.paulbourke.net/dataformats/tga/
		uint8_t header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0, (uint8_t)(width % 256), (uint8_t)(width / 256), (uint8_t)(height % 256), (uint8_t)(height / 256), (uint8_t)(fileChannels * 8), 0x20 };
		fwrite(&header, 18, 1, fp);

		for (uint32_t i = 0; i < width * height; i++)
		{

			fputc(dataBGRA[(i * dataChannels) + 2], fp);
			fputc(dataBGRA[(i * dataChannels) + 1], fp);
			fputc(dataBGRA[(i * dataChannels) + 0], fp);
			
		}
		fclose(fp);
	
}

void screen_draw_screen(screen s) {

	HDC screen = GetDC(0);
	while (1) {
		for (int i = 0; i < s.width; i++) {
			for (int j = 0; j < s.height; j++) {
				color c = s.content[i+ j * s.width];
				
				
				SetPixel(screen, i, j, RGB(c.r, c.g, c.b));
			}
		}
		printf("heya");
		Sleep(300);
	}
}
