#include <stdio.h>
#include <stdlib.h>

#include "pgm.h"
#include "writeData.h"

#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3


int write_data(PGM *pgm, char *filename){
	
	
	
	/* we will store ONE comment	         */
	char *commentLine = NULL;
	/* pointer to raw image data	         */
	unsigned char *imageData = NULL;
	
	int width=pgm->width;
	int height=pgm->height;
	int maxGray=pgm->maxGray;
	commentLine=pgm->commentLine;
	imageData=pgm->imageData;
	
	
	/* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

	/* check whether file opening worked     */
	if (outputFile == NULL)
	{ /* NULL output file */
		/* free memory                   */
		free(commentLine);
		free(imageData);

		/* print an error message        */
		printf("Error: Failed to write pgm image to file %s\n", filename);	

		/* return an error code          */
		return EXIT_BAD_OUTPUT_FILE;
	} /* NULL output file */

	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", width, height, maxGray);

	/* check that dimensions wrote correctly */
	if (nBytesWritten < 0)
	{ /* dimensional write failed    */
		/* free memory                   */
		free(commentLine);
		free(imageData);

		/* print an error message        */
		printf("Error: Failed to write pgm image to file %s\n", filename);	

		/* return an error code          */
		return EXIT_BAD_OUTPUT_FILE;
	} /* dimensional write failed    */
	
	/* define the dimension of output             */
	long nImageBytes = width * height * sizeof(unsigned char);
	

	/* pointer for efficient write code      */
	for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
	{ /* per gray value */
		/* get next char's column        */
		int nextCol = (nextGrayValue - imageData + 1) % width;

		/* write the entry & whitespace  */
		nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

		/* sanity check on write         */
		if (nBytesWritten < 0)
		{ /* data write failed   */
			/* free memory           */
			free(commentLine);
			free(imageData);

			/* print error message   */
			printf("Error: Failed to write pgm image to file %s\n", filename);	

			/* return an error code  */
			return EXIT_BAD_OUTPUT_FILE;
		} /* data write failed   */
	} /* per gray value */
}
