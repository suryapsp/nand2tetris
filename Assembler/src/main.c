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
   
    //Skip Empty Instruction
   if(line[0] == '\0'){
        return;
    }

    char instructions[100];
    sscanf(line, "%s", instructions);
    char binary[100];

    //Handle A instruction
    if(instructions[0] == '@'){
       int address = atoi(instructions+1);
       sprintf(binary, "0%015d\n", address);
    }

    //Handle C instruction
    char *dest = strtok(instructions, "=");
    char *comp = strtok(NULL, ";");
    char *jump = strtok(NULL, "\r\n\t ");

    char *comp_codes[] = {"0", "1", "-1", "D", "A", "!D", "!A", "-D", "-A", "D+1", "A+1", "D-1", "A-1", "D+A", "D-A", "A-D", "D&A", "D|A", "M", "!M", "-M", "M+1", "M-1", "D+M", "D-M", "M-D", "D&M", "D|M"};
    char* dest_codes[] = {"", "M", "D", "MD", "A", "AM", "AD", "AMD"};
    char* jump_codes[] = {"", "JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP"};

    int i;
    for(i = 0; i < 28; i++){
        if(strcmp(comp, comp_codes[i]) == 0)
            break;
    }

    char comp_code = (char)(i < 28 ? '0' + i / 8 : '0');

    char comp_bits[4] = {(i & 4) ? '1' : '0', (i & 2) ? '1' : '0', (i & 1) ? '1' : '0', '\0'};

    for (i = 0; i < 8; i++) {
            if (strcmp(dest, dest_codes[i]) == 0) break;
    }
    char dest_bits[4] = {(i & 4) ? '1' : '0', (i & 2) ? '1' : '0', (i & 1) ? '1' : '0', '\0'};

    for (i = 0; i < 8; i++) {
        if (strcmp(jump, jump_codes[i]) == 0) break;
    }
    char jump_bits[4] = {(i & 4) ? '1' : '0', (i & 2) ? '1' : '0', (i & 1) ? '1' : '0', '\0'};
    
    sprintf(binary, "111%s%s%s\n", comp_bits, dest_bits, jump_bits);

    fprintf(output, "%s", binary);

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

    fclose(input);
    fclose(output);
	
}
