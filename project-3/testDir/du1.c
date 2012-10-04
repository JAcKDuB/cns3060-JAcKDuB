#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SUCCESS 0
#define FAILURE 1
#define CURRENT_DIRECTORY "." 
#define UP ".."
#define ERROR_MESSAGE_LENGTH 256

int printDirectory(const char* directory);
void printError(const char* directory);
char* errorMessage = NULL;

int main(int argc, char* argv[])
{
	const char* currentDirectory = argc > 1 ? argv[1] : CURRENT_DIRECTORY;

  if (printDirectory(currentDirectory) != SUCCESS) 
  {
    printError(currentDirectory);
    return FAILURE;
  }

  return SUCCESS;
}

int printDirectory(const char* directory)
{

	DIR* dirP = opendir(directory);
	if (dirP == NULL)
	{
		errorMessage = "Directory could not be opened";
		return FAILURE;
	}
	
	struct dirent* currentEntry;
	while ((currentEntry = readdir(dirP)) != NULL)
	{
		printf("Directory : '%15s' Entry: '%15s'", directory, currentEntry->d_name);

		struct stat entryStats;
		if (stat(currentEntry->d_name, &entryStats) != SUCCESS)
		{
			errorMessage = "Could not get file stats";
			printError(currentEntry->d_name);
			return FAILURE;
		}

		printf("Size : %lld b\n", (long long)entryStats.st_size);
		
		if(S_ISDIR(entryStats.st_mode)/* && currentEntry->d_name != CURRENT_DIRECTORY || currentEntry->d_name != UP*/)
		{
			if (strcmp(currentEntry->d_name, CURRENT_DIRECTORY) && strcmp(currentEntry->d_name, UP))
			{
				//printf("'%s' is a directory.\n", currentEntry->d_name);
				printDirectory(currentEntry->d_name);
			}
		}
	}

	printf("\n"); //Cosmetics

	if (closedir(dirP) != SUCCESS)
	{
		errorMessage = "Could not close the directory";
		return FAILURE;
	}

	return SUCCESS;
}

void printError(const char* directory)
{
  char buffer[ERROR_MESSAGE_LENGTH];
  snprintf(buffer, sizeof(buffer)-1, "Directory '%s' has encountered error: %s", directory, errorMessage);
  perror(buffer);
}
