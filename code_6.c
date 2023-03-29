#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)
#define pi 3.141592653589793238462643383279



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

	//zoom-out
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
			output[i + 200][j + 20] = output[i][j];
			output[i][j] = 0;
		}
	}

	//rotation		
	for (i = 0; i<512; i++) {
		for (j =0 ; j <512; j++) {
			x = (int)((double)i * cos(0.2) - (double)j * sin(0.2));
			y = (int)((double)i * sin(0.2) + (double)j * cos(0.2));
			if ((x >= 0) && (y >= 0) && (x < 512) && (y < 512)) {
				output[x][y] = output[i][j];
			}
			output[i][j] = 0;
		}
	}

	//hole
	for (i = 1; i < 511; i++) {
		for (j = 1; j < 511; j++) {
			if ( (output[i - 1][j] != 0) && (output[i][j - 1] != 0) && (output[i][j + 1] != 0) && (output[i + 1][j] != 0)&&(output[i][j]==0)) {
				output[i][j] = (output[i - 1][j]+ output[i][j-1]+ output[i][j+1]+output[i+1][j]) / 4;
			}
		}
	}
	





	//File write
	fp = fopen("output_6.img", "wb");

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