#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

void main()
{
	FILE* fp;
	unsigned char** input, ** output;
	int i, j;
	double val;

	//Memory alloc
	input = (unsigned char**)malloc(sizeof(unsigned char*) * 512);
	output = (unsigned char**)malloc(sizeof(unsigned char*) * 256);

	for (i = 0; i < 512; i++) {
		input[i] = (unsigned char*)malloc(sizeof(unsigned char) * 512);
	}

	for (i = 0; i < 256; i++) {
		output[i] = (unsigned char*)malloc(sizeof(unsigned char) * 256);
	}

	//File read
	fp = fopen("lena.img", "rb");
	for (i = 0; i < 512; i++) {
		fread(input[i], sizeof(unsigned char), 512, fp);
	}
	fclose(fp);

	
	//Zoom-out
	for (i = 0; i < 512; i++)	{
		for (j = 0; j < 512; j++) 		{
			if ((i % 2 == 0) && (j % 2 == 0)) {
					val = input[i][j];
					output[i / 2][j / 2] = (unsigned char)val;
			}
		}
	}


	//File write
	fp = fopen("output_1.img", "wb");

	for (i = 0; i < 256; i++)
	{
		fwrite(output[i], sizeof(unsigned char), 256, fp);
	}
	fclose(fp);

	//Memory free
	for (i = 0; i < 512; i++)
		free(input[i]);
	free(input);

	for (i = 0; i < 256; i++)
		free(output[i]);
	free(output);
}