#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <termios.h>

#define PAGELEN 23
#define LINELEN 512
#define SUCCESS 0
#define FAILURE 1
#define ONE 1

int doMore(FILE *);
int seeMore(FILE *);
int countLines(FILE *);
void sigHandler(int);

struct termios tios, origTios;
int first = 1;
double percentage = 0;
char* name;

int main (int argc, char* argv[])
{
	FILE *fp;
	int numbLines = 0;

	signal(SIGINT, sigHandler);

	fputs("\033[2J\033[1;1H", stdout);

	// Get current terminal settings
	if (tcgetattr(0, &origTios))
	{
		printf("Error getting terminal settings\n");
		return FAILURE;
	}

	if (argc == 1)
	{
		doMore(stdin);
	}
	else
	{
		while (--argc)
		{
			if((fp = fopen(argv[1], "r")) != NULL)
			{
				name = argv[1];
				doMore(fp);
				fclose(fp);
			}
			else
			{
				return 1;
			}
		}
	}

	return SUCCESS;
}

// *****************************************************

int doMore(FILE *fp)
{

	char line[LINELEN];
	int currentLine = 0;
	int linesToPrint = PAGELEN;
	int numberOfLines = 0;
	int seeMore(FILE *), reply;
	int skip = 0;
	FILE *ttyPointer;

	ttyPointer = fopen("/dev/tty", "r");

	numberOfLines = countLines(fp);
	rewind(fp);

	if (ttyPointer == NULL)
	{
		return FAILURE;
	}	

	// copy to var to be modified
	tios = origTios;

	// disable Canonical mode
	tios.c_lflag &= ~ICANON;

	// disable ECHO
	tios.c_lflag &= ~ECHO;

	// apply the new settings
	if (tcsetattr(0, TCSANOW, &tios))
	{
		printf("Could not apply new terminal settings");
		return FAILURE;
	}

	// check to see if settings were applied
	if (tcgetattr(0, &tios))
	{
		tcsetattr(0, TCSANOW, &origTios);
		printf("Error asserting terminal settings");
		return FAILURE;
	}

	if ((tios.c_lflag & ICANON) || (tios.c_lflag & ECHO))
	{
		tcsetattr(0, TCSANOW, &origTios);
		printf("could not apply all new settings");
		return FAILURE;
	}


	while (fgets(line, LINELEN, fp))
	{

		//if we've read the number lines we're supposed to 
		if (currentLine == linesToPrint)
		{
			//get percentage
			percentage = (((double)linesToPrint / (double)numberOfLines) * 100);

			//ask for a response
			reply = seeMore(ttyPointer);
			if (reply == 0)
			{
				break;
			}
			//subtract the returned value (defined constants) from currentLine
			linesToPrint += reply;
			currentLine = 0;
			rewind(fp);
			skip = 1;
		}

		if (!skip)
		{
			//if the output is an EOF
			if(fputs(line, stdout) == EOF)
			{
				//Restore terminal settings
				tcsetattr(0, TCSANOW, &origTios);
				//exit
				return SUCCESS;
			}
		}

		++currentLine;
		skip = 0;
	}

	//Restore terminal settings
	tcsetattr(0, TCSANOW, &origTios);

}

// *****************************************************

int seeMore(FILE *fp)
{

	int c;

	if(first)
	{
		printf("\033[7m %s (%%%.0f) \033[m", name, percentage);
		first = 0;
	}
	else
	{
		printf("\033[7m --More--(%%%.0f) \033[m", percentage);
	}

	while ((c=getchar()) != EOF)
	{

		if (c == 'q')
		{
			printf("\n"); // for cosmetics
			return SUCCESS;
		}
		else if (c == ' ')
		{
			fputs("\033[2J\033[1;1H", stdout);
			return PAGELEN;
		}
		else if (c == '\n')
		{
			fputs("\033[2J\033[1;1H", stdout);
			return ONE; //To use failure here would be a little misleading
		}
		else {}
	}
	return SUCCESS;
}


// *****************************************************

int countLines(FILE *fp)
{
	char line[LINELEN];
	int numOfLines = 0;
	int status = 0;

	while ((status=fgetc(fp)) != EOF)
	{
		if (status == '\n')
		++numOfLines;
	}



	return numOfLines;
}

// *****************************************************

void sigHandler(int sig)
{
	signal(sig, SIG_IGN);
	printf("\nCtrl-C detected.\nRestoring terminal and exiting . . .\n");

	//Restore terminal settings
	tcsetattr(0, TCSANOW, &origTios);

	exit(0);	
}

// *****************************************************
