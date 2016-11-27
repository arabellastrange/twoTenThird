/* Loads the instructions from a file and stores its contents into the memory */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "data"

void load_from_file();

int array[32][8];

int main(int argc, char * argv[]){
	if(argc < 1){
		printf("Missing arguments, programme terminated \n");
	}
	if(!strcmp(argv[1], -d)){
		printf("will load default memory\n");
		load_default_memory();
	}
	if(!strcmp(argv[1], -c )){
		printf("will read from console \n");
		read_from_console(array);
	}
	if(!strcmp(argv[1], -f)){
		printf("will read from file \n");
		load_from_file();
	}
	else{
		printf("Invalid argument, programme terminated\n");
	}
	return 1;
}

void load_from_file(){
	FILE *file_pointer;
	file_pointer = fopen(INPUT_FILE, "r");

	char line[9];

	if(file_pointer == NULL){
		printf("Failed to open file \n");
		exit(EXIT_FAILURE);
	}
	else{
		while(fgets(line, sizeof(line), file_pointer)){
			printf("%s\n", line);
			int n;
			int m;
			for(n = 0; n < 32; n++){
				for (m = 0; m < 8; m++)
				{
					array[n][m] = line[m];
				}
			}
		}
	}

	fclose(file_pointer);
}
