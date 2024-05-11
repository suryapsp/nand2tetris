#include <stdio.h>
#include <string.h>

void parser(char *line, FILE *output){
	
}

int main(int argc, char *argv[]){
	
	if(argc < 2){
		printf("no input file provided\n");
		return 1;
	}
	
	FILE *input, *output;
	
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "wb");
	
	if(input == NULL){
		printf("Input file %s can not be opened\n", argv[1]);
		return 1;
	}
	if(output == NULL){
		printf("Output file %s can not be created/overwritten\n", argv[2]);
		return 1;
	}

	char line[MAX_LINE_LENGTH];
	while(fgets(line, MAX_LINE_LENGTH, input) != NULL){
		parser(line, output)
	}
	
}
