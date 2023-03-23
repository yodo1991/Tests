#include <stdio.h>
#include <stdlib.h>
#define NUM_ERROR_STRINGS 12
#define ERROR_UNKNOWN 11

char *errorFormatStrings[NUM_ERROR_STRINGS] =
		{
			"SUCCESS: No Error\n",
			"ERROR:Bad Argument Count\n",
			"ERROR: Bad File Name (%s)\n",
			"ERROR: Bad Magic Number (%s)\n",
			"ERROR: Bad Comment Line (%s)\n",
			"ERROR: Bad Dimensions (%s)\n",
			"ERROR: Bad Max Gray Value (%s)\n",
			"ERROR: Image Malloc Failed\n",
			"ERROR: Bad Data (%s)\n",
			"ERROR: Output Failed (%s)\n",
			"ERROR: Miscellaneous (%s)\n",
			"ERROR: Unknown(%s)\n"
		};

void ExitWithError(int errorCode, char*errorStringInsertion){
	if ((errorCode < 0) || (errorCode >= NUM_ERROR_STRINGS)){
		errorCode = ERROR_UNKNOWN;
	}
	if (errorStringInsertion ==NULL){
		printf(errorFormatStrings[ERROR_UNKNOWN], "Bad Error String!"); 
	}
	printf(errorFormatStrings[errorCode], errorStringInsertion);
	exit(errorCode);
}
