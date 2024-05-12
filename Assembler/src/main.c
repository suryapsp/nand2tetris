#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parser(char *line, FILE *output){
	char *comments = strstr(line, "//");
	if(comments != NULL){
		*comments = '\0';
	}

    // removing leading whitespace
    while(*line == ' ' || *line == '\t'){
        line++;        
    }

    //removing new lines and other space
    char *end = line + strlen(line) - 1;
    while((end > line) && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')){
        end--;
    }
    *(end+1) = '\0';
    
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
		// return 1;
	}

	char line[100];
	while(fgets(line, 100, input) != NULL){
	    parser(line, output);
	}

	
}
