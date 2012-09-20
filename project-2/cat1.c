#include <stdio.h>

#define LINELEN 512

// *****************************************************

int print(FILE* fp, int printNumbers)
{
	char line[LINELEN];
	int lineNumber = 1;

	while (fgets (line, LINELEN, fp))
	{
		if (printNumbers)
		{
			printf("%i\t", lineNumber);
			++lineNumber;
		}

		if (fputs(line, stdout) == EOF)
		{
			perror("Printing the file failed\n");
			return -1;
		}

	}

	return 0;	
}

// *****************************************************

int checkForNumber(char* argv[])
{
		if(argv[0][0] - '-' == 0) 
		{
			if(argv[0][1] - 'n' == 0)
			{
				return 1;
			}
			else
			{
				printf("%s is not supported, please use '-n'\n", argv[0]);
				return 0;
			}
		}
		else
		{
			return 0;
		}//end if/else -
}

// *****************************************************

int main(int argc, char *argv[])
{
	FILE* fp;
	int _numberMode = 0;
	
	if(argc == 1)
	{
		print(stdin, 0);
		fclose(fp);
	}
	else if (argc == 2)
	{
		fp = fopen(argv[1], "r");
		
		if (fp == NULL)
		{
			perror("File not found, check file name. \n");
			return -1;
		}
		else
		{		
			print(fp, 0);
			fclose(fp);
		}
	}
	else if (argc >= 3)
	{
		_numberMode = checkForNumber(&argv[1]);

		if (_numberMode)
		{
			int i = 2;

			for (i; i <= argc - 1; ++i)
			{
				fp = fopen(argv[i], "r");
			
				if (fp == NULL)
				{
					perror("File not found, check file name. \n");
				}
				else
				{		
					print(fp, 1);
					fclose(fp);
				}			

				printf("\n"); // for cosmetics
			}
		}
		else
		{
			int i = 1;

			for (i; i <= argc - 1; ++i)
			{
				fp = fopen(argv[i], "r");
			
				if (fp == NULL)
				{
					perror("File not found, check file name. \n");
				}
				else
				{		
					print(fp, 0);
					fclose(fp);
				}			

				printf("\n"); // for cosmetics
			}
		}// end if/else _numberMode
	}// end if argc == 3
	else
	{
		perror("invalid command. To use: ./cat1 [-n] <filename> \n");
		return -1;
	}
	
	return 0;
}

// *****************************************************
