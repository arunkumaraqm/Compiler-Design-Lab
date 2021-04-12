#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SYMBOLS 225
#define MAX_OPS 225
#define SIC_WORD_SIZE 3
#define INSTRUCTION_LEN SIC_WORD_SIZE

typedef char String [225];

String START = "start", WORD = "word", BYTE = "byte", RESW = "resw", RESB = "resb", END = "end";

bool equals(String one, String two)
{
	return strcmp(one, two) == 0;
}

bool linear_search_string(String *array, int size, String key)
{
	for (int i = 0; i < size; ++i)
	{
		if (equals(array[i], key))
		{
			return true;
		}
	}
	return false;
}
void load_optab(String optab_mnemonic[MAX_OPS], int *optab_size)
{
	FILE *fin = fopen("optab.tsv", "r");
	*optab_size = 0;
	while (!feof(fin))
	{
		String mnemonic; int opcode;
		fscanf(fin, "%s %d", mnemonic, &opcode);

		strcpy(optab_mnemonic[*optab_size], mnemonic);
		(*optab_size)++;
	}
	fclose(fin);
}

int main(int argc, char const *argv[])
{
	// if (argc != 2)
	// {
	// 	printf("Usage: ./a.out foo.asm\n");
	// 	return 1;
	// }

	// const char *filename = argv[1];
	const char *filename = "test.asm";
	// printf("%s\n", filename);//

	FILE* fin = fopen(filename, "r");

	String label, mnemonic, operand;
	String symtab_label[MAX_SYMBOLS];
	int symtab_loc[MAX_SYMBOLS];
	int symtab_size = 0;

	String optab_mnemonic[MAX_OPS];
	int	optab_size = 0;
	load_optab(optab_mnemonic, &optab_size);

	int locctr = 0, noof_lines = 0, starting_address;
	bool found_end = false;

	while (true)
	{
		int status = fscanf(fin, "%s %s %s", label, mnemonic, operand);
		++ noof_lines;

		{
			if (label[0] == '.') // line is a comment jkkjk
			{
				;
			}
			else if (equals(mnemonic, START) && noof_lines == 1)
			{
				starting_address = atoi(operand);
				locctr = starting_address;

				// The label here is actually the name of the program
				// It probably shouldn't be added to symtab
				{
					// Insert entry into symtab
					strcpy(symtab_label[symtab_size], label);
					symtab_loc[symtab_size] = locctr;
					++ symtab_size;
				}

			}
			else 
			{
				if (label[0] == '-')
				{
					;
				}
				else
				{
					if (linear_search_string(symtab_label, symtab_size, label))
					{
						printf("Label declared multiple times.\n");
						break;
					}
					else
					{
						// Insert entry into symtab
						strcpy(symtab_label[symtab_size], label);
						symtab_loc[symtab_size] = locctr;
						++ symtab_size;
					}
				}

				if (linear_search_string(optab_mnemonic, optab_size, mnemonic))
				{
					locctr += INSTRUCTION_LEN;
				}
				else if (equals(mnemonic, WORD))
				{
					locctr += SIC_WORD_SIZE;
				}
				else if (equals(mnemonic, RESW))
				{
					locctr += SIC_WORD_SIZE * atoi(operand);
				}
				else if (equals(mnemonic, RESB))
				{
					locctr += 1 * atoi(operand);
				}
				else if (equals(mnemonic, BYTE))
				{
					locctr += strlen(operand) - 3; // eg: foo byte c"hey"
				}
				else if (equals(mnemonic, END))
				{
					found_end = true;
					break;
				}
				else
				{
					printf("Invalid mnemonic %s.\n", mnemonic);
					found_end = true;
					break;
				}
			}
		}

		if (feof(fin))
		{
			break;
		}
	}

	// for (int i = 0; i < symtab_size; ++i)
	// {
	// 	printf("%s %d\n", symtab_label[i], symtab_loc[i]);
	// }

	if (!found_end)
	{
		printf("No END.\n");
		return 0;
	}
	int program_length = locctr - starting_address;
	printf("program_length %d\n", program_length);


	return 0;
}