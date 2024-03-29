#include <stdio.h>
#include <stdlib.h>

#include "pgm.h"
#include "readData.h"
#include "writeData.h"
#include "pgmError.h"



/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char **argv) {

	//pointer for the pgm structure
	PGM*pgm=NULL;

	if (argc != 3)	
	{ /* wrong arg count */
		/* print an error message        */
		printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
		/* and return an error code      */
		ExitWithError(Bad_Argument_Count, NULL);
	} /* wrong arg count */
	

	char *r_filename=argv[1];
	
	char *w_filename=argv[2];
	pgm =read_data(pgm, r_filename);
	write_data(pgm, w_filename);


	return EXIT_NO_ERRORS;
}