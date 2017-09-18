#include"program.h"

void printNestedDirectory(char *dirName)
{
	DIR *dir;
	struct dirent *dEntry;
	
	// open directory
	if((dir = opendir(dirName)) == NULL)
	{
		perror("opendir");
		fprintf(stderr,"Cannot open directory %s\n",dirName);
	}
	else
	{		
		struct stat fileStat;
		int res;
		
		char *path;		
		path = (char *) malloc(sizeof(dirName) + sizeof(dEntry->d_name) + 1);
		
		while((dEntry = readdir(dir)) != NULL)
		{
			// Creates path by appending the current directory entry to cwd. It is provided as parameter to stat()
			if(strcmp(dirName,"/") == 0)
				sprintf(path,"%s%s",dirName,dEntry->d_name);
			else
				sprintf(path,"%s/%s",dirName,dEntry->d_name);

			if((res = stat(path,&fileStat)) == 0)
			{
				// check if the directory entry is a directory
				if(S_ISDIR(fileStat.st_mode))
				{
					// avoiding recursive calls to the current directory(.) and parent directory(..)
					if((strcmp(dEntry->d_name,".") != 0) && (strcmp(dEntry->d_name,"..") != 0))
					{
						printf("\nDirectory: %s\n",path);
						printNestedDirectory(path);
						printf("\n");
					}
				}
				else
					printf("File: %s\n",path);
			}
		}
	}	
}

int main(int argc, char *argv[])
{
	printNestedDirectory(argv[1]);
	return 0;
}
