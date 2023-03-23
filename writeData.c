#include <stdio.h>
#include <stdlib.h>

#include "pgm.h"
#include "writeData.h"
#include "pgmErrors.h"


int write_data(PGM *pgm, char *filename){
	
	
	
	/* we will store ONE comment	         */
	char *commentLine = NULL;
	/* pointer to raw image data	         */
	unsigned char *imageData = NULL;
	unsigned short *magic_Number =NULL;
	
	int width=pgm->width;
	int height=pgm->height;
	int maxGray=pgm->maxGray;
	commentLine=pgm->commentLine;
	magic_Number=pgm->magic_Number;
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
		ExitWithError(Output_Failed, filename);
	} /* NULL output file */

	/* write magic number, size & gray value */
	size_t nBytesWritten;
	if (*magic_Number == MAGIC_NUMBER_ASCII_PGM){
		nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", width, height, maxGray);
	}
	else{
		nBytesWritten = fprintf(outputFile, "P5\n%d %d\n%d\n", width, height, maxGray);
	}
	

	/* check that dimensions wrote correctly */
	if (nBytesWritten < 0)
	{ /* dimensional write failed    */
		/* free memory                   */
		free(commentLine);
		free(imageData);

		/* print an error message        */
		ExitWithError(Output_Failed, filename);
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
			ExitWithError(Output_Failed, filename);
		} /* data write failed   */
	} /* per gray value */
}
