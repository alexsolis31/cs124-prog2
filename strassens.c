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
	FILE *fp = fopen(fileName, "r");

	if( fp == NULL ){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

    printf("The contents of %s file are :\n", fileName);

    while( ( ch = fgetc(fp) ) != EOF ){
      ch1 = atoi(&ch);
      printf("%d \n",ch1);
 	}
 	
   	fclose(fp);
   	return 0;
 


}

