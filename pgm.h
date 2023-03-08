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
#define MAX_COMMENT_LINE_LENGTH 1288
