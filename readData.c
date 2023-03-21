
#include <stdio.h>
#include <stdlib.h>

#include "pgm.h"
#include "readData.h"
#include "pgmError.h"



PGM *read_data(PGM *pgm, char *filename) {

	// allocate the PGM data structure
	pgm = (PGM *)malloc(sizeof(PGM));

	/* variables for storing the image       */
	/* this is NOT good modularisation       */
	/* and you will eventually replace it    */
	/* for now, leave it here                */

	/* the magic number		         */
	/* stored as two bytes to avoid	         */
	/* problems with endianness	         */
	/* Raw:    0x5035 or P5		         */
	/* ASCII:  0x5032 or P2		         */
	unsigned char magic_number[2] = {'0','0'};
	unsigned short *magic_Number = (unsigned short *) magic_number;

	/* we will store ONE comment	         */
	char *commentLine = NULL;

	/* the logical width & height	         */
	/* note: cannot be negative	         */
	unsigned int width = 0, height = 0;

	/* maximum gray value (assumed)	         */
	/* make it an integer for ease	         */
	unsigned int maxGray = 255;

	/* pointer to raw image data	         */
	unsigned char *imageData = NULL;


	/* now start reading in the data         */
	/* try to open the file for text I/O     */
	/* in ASCII mode b/c the header is text  */
	FILE *inputFile = fopen(filename, "r");

	if (inputFile == NULL) {
		ExitWithError(Bad_File_Name,filename);
	}

	/* read in the magic number              */
	magic_number[0] = getc(inputFile);
	magic_number[1] = getc(inputFile);

	/* sanity check on the magic number      */
	if (*magic_Number != MAGIC_NUMBER_ASCII_PGM) {
		/* failed magic number check   */
		/* be tidy: close the file       */
		fclose(inputFile);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", filename);

		/* and return                    */
		ExitWithError(Bad_Magic_Number,filename);
	} /* failed magic number check   */

	/* scan whitespace if present            */
	int scanCount = fscanf(inputFile, " ");

	/* check for a comment line              */
	char nextChar = fgetc(inputFile);
	if (nextChar == '#') {
		/* comment line                */
		/* allocate buffer               */
		commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
		/* fgets() reads a line          */
		/* capture return value          */
		char *commentString = fgets(commentLine, MAX_COMMENT_LINE_LENGTH, inputFile);
		/* NULL means failure            */
		if (commentString == NULL) {
			/* NULL comment read   */
			/* free memory           */
			free(commentLine);
			/* close file            */
			fclose(inputFile);

			/* print an error message */
			printf("Error: Failed to read pgm image from file %s\n", filename);

			/* and return            */
			ExitWithError(Bad_Comment_Line,filename);
		} /* NULL comment read   */
	} /* comment line */
	else {
		/* not a comment line */
		/* put character back            */
		ungetc(nextChar, inputFile);
	} /* not a comment line */

	/* read in width, height, grays          */
	/* whitespace to skip blanks             */
	scanCount = fscanf(inputFile, " %u %u %u", &(width), &(height), &(maxGray));

	/* sanity checks on size & grays         */
	/* must read exactly three values        */
	if 	(
	    (scanCount != 3				)	||
	    (width 	< MIN_IMAGE_DIMENSION	) 	||
	    (width 	> MAX_IMAGE_DIMENSION	) 	||
	    (height < MIN_IMAGE_DIMENSION	) 	||
	    (height > MAX_IMAGE_DIMENSION	) 	||
	    (maxGray	!= 255		)
	) {
		/* failed size sanity check    */
		/* free up the memory            */
		free(commentLine);

		/* be tidy: close file pointer   */
		fclose(inputFile);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", filename);

		/* and return                    */
		ExitWithError(Bad_Dimensions,filename);
	} /* failed size sanity check    */

	/* allocate the data pointer             */
	long nImageBytes = width * height * sizeof(unsigned char);
	imageData = (unsigned char *) malloc(nImageBytes);

	/* sanity check for memory allocation    */
	if (imageData == NULL) {
		/* malloc failed */
		/* free up memory                */
		free(commentLine);

		/* close file pointer            */
		fclose(inputFile);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", filename);

		/* return error code             */
		ExitWithError(Image_Malloc_Failed,filename);
	} /* malloc failed */

	/* pointer for efficient read code       */
	for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++) {
		/* per gray value */
		/* read next value               */
		int grayValue = -1;
		int scanCount = fscanf(inputFile, " %u", &grayValue);

		/* sanity check	                 */
		if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255)) {
			/* fscanf failed */
			/* free memory           */
			free(commentLine);
			free(imageData);

			/* close file            */
			fclose(inputFile);

			/* print error message   */
			printf("Error: Failed to read pgm image from file %s\n", filename);

			/* and return            */
			ExitWithError(Bad_Max_Gray_Value,filename);
		} /* fscanf failed */

		/* set the pixel value           */
		*nextGrayValue = (unsigned char) grayValue;
	} /* per gray value */

	pgm->width=width;
	pgm->height=height;
	pgm->maxGray=maxGray;
	pgm->commentLine=commentLine;
	pgm->imageData=imageData;
	pgm->magic_Number=magic_Number;
	pgm->magic_number[0]=magic_number[0];
	pgm->magic_number[1]=magic_number[1];

	/* we're done with the file, so close it */
	fclose(inputFile);

	return pgm;
}


