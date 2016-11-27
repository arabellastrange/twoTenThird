#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void load_default_memory();
void display_memory(int array[32][8]);
void read_from_console(int array[32][8]); 
void convert_to_assembly(int array[32][8]);
void decimal_to_binary(int dec, char bin[]);
int binary_to_decimal(char bin[]);
int power(double exp);
int conc(int m);

int array[32][8];
int instruct;

/*calls our functions*/
int main(){
	char bin2[8];
	char bin[8];
	int i;

	load_default_memory();

	/*fill the binary array from local memory
	for (i = 0; i < 8; i++)
	{
		bin[i] = array[5][i];
	}

	decimal_to_binary(10, bin2);

	printf("translation: %i \n", binary_to_decimal(bin));*/

	read_from_console(array);

	convert_to_assembly(array);

	return 1;
}

/*loads some random binary numbers into the array*/
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
}

/* Displays the memory contents & respective locations*/
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

/* Prompts the user to input the memory contents from the console (i.e. command line), reads the
/* input in and stores it into the memory */
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
void decimal_to_binary(int dec, char bin[]){
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
int binary_to_decimal(char bin[]){
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

/*raises 2 to the power of the appropriate index*/
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
