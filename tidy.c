#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define INPUT_FILE "data"

void load_default_memory();
void load_from_file();
void read_from_console(int array[32][8]); 
void display_memory(int array[32][8]);

void convert_to_assembly(int array[32][8]);
void decimal_to_binary(int dec, int bin[]);
int binary_to_decimal(int bin[]);
int power(double exp);
int conc(int m);

void halt();
void load(int *operand);
void loadC(int operand);
void store(int *operand);
void add(int *operand);
void sub(int *operand);
void jump(int *operand);
void jumpZ(int *operand);

int array[32][8];
int ACC;
int IP;
int instruct;

/*calls appropiate data inout method based on argument form user*/
int main(int argc, char * argv[]){
	if (argc == 2){
		if (!strcmp(argv[1],"-d")){
			printf("will load default memory\n");
			load_default_memory();
		}
		else if(!strcmp(argv[1],"-c")){
			printf("will read from console \n");
			read_from_console(array);
		}
		else if(!strcmp(argv[1],"-f")){
			printf("will read from file \n");
			load_from_file();
		}
		else{
			printf("Invalid argument, program terminated\n");
		}
	}
	else {
		printf("Missing or too many arguments, program terminated \n");
	}
	return 1;
}

/*loads random 1s and 0s into a global 32x8 array*/
void load_default_memory(){
	int n;
	int m;
	srand(time(NULL));

	for(n = 0; n < 32; n++){
		for(m = 0; m < 8; m++){
			int r = rand() % 2;
			array[n][m] = r;
		}
	}
	display_memory(array);
}

/*loads values into a global 32x8 array based on user input*/
void read_from_console(int array[32][8]){
	int n;
	int m;
	for(n = 0; n < 32; n++){
		printf("Enter the binary string you would like to add: ");
	
		for(m = 0; m < 8; m++){
				scanf("%1i", &array[n][m]); /*read one character*/
		}
	}
	display_memory(array);
}

/*loads values into a global 32x8 array based on an input file*/
void load_from_file(){
	int n;
	int m;
	FILE *file_pointer;
	file_pointer = fopen(INPUT_FILE, "r");

	char line[9];

	if(file_pointer == NULL){
		printf("Failed to open file \n");
		exit(EXIT_FAILURE);
	}
	else{
		while(fgets(line, sizeof(line), file_pointer)){
			printf("%s", line);
			for(n = 0; n < 32; n++){
				for (m = 0; m < 8; m++)
				{
					/*array[n][m] = line[m];*/
					if(line[m] == 48){
						array[n][m] = 0;
					}
					else{
						array[n][m] = 1;
					}
				}
			}
		}
	}

	fclose(file_pointer);
	display_memory(array);
}

/*prints the contents of memory to screen*/
void display_memory(int array[32][8]) {
	int n;
	int m;
	for(n = 0; n < 32; n++){
		printf("this binary number at row %i is: ", n);
		for(m = 0; m < 8; m++){
			 printf("%i ", array[n][m]);
		}
		printf("\n");
	}
}

/* Converts the memory contents to assembly language and displays the results on the screen */
void convert_to_assembly(int array[32][8]){
	int n;
	int m = 0;
	for(n = 0; n < 32; n++){
		printf("the instruction at this row is: ");

		for (m = 0; m < 3; m++){
			instruct = conc(array[n][m]);
			printf("%i", instruct);
		}

		printf("\n");

		switch(instruct){
			case 000: printf("Halt execution of the program.\n"); 
					  break;
			case 001: printf("Load a copy of the value in the referenced memory location. \n");
					  break;
			case 010: printf("Load the constant value of the operand in the accumulator.\n"); 
					  break;
			case 011: printf("Store a copy of the contents of the accumulator.\n");
					  break;
			case 100: printf("Add the value in the referenced memory location to the value in the accumulator.\n");
					  break;
			case 101: printf("Subtract the value in the referenced memory location from the value in the accumulator.\n");
					  break;
			case 110: printf("Jump to the referenced memory location if the value of the accumulator is a positive number.\n");
					  break;
			case 111: printf("Jump to the referenced memory location if the value of the accumulator is 0.\n");
					  break;
		}

		instruct = '\0';			
	}
}

/*translate from decimal to binary*/
void decimal_to_binary(int dec, int bin[]){
	int i;

	for(i = 7; i >= 0; i--){
			bin[i] = dec%2;
			dec = dec/2;
	}

	printf("translation: ");
	for(i = 0; i < 8; i++){
		printf("%i ", bin[i]);
	}
	printf("\n");
}

/*translate from binary to decimal*/
int binary_to_decimal(int bin[]){
	int m;
	int dec = 0;
		for (m = 0; m < 8; m++)
		{
			if(bin[m] != 0){
				dec = dec + power(m);
			}
		}
	return dec;
}

/*raises 2 to the power of the appropriate index for dicmal translation*/
int power(double exp){
	exp = 7.0 - exp;
	if(exp == 7){
		return -128;
	}
	else{
		return pow(2.0, exp);
	}
}

/*concatenate the first three digits from the bin number for comparision*/
int conc(int m){
    return (instruct << 1) | m;
}

/*actual computer functions*/
void halt(){
	printf("Goodbye! \n");
	IP++;
}

void load(int *operand){
	ACC = *operand;
	IP++;	
}

void loadC(int operand){
	ACC = operand;
	IP++;
}

void store(int *operand){
	*operand = ACC;
	IP++;
}

void add(int *operand){
	ACC = ACC + *operand;
	IP++;
}

void sub(int *operand){
	ACC = ACC - *operand;
	IP++;
}

void jump(int *operand){
	if(ACC > 0){
		IP = binary_to_decimal(operand);
	}
}

void jumpZ(int *operand){
	if(ACC == 0){
		IP = binary_to_decimal(operand);
	}
}