#pragma once
typedef struct _pgm {
	unsigned char magic_number[2];
	unsigned short *magic_Number;
	char *commentLine;
	unsigned int width;
	unsigned int height;
	unsigned int maxGray;
	unsigned char *imageData;
} PGM;

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

#define Bad_Argument_Count 1 //Program given wrong # of arguments 
#define Bad_File_Name 2 //Program fails to open file 
#define Bad_Magic_Number 3 //File has an illegal magic number 
#define Bad_Comment_Line 4 //Program failed on comment line 
#define Bad_Dimensions 5 //File has illegal dimensions 
#define Bad_Max_Gray_Value 6 //Program failed on max gray value 
#define Image_Malloc_Failed 7 // Malloc failed to allocate memory 
#define Bad_Data 8 //Reading in data failed 
#define Output_Failed 9 //Writing out data failed 
#define Miscellaneous (text description) 100 // Any other error which is detected 
