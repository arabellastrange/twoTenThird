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
void load(int operand[5]);
void loadC(int operand[5]);
void store(int operand[5]);
void add(int operand[5]);
void sub(int operand[5]);
void jump(int operand[5]);
void jumpZ(int operand[5]);

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
	int o[5];
	for(n = 0; n < 32; n++){
		printf("the instruction at this row is: ");

		for (m = 0; m < 3; m++){
			instruct = conc(array[n][m]);
			printf("%i", instruct);
		}
		/*read the op of this instruction store it*/
		for(m = 3; m < 8; m++){
			o[m] = array[n][m];
		}
		printf("\n");

		switch(instruct){
			case 000: printf("Halt execution of the program.\n");
								halt();
					  		break;
			case 001: printf("Load a copy of the value in the referenced memory location. \n");
								load(o);
					  		break;
			case 010: printf("Load the constant value of the operand in the accumulator.\n");
								loadC(o)
					  		break;
			case 011: printf("Store a copy of the contents of the accumulator.\n");
								load(o);
					  		break;
			case 100: printf("Add the value in the referenced memory location to the value in the accumulator.\n");
								add(o);
					  		break;
			case 101: printf("Subtract the value in the referenced memory location from the value in the accumulator.\n");
								sub(o);
					  		break;
			case 110: printf("Jump to the referenced memory location if the value of the accumulator is a positive number.\n");
								jump(o);
					  		break;
			case 111: printf("Jump to the referenced memory location if the value of the accumulator is 0.\n");
								jumpZ(o);
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

void load(int operand[5]){
	int m;
	int current = IP;
	int constant[8];
	IP = binary_to_decimal(operand);
	for(m = 0; m <8; m++){
		constant[m] = array[IP][m];
	}
	ACC = binary_to_decimal(constant);
	IP = current;
	IP++;
}

void loadC(int operand[5]){
	ACC = binary_to_decimal(operand);
	IP++;
}

void store(int operand[5]){
	int m;
	int val = decimal_to_binary(ACC);
	int current = IP
	IP = binary_to_decimal(operand);
	for(m = 0; m < 8; m++){
		array[IP][m] = val[m];
	}
	IP = current;
	IP++;
}

void add(int *operand){
	ACC = ACC + *operand;
	printf("Result: %i \n", ACC);
	IP++;
}

void sub(int *operand){
	ACC = ACC - *operand;
	printf("Result: %i \n", ACC);
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
