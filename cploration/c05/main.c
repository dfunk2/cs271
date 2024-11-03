/****************************************
 * C-ploration 4 for CS 271
 * 
 * Denise Funk
 * Fall 2024
 * Synopsis: Makefile with parser.c, parser.h, and main.c
 ****************************************/
#include "parser.h"

int main(int argc, const char *argv[])
{	//check that one argument has been passed
	if(argc != 2) {
		printf("usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	//open input file
	FILE *fin = fopen(argv[1], "r");

	if(fin == NULL) {
		perror("unable to open file");
		exit(EXIT_FAILURE);
	}
	//Call parse function
	parse(fin);
	
	//close file pointer
	fclose(fin);

	return 0;
}


