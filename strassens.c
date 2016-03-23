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

    int holdingArray[2*d*d];
    int counter = 0;

    while((read = getline(&line, &len, fp)) != -1){
      ch1 = atoi(line);
      holdingArray[counter] = ch1; 
      counter++;
    }

    int** matrixA = (int**) malloc(sizeof(int*)*d);
	for (int i=0; i<d; i++){
		matrixA[i] = (int*) malloc(sizeof(int)*d);
	}

    int countvar = 0;
    for (int i = 0; i < d; i++){
      for (int j = 0; j < d; j++){
        matrixA[i][j] = holdingArray[countvar];
        countvar++;
       }
    }


    int** matrixB = (int**)malloc(sizeof(int*) * d);
   	for (int i=0; i<d; i++){
		matrixB[i] = (int*) malloc(sizeof(int)*d);
	}

    for (int i = 0; i < d; i++){
      for (int j = 0; j < d; j++){
        matrixB[i][j] = holdingArray[countvar];
        countvar++;
       }
    }
    fclose(fp);
    printMatrix(matrixA, dimension);
    allocateQuadrant(matrixA, dimension, 0);
    return 0; 
}

void printMatrix(int** matrix, int dimension){
	for (int i=0; i<dimension; i++){
 		for (int j=0; j<dimension; j++){
 			printf("%d ", matrix[i][j]);
 		}
 		printf("\n");
 	}
  }

int** allocateQuadrant(int** matrix, int d, int quadrant){
	int h = d/2;

	// allocate memory for new quadrant matrix
	int** newQuadrant = (int**)malloc(sizeof(int*) * h);
	for (int i=0; i<h; i++){
		newQuadrant[i] = (int*) malloc(sizeof(int) * h);
	}

	for (int i = 0; i < h; i++){
			for (int j = 0; j < h; j++){
				switch(quadrant){
				case 0: //upper left
					newQuadrant[i][j] = matrix[i][j];
					printf("switch 0\n");
					break;
				case 1: //upper right
					newQuadrant[i][j] = matrix[i][j+h];
					printf("switch 1\n");
					break;
				case 2: // bottom left
					newQuadrant[i][j] = matrix[i+h][j];
					printf("switch 2\n");
					break;
				case 3: // bottom right
					newQuadrant[i][j] = matrix[i+h][j+h];
					printf("switch 3\n");
					break;

			}
		}
	}
	printf("New Quadrant Matrix:\n");
	printMatrix(newQuadrant, h);
	return newQuadrant;
}





 // int strassenAlgorithm(int dimension, int** matrixA, int** matrixB ){
 //    int d = dimension;
    
 //    // Base Case: when matrix is 1x1 (scalar multiplication)
 //    if (d == 1){
 //      matrixC[0][0] = matrixA[0][0] * matrixB[0][0];
 //      return 0; 
 //    }

 //    else{
 //      newDim = d/2; 
 //      int **a00, **a01, **a10, **a11; 
 //      int **b00, **b01, **b10, **b11; 
 //      int **c00, **c01, **c10, **c11; 
 //      int **x1, **x2, **x3, **x4, **x5;
 //      int **x6, **x7, **x8; 

 //      // divide matrices into four parts
 //      a00 = allocateUpperLeft(matrixA, d);
 //      a01 = allocateUpperRight(matrixA, d);
 //      a10 = allocateLowerLeft(matrixA, d);
 //      a11 = allocateLowerRight(matrixA, d);

 //      // free Matrix A

 //      b00 = allocateUpperLeft(matrixB, d);
 //      b01 = allocateUpperRight(matrixB, d);
 //      b10 = allocateLowerLeft(matrixB, d);
 //      b11 = allocateLowerRight(matrixB, d);

 //      // free Matrix B

 //      c00 = allocateMatrix(newDim);
 //      c01 = allocateMatrix(newDim);
 //      c10 = allocateMatrix(newDim);
 //      c11 = allocateMatrix(newDim);


 //      x1 = allocateMatrix(newDim);
 //      x2 = allocateMatrix(newDim);
 //      x3 = allocateMatrix(newDim);
 //      x4 = allocateMatrix(newDim);
 //      x5 = allocateMatrix(newDim);
 //      x6 = allocateMatrix(newDim);
 //      x7 = allocateMatrix(newDim);
 //      x8 = allocateMatrix(newDim);

 //      // compute A11, B11, ... A22, B22 
 //      x1 = strassenAlgorithm(newDim, a11, b11, c11);
 //      x2 = strassenAlgorithm(newDim, ) 



 //    }
 // }






