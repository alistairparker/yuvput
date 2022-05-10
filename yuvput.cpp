#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern void* calloc(int, int);

#define iabs(x)	((x>=0)?x:-x)

int main(int argc, char** argv) {
	int width = 176;
	int height = 144;
	int rate = 60;
	FILE* fp = NULL;

	if(argc < 5) {
		fprintf(stderr, "Uage: yuvput outfile width height rate\n");
		exit(-1);
	}
	fp = fopen(*++argv, "wb");
	width = atoi(*++argv);
	height = atoi(*++argv);
	rate = atoi(*++argv);
	if(fp) {
		unsigned char* img = (unsigned char*)malloc(width * height * 2);

		if(img) {
			int o = 0;
			for(; o < 128; o++) {
				for(int i = 0; i < height; i++) {
					int roffset = i * width * 2;
					for(int j = 0; j < width; j++) {
						if( 0 == (j % 2)) {
							// U
							img[roffset + (j * 2)] = (i * 255) / height;
						} else {
							// V
							img[roffset + (j * 2)] = (j * 255) / width;
						}
						// Y
						img[roffset + (j * 2) + 1] = o % 128; // 0 => black, 255 => white
					}
				}
				fwrite(img, width * height * 2, 1, fp);
				if(rate) {
					usleep(1000000 / rate);
					rewind(fp);
				}
			}
			for(--o; 0 <= o ; o--) {
				for(int i = 0; i < height; i++) {
					int roffset = i * width * 2;
					for(int j = 0; j < width; j++) {
						if( 0 == (j % 2)) {
							// U
							img[roffset + (j * 2)] = (i * 255) / height;
						} else {
							// V
							img[roffset + (j * 2)] = (j * 255) / width;
						}
						// Y
						img[roffset + (j * 2) + 1] = o % 128; // 0 => black, 255 => white
					}
				}
				fwrite(img, width * height * 2, 1, fp);
				if(rate) {
					usleep(1000000 / rate);
					rewind(fp);
				}
			}
		}
		fclose(fp);
	}
}
