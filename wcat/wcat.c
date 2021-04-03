#include <stdio.h>

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

}

int main(int argc, char *argv[]) {

	if( !validate_input(argc, argv) ) {
		return 0;
	}

	read_content(argv[argc - 1]);

	return 0;
}
