#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

void main()
{
	FILE* fp;
	unsigned char** input, ** output;
	int i, j; int* n_k,*result; double* p_r,*s_r;
	double val;

	//Memory alloc
	input = (unsigned char**)malloc(sizeof(unsigned char*) * 512);
	output = (unsigned char**)malloc(sizeof(unsigned char*) * 512);

	for (i = 0; i < 512; i++) {
		input[i] = (unsigned char*)malloc(sizeof(unsigned char) * 512);
		output[i] = (unsigned char*)malloc(sizeof(unsigned char) * 512);
	}

	n_k = (int*)malloc(sizeof(int) * 256);
	for (i = 0; i < 256; i++) { n_k[i] = 0; }

	p_r = (double*)malloc(sizeof(double) * 256);
	for (i = 0; i < 256; i++) { p_r[i] = 0; }

	s_r = (double*)malloc(sizeof(double) * 256);
	for (i = 0; i < 256; i++) { s_r[i] = 0; }

	result = (int*)malloc(sizeof(int) * 256);
	for (i = 0; i < 256; i++) { result[i] = 0; }


	//File read
	fp = fopen("lena.img", "rb");
	for (i = 0; i < 512; i++) {
		fread(input[i], sizeof(unsigned char), 512, fp);
	}
	fclose(fp);

	
	//n_k
	for (i = 0; i < 512; i++) {
		for (j = 0; j < 512; j++) {
			n_k[input[i][j]]++;
		}
	}

	//p_r
	for (i = 0; i < 256; i++) {
		p_r[i] = ((double)n_k[i]) / (512 * 512);
	}

	//s_r 
	s_r[0] = 255*p_r[0];
	for (i = 1; i < 256; i++) {
		s_r[i] = s_r[i - 1] +(255* p_r[i]);
	}

	//result
	for (i = 0; i < 256; i++) {
		result[i] = round(s_r[i]);
	}

	//equalization
	for (i = 0; i < 512; i++) {
		for (j = 0; j < 512; j++) {
			output[i][j] = result[input[i][j]];
		}
	}














	//File write
	fp = fopen("output_7.img", "wb");

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

	free(result);
	free(s_r);
	free(p_r);
	free(n_k);
}