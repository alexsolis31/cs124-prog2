#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "strassens.h"

int readFile(char* fileName);

int main(int argc, char **argv){

	// parse inputs 
	if(argc != 4){
		printf("Command line input should be in the form  ./strassen 0 dimension inputfile" );
		return -1; 
	}


	int flag = strtoul(argv[1],NULL, 10);
	int dimension = strtoul(argv[2], NULL, 10);
	char* fileName = argv[3];
	readFile(fileName, dimension);


   	return 0;
 
}


int readFile(char* fileName, dimension){

	// reading in data from the inputFile 
	char ch;
	int ch1;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	FILE *fp = fopen(fileName, "r");
	d = dimension; 

	if( fp == NULL ){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

    printf("The contents of %s file are :\n", fileName);


    int** matrixA = malloc(sizeof(int*) * d);
    int** matrixB = malloc(sizeof(int*) * d);

    for(int i = 0; i < d; i++){
    	if(read = getline(&line, &len, fp)) != -1){
			
		}
    }


    while((read = getline(&line, &len, fp)) != -1){   	
    	ch1 = atoi(line);
    	for(int i = 0; i < d; i++){
    		matrixA[i]
    	}

    	printf("%d \n", ch1);
    }

    


   	fclose(fp);


}




