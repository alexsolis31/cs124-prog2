#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "strassens.h"

int readFile(char* fileName, int dimension);

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


int readFile(char* fileName, int dimension){

  // reading in data from the inputFile 
  char ch;
  int ch1;
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  FILE *fp = fopen(fileName, "r");
  int d = dimension; 

  if( fp == NULL ){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

    printf("The contents of %s file are :\n", fileName);

    int holdingArray[2*d*d];
    int counter = 0;

    while((read = getline(&line, &len, fp)) != -1){
      ch1 = atoi(line);
      holdingArray[counter] = ch1; 
      printf("%d \n", ch1);
      counter++;
    }

    // print the holdingArray
    for (int i = 0; i < (2*d*d); i++){
      printf("%d", holdingArray[i]);
    }

    printf("\n");

    int** matrixA = malloc(sizeof(int*)*d*d);

    int countvar = 0;
    for (int i = 0; i < d; i++){
      for (int j = 0; j < d; j++){
        printf("A: %d\n", matrixA[i][j]);
        // printf("countvar: %d\n", countvar);
        // printf("B: %d\n", holdingArray[countvar]);
        // matrixA[i][j] = holdingArray[countvar];
        countvar++;
       }
    }

    int** matrixB = malloc(sizeof(int*) * d);
   
    fclose(fp);
    return 0; 


}




