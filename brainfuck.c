#include <stdio.h>

#define PROGRAM_SIZE 30000
#define DATA_SIZE 30000

int valid_char(char);
void print_program_code(char *);

int main(int argc, char **argv) {
	char program[PROGRAM_SIZE];
	unsigned char program_data[DATA_SIZE];

	char *filename;
	FILE *file = stdin;
	if(argc == 2) {
		filename = argv[1];
		file = fopen(filename, "r");
	}

	int i = 0;
	while(i < DATA_SIZE) {
		program_data[i++] = 0;
	}
	
	int idx = 0;
	int in;
    int comment = 0;
	while(1) {
        in = getc(file);

        if(in == EOF) {
            program[idx] = '&';
            break;

        } else if(in == '\n') {
            comment = 0;

        } else if(in == '#') {
            comment = 1;

        } else if(!comment && valid_char(in)) {
            program[idx++] = in;
        }
	}
	
	//print_program_code(program);

	char *instruction_ptr = program;
	
	unsigned char *data_ptr = program_data;

	char cur_instruction;
	while(1) {
		cur_instruction = *instruction_ptr;
		if(cur_instruction == '>') {
			data_ptr++;
		} else if(cur_instruction == '<') {
			data_ptr--;
		} else if(cur_instruction == '+') {
			++*data_ptr;
		} else if(cur_instruction == '-') {
			--*data_ptr;
		} else if(cur_instruction == '.') {
			putchar(*data_ptr);
		} else if(cur_instruction == ',') {
			*data_ptr = getchar();
		} else if(cur_instruction == '[') {
			if(*data_ptr == 0) {
				// Find the matching closing brace
				instruction_ptr++;
				int opening_braces = 1;
				while(opening_braces) {
					if(*instruction_ptr == '[') {
						opening_braces++;
					} else if(*instruction_ptr == ']') {
						opening_braces--;
					}
					instruction_ptr++;
				}
				instruction_ptr--;
			}
		} else if(cur_instruction == ']') {
			if(*data_ptr != 0) {
				// Find the matching opening brace
				instruction_ptr--;
				int closing_braces = 1;
				while(closing_braces) {
					if(*instruction_ptr == '[') {
						closing_braces--;
					} else if(*instruction_ptr == ']') {
						closing_braces++;
					}
					instruction_ptr--;
				}
				// Command after the matching [
				instruction_ptr++;
			}
		} else if(cur_instruction == '&') {
			break;
		} else {
			break;
		}

		instruction_ptr++;
	}

	return 0;
}

int valid_char(char a) {
	return (a == '.' || a == ',' || a == '+' || a == '-' || a == '<' || a == '>' || a == '[' || a == ']');
}

void print_program_code(char *program) {
	int idx = 0;
	while(1) {
		if(program[idx] == '&') {
			break;
		}
		putchar(program[idx++]);
	}
	putchar('\n');
}
