#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "strassens.h"


int main(int argc, char **argv){
  // parse inputs 
  if(argc != 4){
    printf("Command line input should be in the form:  ./strassens 0 dimension inputfile\n" );
    return 1; 
  }
  printf("test1\n");

  int flag = strtoul(argv[1],NULL, 10);
  int dimension = strtoul(argv[2], NULL, 10);
  int d = dimension; 

  // printf("ARGV4: %s\n", argv[3]);

  // allocate matrix A
  int** matrixA = (int**) malloc(sizeof(int*)*d);
  for (int i=0; i<d; i++){
    matrixA[i] = (int*) malloc(sizeof(int)*d);
  }

  // allocate matrix B
  int** matrixB = (int**)malloc(sizeof(int*) * d);
  for (int i=0; i<d; i++){
    matrixB[i] = (int*) malloc(sizeof(int)*d);
  }


  char* fileName = argv[3];
  readFile(fileName, dimension, matrixA, matrixB);

  strassenAlgorithm(dimension, matrixA, matrixB);

  return 0;
}

int readFile(char* fileName, int dimension, int** matrixA, int** matrixB){
  // reading in data from the inputFile 
  char ch;
  int ch1;
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  FILE *fp = fopen(fileName, "r");
  int d = dimension; 

  if(fp == NULL ){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

    int holdingArray[(2*d*d) + 1];
    int counter = 0;

    while((read = getline(&line, &len, fp)) != -1){
      ch1 = atoi(line);
      holdingArray[counter] = ch1; 
      counter++;
    }
    printf("HERE %d\n", holdingArray[3]);

	// fill matrix A
    int countvar = 0;
    for (int i = 0; i < d; i++){
      for (int j = 0; j < d; j++){
        matrixA[i][j] = holdingArray[countvar];
        countvar++;
       }
    }

	// fill matrix B
    for (int i = 0; i < d; i++){
      for (int j = 0; j < d; j++){
        matrixB[i][j] = holdingArray[countvar];
        countvar++;
       }
    }
    fclose(fp);
    printf("Matrix A: \n");
    printMatrix(matrixA, dimension);
    printf("Matrix B: \n");
    printMatrix(matrixB, dimension);
    // int** aTest = allocateQuadrant(matrixA, dimension, 0);
    // int** bTest = allocateQuadrant(matrixA, dimension, 1);
    // int** cTest = allocateQuadrant(matrixA, dimension, 2);
    // int** dTest = allocateQuadrant(matrixA, dimension, 3);
    // reglue(aTest,bTest,cTest,dTest,dimension);
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
	printf("IN HERE\n");
	int h = d/2;

	// allocate memory for new quadrant matrix
	int** newQuadrant = (int**)malloc(sizeof(int*) * h);
	for (int i=0; i<h; i++){
		printf("AAAAA %d\n", i);
		newQuadrant[i] = (int*) malloc(sizeof(int) * h);
		printf("AAAAB %d\n", newQuadrant[i][0]);
	}

	// printf("2HERE:%d\n", matrix[3][3]);

	for (int i = 0; i < h; i++){
			for (int j = 0; j < h; j++){
				switch(quadrant){
				case 0: //upper left
					newQuadrant[i][j] = matrix[i][j];
					break;
				case 1: //upper right
					newQuadrant[i][j] = matrix[i][j+h];
					break;
				case 2: // bottom left
					newQuadrant[i][j] = matrix[i+h][j];
					break;
				case 3: // bottom right
					newQuadrant[i][j] = matrix[i+h][j+h];
					break;

			}
		}
	}
	printf("New Quadrant Matrix:\n");
	printMatrix(newQuadrant, h);
	return newQuadrant;
}


int** strassenAlgorithm(int dimension, int** matrixA, int** matrixB){
    int d = dimension;

    int** matrixC = allocateMatrix(d);
    
    // Base Case: when matrix is 1x1 (scalar multiplication)
    if (d == 1){
      matrixC[0][0] = matrixA[0][0] * matrixB[0][0];
      return matrixC; 
    }



    else{
      int newDim = d/2; 

      int **a00, **a01, **a10, **a11; 
      int **b00, **b01, **b10, **b11; 
      int **c00, **c01, **c10, **c11; 
      int **x0, **x1, **x2, **x3, **x4;
      int **x5, **x6, **x7; 

      // divide matrices into four parts
      printf("3HERE %d\n", matrixA[1][1]);
      a00 = allocateQuadrant(matrixA, d, 0);
      printf("4HERE %d\n", matrixA[0][0]);
      a01 = allocateQuadrant(matrixA, d, 1);
      a10 = allocateQuadrant(matrixA, d, 2);
      a11 = allocateQuadrant(matrixA, d, 3);

      // free Matrix A

      b00 = allocateQuadrant(matrixB, d, 0);
      b01 = allocateQuadrant(matrixB, d, 1);
      b10 = allocateQuadrant(matrixB, d, 2);
      b11 = allocateQuadrant(matrixB, d, 3);

      // free Matrix B

      c00 = allocateMatrix(newDim);
      printf("CCCCCCCC\n");
      c01 = allocateMatrix(newDim);
      c10 = allocateMatrix(newDim);
      c11 = allocateMatrix(newDim);


      x0 = allocateMatrix(newDim);
      x1 = allocateMatrix(newDim);
      x2 = allocateMatrix(newDim);
      x3 = allocateMatrix(newDim);
      x4 = allocateMatrix(newDim);
      x5 = allocateMatrix(newDim);
      x6 = allocateMatrix(newDim);
      x7 = allocateMatrix(newDim);

      // compute A11, B11, ... A22, B22 
      printf("0111111\n");
      x0 = strassenAlgorithm(newDim, a11, b11);
      printf("1111111\n");
      x1 = strassenAlgorithm(newDim, a01, b10);
      x2 = strassenAlgorithm(newDim, a00, b01);
      x3 = strassenAlgorithm(newDim, a01, b11);
      x4 = strassenAlgorithm(newDim, a10, b00);
      x5 = strassenAlgorithm(newDim, a11, b10);
      x6 = strassenAlgorithm(newDim, a10, b01);
      x7 = strassenAlgorithm(newDim, a11, b11);

      c00 = sumMatrices(x0, x1, newDim);
      c01 = sumMatrices(x2, x3, newDim);
      c10 = sumMatrices(x4, x5, newDim);
      c11 = sumMatrices(x6, x7, newDim);

      matrixA = reglue(c00, c01, c10, c11, newDim);
      printMatrix(matrixA, dimension);
      return matrixA; 
    }
 }
/********************************************************/
 // sum two vertices 
 int** sumMatrices(int** a, int** b, int dimension){
    int** matrixSum = allocateMatrix(dimension);

    for(int i = 0; i < dimension; i++){
      for(int j = 0; j < dimension; j++){
        matrixSum[i][j] = a[i][j] + b[i][j];    
      }
    }  
    return matrixSum; 
 }

/********************************************************/
// allocate matrix 

 int** allocateMatrix(int d){
    int** matrix; 

    matrix = (int**) malloc(d * sizeof(double*));

    if (matrix == NULL){
      printf("Error in Matrix Allocation \n");
    }

    for (int i = 0; i < d; i++){
      matrix[i] = (int*) malloc(d * sizeof(double));

      if (matrix[i] == NULL){
        printf("Error in Matrix row allocation \n");
      }

    }

    return matrix; 
 }

/********************************************************/

int** reglue(int** a, int** b, int** c, int** d, int dimension){
  int h = dimension/2;
  int** gluedMatrix = (int**)malloc(sizeof(int*)*dimension);
  for (int i=0; i<dimension; i++){
    gluedMatrix[i] = (int*) malloc(sizeof(int)*dimension);
  }

  for (int i=0; i<h; i++){
    for (int j=0; j<h; j++){
      gluedMatrix[i][j] = a[i][j];
      gluedMatrix[i][j+h] = b[i][j];
      gluedMatrix[i+h][j] = c[i][j];
      gluedMatrix[i+h][j+h] = d[i][j];
    }
  }
  printf("reglued: \n");
  printMatrix(gluedMatrix, dimension);
  return gluedMatrix; 
 }




