#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

void main()
{
	FILE* fp;
	unsigned char** input, ** output;
	int i, j;
	double val1, val2, val;

	//Memory alloc
	input = (unsigned char**)malloc(sizeof(unsigned char*) * 512);
	output = (unsigned char**)malloc(sizeof(unsigned char*) * 512);

	for (i = 0; i < 512; i++) {
		input[i] = (unsigned char*)malloc(sizeof(unsigned char) * 512);
	}

	for (i = 0; i < 512; i++) {
		output[i] = (unsigned char*)malloc(sizeof(unsigned char) * 512);
	}

	//File read
	fp = fopen("lena.img", "rb");
	for (i = 0; i < 512; i++) {
		fread(input[i], sizeof(unsigned char), 512, fp);
	}
	fclose(fp);


	//High-pass
	for (i = 1; i < 511; i++) {
		for (j = 1; j < 511; j++) {
			val1 = (input[i - 1][j - 1]) + (input[i - 1][j] * 2) + (input[i - 1][j + 1]) +
				(input[i + 1][j - 1] * (-1)) + (input[i + 1][j] * (-2)) + (input[i + 1][j + 1] * (-1));

			val2 = (input[i - 1][j - 1]) + (input[i - 1][j + 1] * (-1)) +
				(input[i][j - 1] * 2) + (input[i][j + 1] * (-2)) +
				(input[i + 1][j - 1]) + (input[i + 1][j + 1] * (-1));

			if (val1 < 0) { val1 = 0 - val1; }
			if (val2 < 0) { val2 = 0 - val2; }
			val = val1 + val2;
			output[i][j] = (unsigned char)val;
		}
	}


	//File write
	fp = fopen("output_4.img", "wb");

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