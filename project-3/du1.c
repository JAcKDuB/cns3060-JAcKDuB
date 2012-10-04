#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SUCCESS 0
#define FAILURE 1
#define SUPERFAIL -1
#define CURRENT_DIRECTORY "." 
#define UP ".."
#define ERROR_MESSAGE_LENGTH 256

int printDirectory(const char* directory);
void printError(const char* directory);
char* errorMessage = NULL;

int main(int argc, char* argv[])
{
	const char* currentDirectory = argc > 1 ? argv[1] : CURRENT_DIRECTORY;
	
	struct stat input;
	if(stat(currentDirectory, &input) != SUCCESS)
	{
		perror("File error");
		return FAILURE;
	}

	if(S_ISDIR(input.st_mode))
	{
		int dirSize = printDirectory(currentDirectory);

		if	(dirSize == SUPERFAIL) 
		{
			errorMessage = "printDirectory failed.";
			printError(currentDirectory);
			return FAILURE;
		}
		//printf("%7lld B %s\n", (long long)dirSize, currentDirectory);
	}
	else
	{
		printf("Size of '%s' : %lld B\n", currentDirectory, (long long)input.st_size);
	}



  return SUCCESS;
}

// ********************************************************************

int printDirectory(const char* directory)
{
	
	int directorySize = 4096;

	DIR* dirP = opendir(directory);
	if (dirP == NULL)
	{
		errorMessage = "Directory could not be opened";
		printError(directory);
		return SUPERFAIL;
	}
	
	struct dirent* currentEntry;
	while ((currentEntry = readdir(dirP)) != NULL)
	{

		struct stat entryStats;
		char statDirectory[512];
		snprintf(statDirectory, sizeof(statDirectory)-1, "%s/%s", directory, currentEntry->d_name);
		if (stat(statDirectory, &entryStats) != SUCCESS)
		{
			errorMessage = "Could not get file stats";
			printError(currentEntry->d_name);
			return SUPERFAIL;
		}

		if(S_ISDIR(entryStats.st_mode))
		{
			if (strcmp(currentEntry->d_name, CURRENT_DIRECTORY) && strcmp(currentEntry->d_name, UP))
			{
				char nextDirName[512];
				snprintf(nextDirName, sizeof(nextDirName)-1, "%s/%s", directory, currentEntry->d_name);
				directorySize += printDirectory(nextDirName);
			}
		}
		else
		{
			directorySize += entryStats.st_size;
			printf("%7lld B %s/%s\n", (long long)entryStats.st_size, directory, currentEntry->d_name);
		}
	}

	if (closedir(dirP) != SUCCESS)
	{
		errorMessage = "Could not close the directory";
		printError(currentEntry->d_name);
		return SUPERFAIL;
	}

	printf("%7lld B %s\n", (long long)directorySize, directory);
	return directorySize;
}

// ********************************************************************

void printError(const char* directory)
{
  char buffer[ERROR_MESSAGE_LENGTH];
  snprintf(buffer, sizeof(buffer)-1, "Directory '%s' has encountered error: %s", directory, errorMessage);
  perror(buffer);
}
