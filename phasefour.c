/* Loads the instructions from a file and stores its contents into the memory */
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "data"

void load_from_file();

int array[32][8];

int main(){
 	load_from_file();
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
