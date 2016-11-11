#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void load_default_memory();
void decimal_to_binary(int dec, char bin[]);
int binary_to_decimal(char bin[]);
int power(double exp);

/*calls our functions*/
int main()
{
	char bin2[8] = {0};
	char bin[8] = {'0', '0', '0', '0', '0', '1', '1', '1'};

	load_default_memory();
	decimal_to_binary(10, bin2); /*should return 00001010*/
	printf("translation: %i \n", binary_to_decimal(bin)); /*should return 7*/

	return 0;
}


/*loads some random binary numbers into the array*/
void load_default_memory(){
	int array[32][8];
	int n;
	int m;
	srand(time(NULL));

	for(n = 0; n < 32; n++){
		for(m = 0; m < 8; m++){
			int r = rand() % 2;
			array[n][m] = r;
		}
	}

	/*for(n = 0; n < 32; n++){
		printf("this binary number is: ");
		for(m = 0; m < 8; m++){
			 printf("%i ", array[n][m]);
		}
		printf("\n");
	}*/
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
			if(bin[m] != 48){
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
