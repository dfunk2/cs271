/****************************************
 * C-ploration 3 for CS 271
 * 
 * Denise Funk
 * FALL 2024
 * Synopsis: using c to handle files.
 ****************************************/
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
#define MAX_LINE_LENGTH 200

int main(int argc, const char *argv[])
{
	//if incorrect number of arguments
	if(argc != 2) {
	printf("Usage: %s [filename]\n", argv[0]);
	exit(EXIT_FAILURE);
	}

	//open input file
	FILE *fin = fopen(argv[1], "r");

	if(fin == NULL) {
		perror("unable to open file!");
		exit(EXIT_FAILURE);
	}
	//create output file
	char out_file[strlen(argv[1]) + 6];
	strcpy(out_file, argv[1]);
	strcat(out_file, ".echo");

	//open output file
	FILE *fout = fopen(out_file, "w+");

	if(fout == NULL) {
	perror("unable to open file!");
	exit(EXIT_FAILURE);
	}

	//Reading the file
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;

	while(fgets(line, sizeof(line), fin)) {
		line_num++;
		printf("[%04d] %s", line_num, line);
		fprintf(fout, "%s", line);
	}

	//close file pointer
	fclose(fin);
	fclose(fout);


	return 0;
}
