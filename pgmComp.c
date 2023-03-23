#include <stdio.h>
#include <stdlib.h>

#include "pgmComp.h"
#include "readData.h"
#include "pgmErrors.h"


int main(int argc, char **argv) {

	//pointer for the pgm structure
	PGM*pgm=NULL;
	PGM*pgm1=NULL;
	PGM*pgm2=NULL;

	if (argc != 3) {
		/* wrong arg count */
		/* print an error message        */
		printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
		/* and return an error code      */
		ExitWithError(Bad_Argument_Count, NULL);
	} /* wrong arg count */

	char *filename1 = argv[1];
	char *filename2 = argv[2];

	pgm1 = read_data(pgm, filename1);
	pgm2 = read_data(pgm, filename2);

	if(pgm1->width == pgm2->width && pgm1->height == pgm2->height) {
		for (int i = 0; i<pgm1->width*pgm1->height;i++){
			if(pgm1->imageData[i] == pgm1->imageData[i]){
				continue;
			}
			else{
				printf("The two files were not logically");
				return 0;
			}
		}
		printf("The two files were logically identical");
		return 0;

	} else {
		printf("The two files were not logically");
		return 0;
	}

}
