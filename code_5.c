#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

void main()
{
	FILE* fp;
	unsigned char** input, ** output;
	int i, j, x, y; x = y = 0;
	double val;

	//Memory alloc
	input = (unsigned char**)malloc(sizeof(unsigned char*) * 512);
	output = (unsigned char**)malloc(sizeof(unsigned char*) * 512);

	for (i = 0; i < 512; i++) {
		input[i] = (unsigned char*)malloc(sizeof(unsigned char) * 512);
		output[i] = (unsigned char*)malloc(sizeof(unsigned char) * 512);

	}


	//File read
	fp = fopen("lena.img", "rb");
	for (i = 0; i < 512; i++) {
		fread(input[i], sizeof(unsigned char), 512, fp);
	}
	fclose(fp);


	//Zoom-out
	for (i = 0; i < 512; i++) {
		for (j = 0; j < 512; j++) {
			if ((i % 2 == 0) && (j % 2 == 0)) {
				val = input[i][j];
				output[x][y] = (unsigned char)val;
				if (y == 255) { x++; y = 0; }
				else { y++;	}

			}
		}
	}

	for (i = 256; i < 512; i++) {
		for (j = 0; j < 512; j++) {
			output[i][j] = 0;
		}
	}
	for (i = 0; i < 256; i++) {
		for (j = 256; j < 512; j++) {
			output[i][j] = 0;
		}
	}

	//translation
	for (i = 255; i >= 0; i--) {
		for (j = 255; j >=0; j--) {
			output[i + 100][j + 80] = output[i][j];
			output[i][j] = 0;
		}
	}

	//File write
	fp = fopen("output_5.img", "wb");

	for (i = 0; i < 512; i++)
	{
		fwrite(output[i], sizeof(unsigned char), 512, fp);
	}
	fclose(fp);

	//Memory free
	for (i = 0; i < 512; i++)
		free(input[i]);
	free(input);

	for (i = 0; i < 512; i++)
		free(output[i]);
	free(output);
}