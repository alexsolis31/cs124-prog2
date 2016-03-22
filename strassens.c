#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "strassens.h"

int main(int argc, char **argv){

	// parse inputs 
	if(argc != 4){
		printf("Command line input should be in the form  ./strassen 0 dimension inputfile" );
		return -1; 
	}


	int flag = strtoul(argv[1],NULL, 10);
	int dimension = strtoul(argv[2], NULL, 10);
	char* fileName = argv[3];
	char ch;
	int ch1;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	FILE *fp = fopen(fileName, "r");

	if( fp == NULL ){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

    printf("The contents of %s file are :\n", fileName);

    
    while((read = getline(&line, &len, fp)) != -1){
    	ch1 = atoi(line);
    	printf("%d \n", ch1);
    }

   	fclose(fp);
   	return 0;
 


}

