#include <stdio.h>
#include <stdlib.h>

long get_file_length(FILE **file) {
	fseek((*file), 0, SEEK_END);
	long length = ftell(*file);
	fseek((*file), 0, SEEK_SET);

	return length;
}

int validate_input(int argc, char **argv) {
	
	if(argc < 2) {
		printf("You must enter a file to be read.\n");
		return 0;
	}

	return 1;

}

void read_content(char *filename) {
	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		printf("ERROR: Could not find file: %s\n", filename);
	}

	long length = get_file_length(&file);

	char *buffer = malloc(length * sizeof(char));
	if (buffer != NULL) {
		fread(buffer, 1, length, file);
		printf("%s", buffer);
	}

	fclose(file);
}

int main(int argc, char *argv[]) {

	if( !validate_input(argc, argv) ) {
		return 0;
	}

	read_content(argv[argc - 1]);

	return 0;
}
