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
void run();

void halt();
void load(int operand[5]);
void loadC(int operand[5]);
void store(int operand[5]);
void add(int operand[5]);
void sub(int operand[5]);
void jump(int operand[5]);
void jumpZ(int operand[5]);

int array[32][8];
int ACC = 0;
int IP = 0;
char instruct[4];

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
	run();
}

/*loads values into a global 32x8 array based on user input*/
void read_from_console(int array[32][8]){
	int n = 0;
	int m;
	char option;

	printf("Enter 'I' to add a new instruction or 'Q' to exit and run program: ");
	scanf("%c", &option);

	while(option != 81){
		printf("Enter the binary string you would like to add: ");

		for(m = 0; m < 8; m++){
				scanf("%1i", &array[n][m]); /*read one character*/
		}

		n++;

		printf("Your command: ");
		scanf(" %c", &option);
	}

	display_memory(array);
	run();
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
			printf("\n");
			for(n = 0; n < 32; n++){
				for (m = 0; m < 8; m++)
				{
					if(line[n + m] == 48){
						array[n][m] = 0;
					}
					else{
						array[n][m] = 1;
					}
				}
			*line = *line + 9;
			}
		}
	}

	fclose(file_pointer);
	display_memory(array);
	run();
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

void run(){
	if(IP < 32){
		convert_to_assembly(array);
	}
	else{
		printf("that address does not exit \n");
	}
}

/* Converts the memory contents to assembly language and displays the results on the screen */
void convert_to_assembly(int array[32][8]){
	int n;
	int m = 0;
	int o[5];
	char add[] = "0";

	printf("pointer: %i\n", IP);
	printf("the instruction at this row is: ");
	/*read the op of this instruction store it*/
	for(m = 3; m < 8; m++){
		o[m] = array[IP][m];
	}

	for(m = 0; m < 3; m++){
		if(array[IP][n] == 0){
			add[0] = '0';
		}
		else{
			add[0] = '1';
		}
		instruct = strcat(instruct, add);
	}

	printf("%s \n", instruct);

	if(!strcmp(instruct, '000')){
		printf("Halt execution of the program.\n");
		halt();
		break;
	}
	else if(!strcmp(instruct, '001')){ 
		printf("Load a copy of the value in the referenced memory location. \n");
		load(o);
		continue;
	}
	else if(!strcmp(instruct, '010')){
		printf("Load the constant value of the operand in the accumulator.\n");
		loadC(o);
		continue;
	}
	else if(!strcmp(instruct, '011')){ 
		printf("Store a copy of the contents of the accumulator.\n");
	  	load(o);
	  	continue;
	}
	else if(!strcmp(instruct, '100')){
		printf("Add the value in the referenced memory location to the value in the accumulator.\n");
		add(o);
		continue;
	}
	else if(!strcmp(instruct, '101')){
		printf("Subtract the value in the referenced memory location from the value in the accumulator.\n");
		sub(o);
		continue;
	}
	else if(!strcmp(instruct, '110')){
		printf("Jump to the referenced memory location if the value of the accumulator is a positive number.\n");
		jump(o);
		continue;
	}
	else if(!strcmp(instruct, '111')){
		printf("Jump to the referenced memory location if the value of the accumulator is 0.\n");
		jumpZ(o);
		continue;
	}
	else{
		printf("No instruction matched \n");
	}
	for(m = 0; m < 3; m++){
		instruct[m] = "\0";
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
	printf("Loaded: %i\n", ACC);
	IP = current;
	IP++;
	run();
}

void loadC(int operand[5]){
	ACC = binary_to_decimal(operand);
	printf("Loaded: %i\n", ACC);
	IP++;
	run();
}

void store(int operand[5]){
	int m;
	int val[8];
	decimal_to_binary(ACC, val);
	int current = IP;
	IP = binary_to_decimal(operand);
	for(m = 0; m < 8; m++){
		array[IP][m] = val[m];
	}
	IP = current;
	IP++;
	run();
}

void add(int operand[5]){
	int current = IP;
	int constant[5];
	int m;
	IP = binary_to_decimal(operand);
	for(m = 0; m < 8; m ++){
		constant[m] = array[IP][m];
	}
	ACC = ACC + binary_to_decimal(constant);
	printf("Result: %i \n", ACC);
	IP = current;
	IP++;
	run();
}

void sub(int operand[5]){
	int current = IP;
	int constant[5];
	int m;
	IP = binary_to_decimal(operand);
	for(m = 0; m < 8; m ++){
		constant[m] = array[IP][m];
	}
	ACC = ACC - binary_to_decimal(constant);
	printf("Result: %i \n", ACC);
	IP = current;
	IP++;
	run();
}

void jump(int operand[5]){
	if(ACC > 0){
		IP = binary_to_decimal(operand);
	}
	run();
}

void jumpZ(int operand[5]){
	if(ACC == 0){
		IP = binary_to_decimal(operand);
	}
	run();
}
