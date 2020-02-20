/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "sys/alt_timestamp.h"
#include "alt_types.h"

unsigned char** pgmread(char* filename, int* w, int* h)
{
    FILE* file;
    char line[256];
    int maxval;
    int binary;
    int nread;
    int i,j, int_tmp;

    unsigned char** data;
    unsigned char*  bindata;
	printf("Debug: Opening image:\n");
    if ((file = fopen(filename, "r")) == NULL)
	{
	    printf("ERROR: file open failed\n");
	    *h = *w = 0;
	    return(NULL);
	} else {
		printf("Debug: Image open successfully!\n");
	}
    fgets(line, 256, file);
    if (strncmp(line,"P5", 2))
	{
	    if (strncmp(line,"P2", 2))
		{
		    printf("pgm read: not a pgm file\n");
		    *h = *w = 0;
		    return(NULL);
		}
	    else
		binary = 0;
	}
    else
	binary = 1;

    fgets(line, 256, file);
    while (line[0] == '#')
    fgets(line, 256, file);


    sscanf(line,"%d", w);
    fgets(line, 256, file);
    sscanf(line,"%d", h);
    fgets(line, 256, file);
    sscanf(line, "%d", &maxval);


    if ((data = (unsigned char**)calloc((*w), sizeof(unsigned char*))) == NULL)
    {
	printf("Memory allocation error. Exit program\n");
	exit(1);
    }
    for (j=0 ; j < (*w); j++)
        if ((data[j] = (unsigned char*)calloc((*h), sizeof(unsigned char))) == NULL)
        {
	   printf("Memory allocation error. Exit program\n");
	   exit(1);
        }


    if (binary)
    {
	if ((bindata = (unsigned char*)calloc((*w)*(*h), sizeof(unsigned char))) == NULL)
        {
	   printf("Memory allocation error on bindata. Exit program\n");
	   exit(1);
        }

	printf("Reading %s as binary.\n", filename);

	nread = fread((void*)bindata, sizeof(unsigned char), (*w)*(*h), file);

	for(i=0; i< (*w); i++)
           for(j=0; j< (*h); j++)
               data[i][j] = (unsigned char)bindata[(j*(*w))+i];

	free(bindata);
    }
    else {
	printf("Reading %s as ascii.\n", filename);

	for (i = 0; i < (*h); i++)
	{
            for (j = 0; j < (*w); j++)
	    {
		fscanf(file,"%d", &int_tmp);
		data[j][i] = (unsigned char)int_tmp;

	    }

        }

    }


    fclose(file);
    return(data);
}

int pgmwrite(char* filename, int w, int h, unsigned char** data,
			char* comment_string, int binsave)
{
    FILE* file;
    char line[256];
    int maxval;
    int binary;
    int nread;
    int i,j, int_tmp;
    unsigned char* temp;

    if ((file = fopen(filename, "w")) == NULL)
	{
	    printf("ERROR: file open failed\n");
	    return(-1);
	}

   if (binsave == 1)
      fprintf(file,"P5\n");
   else
      fprintf(file,"P2\n");

    if (comment_string != NULL)
	fprintf(file,"# %s \n", comment_string);

    fprintf(file,"%d %d \n", w, h);

    maxval = 0;
    for (i = 0; i < w; i++)
        for (j=0; j < h; j++)
	    if ((int)data[i][j] > maxval)
	        maxval = (int)data[i][j];

    fprintf(file, "%d \n", maxval);

    if (binsave == 1)
    {
	temp = (unsigned char*)calloc(w*h, sizeof(unsigned char));

	for(i=0; i<w; i++)
           for(j=0; j<h; j++)
               temp[(j*w)+i]= (unsigned char)data[i][j];

        nread = fwrite((void*)temp, sizeof(unsigned char), (w)*(h), file);
	printf("Writing to %s as binary.\n", filename);
        free(temp);

    }else{
	printf("Writing to %s as ascii.\n", filename);

	for(i=0; i<h; i++)
           for(j=0; j<w; j++)
		fprintf(file,"%d ", (int)data[j][i]);

    }

    fclose(file);
    return(0);
}

int main()
{
  printf("Hello from Nios II!\n");

  int w = 512, h = 512;
  const char* filename = "/mnt/host/inputImage.pgm";

  filtrado(filename, w, h);

  printf("Termino");

  return 0;
}

int filtrado(const char* filename, int w, int h)
{
	int i,j;
	int filtro_w = 3, filtro_h = 3;

	unsigned char **filtro;
	filtro = (unsigned char**)calloc((filtro_w), sizeof(unsigned char*));

	for(i=0; i<w; i++)
		filtro[i] = (unsigned char**)calloc((filtro_h), sizeof(unsigned char*));

	filtro[0][0] = 20;
	filtro[0][1] = 50;
	filtro[0][2] = 20;
	filtro[1][0] = 50;
	filtro[1][1] = 60;
	filtro[1][2] = 50;
	filtro[2][0] = 20;
	filtro[2][1] = 50;
	filtro[2][2] = 20;

	unsigned char **data_dest;
	data_dest = (unsigned char**)calloc((w-2), sizeof(unsigned char*));

	for (i=0 ; i<w; i++)
		data_dest[i] = (unsigned char*)calloc((h-2), sizeof(unsigned char));

	unsigned char **data = pgmread(filename, &w, &h);

	alt_u32 time1;
	alt_u32 time2;
	alt_u32 time3;

	if(alt_timestamp_start() < 0)
	{
		printf("No timestamp device available\n");
	}
	else
	{
		time1 = alt_timestamp();

		for(i=1; i<(w-1); i++){
			for(j=1; j<(h-1); j++){
				char pixel = 0;
				int calculo = (int)filtro[0][0] * (int)data[i-1][j-1];
				calculo += (int)filtro[0][1] * (int)data[i][j-1];
				calculo += (int)filtro[0][2] * (int)data[i+1][j-1];
				calculo += (int)filtro[1][0] * (int)data[i-1][j];
				calculo += (int)filtro[1][1] * (int)data[i][j];
				calculo += (int)filtro[1][2] * (int)data[i+1][j];
				calculo += (int)filtro[2][0] * (int)data[i-1][j+1];
				calculo += (int)filtro[2][1] * (int)data[i][j+1];
				calculo += (int)filtro[2][2] * (int)data[i+1][j+1];

				pixel = calculo/900;

				data_dest[i-1][j-1] = pixel;
			}
		}

		time2 = alt_timestamp();

		printf("Time filtering the image = %u ticks\n", (unsigned int) (time2 -time1));
		printf("Number of ticks per second = %u\n", (unsigned int)alt_timestamp_freq());
	}

	const char* filedest = "/mnt/host/ImpageDest.pgm";
	pgmwrite(filedest, w-2, h-2, data_dest, NULL, 1);

	return (0);
}
