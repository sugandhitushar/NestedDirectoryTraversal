#include"program.h"

char cwd[500]="\0";

void printNestedDirectory(char *dirName)
{
	// Maintains the cwd (abbreviation for current working directory) and appends the dirName into it upon recursive call.
	if(strcmp(cwd,"\0") == 0)
		sprintf(cwd,"%s",dirName);
	else 
		sprintf(cwd,"%s/%s",cwd,dirName);
		
	DIR *dir;
	struct dirent *dEntry;
	
	// open cwd
	if((dir = opendir(cwd)) == NULL)
	{
		perror("opendir");
		fprintf(stdout,"Cannot open directory %s\n",dirName);
	}
	else
	{		
		struct stat fileStat;
		int res;
		
		char path[100];
		
		while((dEntry = readdir(dir)) != NULL)
		{
			// Creates path by appending the current directory entry to cwd. It is provided as parameter to stat()
			sprintf(path,"%s/%s",cwd,dEntry->d_name);

			if((res = stat(path,&fileStat)) == 0)
			{
				// check if the directory entry is a directory
				if(S_ISDIR(fileStat.st_mode))
				{
					// avoiding recursive calls to the current directory(.) and parent directory(..)
					if((strcmp(dEntry->d_name,".") != 0) && (strcmp(dEntry->d_name,"..") != 0))
					{
						printf("Directory: %s/%s\n",cwd,dEntry->d_name);
						printNestedDirectory(dEntry->d_name);
						sprintf(cwd,"%s",dirName);
						
					}
				}
				else
				{
					printf("File: %s/%s\n",cwd,dEntry->d_name);
				}
			}
		}
	}	
	
}

int main(int argc, char *argv[])
{
	printNestedDirectory(argv[1]);	
}
