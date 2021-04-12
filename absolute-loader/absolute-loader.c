#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
/*
Header record
1 - H
2-7 - Program name
8-13 Starting address of object program
14-19 lenght of obj program

Text record
1 - T
2-7 starting address of object code in this record
8-9 lenght of object cod ein this record
10-69 object code

End record
1 - E
2-7	address of first executable instruction in object program
*/

void remove_carets(char line[255])
{
	// Removes carets and changes to 1-based index
	char temp[255] = "temp";
	int j = 1;
	for (int i = 0; i < 255; ++i)
	{
		if (line[i] == '^')
		{
			;
		}
		else
		{
			temp[j++] = line[i];
		}
	}
	strcpy(line, temp);
}

void my_strcpy(char* src, char* dst, int nf_bits)
{
	for (int i = 0; i < nf_bits; ++i)
	{
		*dst = *src;
		src++;
		dst++;
	}
}

int read_number(char* string, int size)
{
	char temp[size + 1];
	my_strcpy(string, temp, size);
	temp[size] = '\0';
	int number;
	sscanf(temp, "%x", &number);
	// printf("%x\n", number);
	return number;
}

bool parse_header_record(
	char line[255],
	char program_name[6 + 1],
	int *starting_address,
	int *length_of_pgm
)
{
	if (line[1] != 'H' && line[1] != 'h')
	{
		return false;
	}

	my_strcpy(&line[2], program_name, 6);
	program_name[6] = '\0';

	*starting_address = read_number(&line[8], 6);
	*length_of_pgm = read_number(&line[14], 6);

	return true;
}

bool parse_text_record(
	char line[255],
	int *begin_address,
	int *size_of_object_codes,
	int object_codes[12 * 3] // 3 is sic word length, each element is one byte
)
{
	if (line[1] != 'T' && line[1] != 't')
	{
		return false;
	}

	*begin_address = read_number(&line[2], 6);
	*size_of_object_codes = read_number(&line[8], 2);
	for (int i = 0; i < *size_of_object_codes; ++i)
	{
		object_codes[i] = read_number(&line[10 + i * 2], 2);
	}
	return true;
}

bool parse_end_record(
	char line[255],
	int *address
)
{
	if (line[1] != 'E' && line[1] != 'e')
	{
		return false;
	}

	*address = read_number(&line[2], 6);	
	return true;
}

int main(int argc, char const *argv[])
{
	char filename[255] = "test.sic_object_readable";
	FILE* fin = fopen(filename, "r");

	char line[255];
	char program_name[6 + 1];
	int starting_address;
	int length_of_pgm;
	int begin_address;
	int size_of_object_codes;
	int object_codes[12];
	int address_specified_at_end;

	// Read header record
	{
		fscanf(fin, "%s", line);
		remove_carets(line);
		bool status;
		status = parse_header_record(line, program_name, &starting_address, &length_of_pgm);
		if (!status)
		{
			printf("Does not begin with header record.\n");
			fclose(fin);
		}

		// Print header record info
		printf(
			"%s %x %x\n", 
			program_name,
			starting_address,
			length_of_pgm
		);
	}

	while (!feof(fin)) // repeatedly read records
	{
		fscanf(fin, "%s", line);
		remove_carets(line);
		bool status;
		status = parse_text_record(
			line,
			&begin_address,
			&size_of_object_codes,
			object_codes
		);
		if (!status)
		{
			status = parse_end_record(
				line,
				&address_specified_at_end
			);
			if (!status)
			{
				printf("Invalid record found.\n");
				fclose(fin);
				return 1;
			}

			// Print end record information
			printf(
				"%x\n", 
				address_specified_at_end
			);
		}
		else
		{	// Print text record information
			printf(
				"%x %x \n", 
				begin_address,
				size_of_object_codes
			);
			for (int i = 0; i < size_of_object_codes; ++i)
			{
				printf("%x: %x\n", begin_address + i, object_codes[i]);
			}
			/*
			for (int i = 0; i < size_of_object_codes; ++i)
			{
				printf("%x ", object_codes[i]);
			}*/
			printf("\n");
		}
	}

	fclose(fin);

	return 0;
}

// TODO cumulatively total up size of records and check if that's equal to the size of the entire program
// TODO check whether address specified at end is the same as start address
// TODO raise error if end record is absent