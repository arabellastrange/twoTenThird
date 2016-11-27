/*needed functionality: 
	- Halt (HLT)
	- Load from memory to ACC (LOD)
	- Load from contsant to ACC (LCD)
	- Store ACC in memory (STO)
	- Add ACC and memory, store in ACC (ADD)
	- Sub memory from ACC, store in ACC (SUB)
	- Jump if ACC is postive (JMP)
	- Jump if ACC is 0 (JMZ)*/

#include <stdio.h>

void halt();
void load(int *operand);
void loadC(int operand);
void store(int *operand)
void add(int *operand);
void sub(int *operand);
void jump(int *operand);
void jumpZ(int *operand);

int array[32][8];
int ACC;
int IP;
int instruct;

int main(int argc, char * argv[]){
	/*call methods basically*/
	printf("start execution\n");
}

void halt(){
	printf("Goodbye! \n");
	IP++;
	/*Exit?*/
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