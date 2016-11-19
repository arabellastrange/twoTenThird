void convert_to_assembly(int array[32][8]){
	int n;
	int m = 0;
	for(n = 0; n < 32; n++){
		int instruct;
		printf("the instruction at this row is: ");

		for (m = 0; m < 4; m++)
			{
				/* code */
			}

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
	}
}