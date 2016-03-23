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


 int strassenAlgorithm(int dimension, int** matrixA, int** matrixB ){
    int d = dimension;
    
    // Base Case: when matrix is 1x1 (scalar multiplication)
    if (d == 1){
      matrixC[0][0] = matrixA[0][0] * matrixB[0][0];
      return 0; 
    }

    else{
      newDim = d/2; 
      int **a00, **a01, **a10, **a11; 
      int **b00, **b01, **b10, **b11; 
      int **c00, **c01, **c10, **c11; 
      int **x1, **x2, **x3, **x4, **x5;
      int **x6, **x7, **x8; 

      // divide matrices into four parts
      a00 = allocateUpperLeft(matrixA, d);
      a01 = allocateUpperRight(matrixA, d);
      a10 = allocateLowerLeft(matrixA, d);
      a11 = allocateLowerRight(matrixA, d);

      // free Matrix A

      b00 = allocateUpperLeft(matrixB, d);
      b01 = allocateUpperRight(matrixB, d);
      b10 = allocateLowerLeft(matrixB, d);
      b11 = allocateLowerRight(matrixB, d);

      // free Matrix B

      c00 = allocateMatrix(newDim);
      c01 = allocateMatrix(newDim);
      c10 = allocateMatrix(newDim);
      c11 = allocateMatrix(newDim);


      x1 = allocateMatrix(newDim);
      x2 = allocateMatrix(newDim);
      x3 = allocateMatrix(newDim);
      x4 = allocateMatrix(newDim);
      x5 = allocateMatrix(newDim);
      x6 = allocateMatrix(newDim);
      x7 = allocateMatrix(newDim);
      x8 = allocateMatrix(newDim);

      // compute A11, B11, ... A22, B22 
      x1 = strassenAlgorithm(newDim, a11, b11, c11);
      x2 = strassenAlgorithm(newDim, ) 



    }
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
      printf("A: %d \n", ch1);
      counter++;
    }

    // print the holdingArray
    for (int i = 0; i < (2*d*d); i++){
      printf("B: %d\n", holdingArray[i]);
    }

    printf("HI: %d\n", d);

    int** matrixA = (int**) malloc(sizeof(int*)*d);
	for (int i=0; i<d; i++){
		matrixA[i] = (int*) malloc(sizeof(int)*d);
	}

    int countvar = 0;
    for (int i = 0; i < d; i++){
      for (int j = 0; j < d; j++){
      	printf("I: %d\n", i);
      	printf("J: %d\n", j);
        printf("matrix before A: %d\n", matrixA[i][j]);
        printf("countvar A: %d\n", countvar);
        // printf("B: %d\n", holdingArray[countvar]);
        matrixA[i][j] = holdingArray[countvar];
        printf("matrix after A: %d\n", matrixA[i][j]);
        countvar++;
       }
    }

    printf("final matrix A: %d\n", matrixA[d-1][d-1]);

    int** matrixB = (int**)malloc(sizeof(int*) * d);
   	for (int i=0; i<d; i++){
		matrixB[i] = (int*) malloc(sizeof(int)*d);
	}

    for (int i = 0; i < d; i++){
      for (int j = 0; j < d; j++){
      	printf("I: %d\n", i);
      	printf("J: %d\n", j);
        printf("matrix before B: %d\n", matrixA[i][j]);
        printf("countvar B: %d\n", countvar);
        // printf("B: %d\n", holdingArray[countvar]);
        matrixB[i][j] = holdingArray[countvar];
        printf("matrix after B: %d\n", matrixA[i][j]);
        countvar++;
       }
    }
    printf("final matrix B: %d\n", matrixB[d-1][d-1]);
    fclose(fp);
    return 0; 


}




