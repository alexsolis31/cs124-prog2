#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "strassens.h"

int countess = 0; 

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

    sumMatrices(matrixA, matrixB, dimension);
    subMatrices(matrixB, matrixA, dimension);
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
	int h = d/2;

	// allocate memory for new quadrant matrix
	int** newQuadrant = (int**)malloc(sizeof(int*) * h);
	for (int i=0; i<h; i++){
		newQuadrant[i] = (int*) malloc(sizeof(int) * h);
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
	// printf("New Quadrant Matrix:\n");
	// printMatrix(newQuadrant, h);
	return newQuadrant;
}
 


int** strassenAlgorithm(int dimension, int** matrixA, int** matrixB){
    int d = dimension;

    int** matrixC = allocateMatrix(d);
    
    // Base Case: when matrix is 1x1 (scalar multiplication)
    if (d == 1){
      countess++; 
      matrixC[0][0] = matrixA[0][0] * matrixB[0][0];
      printf("Matrix C MRKD:\n");
      printMatrix(matrixC, d);
      printf("\n");
      printf("Count: %d", countess );
      return matrixC; 

    }

    else{
      countess++; 
      printf("Counter: %d \n", countess );
      int newDim = d/2; 

      int **a00, **a01, **a10, **a11; 
      int **b00, **b01, **b10, **b11; 
      int **c00, **c01, **c10, **c11; 
      int **P1, **P2, **P3, **P4;
      int **P5, **P6, **P7; 

      // divide matrices into four parts

      printf("START %d\n", matrixA[1][1]);

      printf("Matrix A:\n");
      printMatrix(matrixA, newDim);
      printf("\n");

      a00 = allocateQuadrant(matrixA, d, 0);
      a01 = allocateQuadrant(matrixA, d, 1);
      a10 = allocateQuadrant(matrixA, d, 2);
      a11 = allocateQuadrant(matrixA, d, 3);

      printf("a00:\n");
      printMatrix(a00, d/2);
      printf("\n");
      printf("a01:\n");
      printMatrix(a01, d/2);
      printf("\n");
      printf("a10:\n");
      printMatrix(a10, d/2);
      printf("\n");
      printf("a11:\n");
      printMatrix(a11, d/2);
      printf("\n");


      // free Matrix A

      b00 = allocateQuadrant(matrixB, d, 0);
      b01 = allocateQuadrant(matrixB, d, 1);
      b10 = allocateQuadrant(matrixB, d, 2);
      b11 = allocateQuadrant(matrixB, d, 3);

      printf("b00:\n");
      printMatrix(b00, d/2);
      printf("\n");
      printf("b01:\n");
      printMatrix(b01, d/2);
      printf("\n");
      printf("b10:\n");
      printMatrix(b10, d/2);
      printf("\n");
      printf("b11:\n");
      printMatrix(b11, d/2);
      printf("\n");

      // free Matrix B

      c00 = allocateMatrix(newDim);
      c01 = allocateMatrix(newDim);
      c10 = allocateMatrix(newDim);
      c11 = allocateMatrix(newDim);


      P1 = allocateMatrix(newDim);
      P2 = allocateMatrix(newDim);
      P3 = allocateMatrix(newDim);
      P4 = allocateMatrix(newDim);
      P5 = allocateMatrix(newDim);
      P6 = allocateMatrix(newDim);
      P7 = allocateMatrix(newDim);

      int **x, **y, **z; 

      x = allocateMatrix(newDim);
      y = allocateMatrix(newDim);

      x = sumMatrices(a00, a11, newDim);
      printf("Matrix Sum a00 + a11: \n" );
      printMatrix(x, newDim);
      printf("\n");

      y = sumMatrices(b00, b11, newDim);
      printf("Matrix Sum b00 + b11: \n" );
      printMatrix(y, newDim);
      printf("\n");

      // compute A11, B11, ... A22, B22 
      P1 = strassenAlgorithm(newDim, sumMatrices(a00, a11, newDim), sumMatrices(b00, b11, newDim));
      P2 = strassenAlgorithm(newDim, sumMatrices(a10, a11, newDim), b00);
      P3 = strassenAlgorithm(newDim, a00, subMatrices(b01, b11, newDim));
      P4 = strassenAlgorithm(newDim, a11, subMatrices(b10, b00, newDim));
      P5 = strassenAlgorithm(newDim, sumMatrices(a00, a01, newDim), b11);
      P6 = strassenAlgorithm(newDim, subMatrices(a10, a00, newDim), sumMatrices(b00, b01, newDim));
      P7 = strassenAlgorithm(newDim, subMatrices(a01, a11, newDim), sumMatrices(b10, b11, newDim));

      printf("P1:\n");
      printMatrix(P1, newDim);
      printf("\n");
      printf("P2:\n");
      printMatrix(P2, newDim);
      printf("\n");
      printf("P3:\n");
      printMatrix(P3, newDim);
      printf("\n");
      printf("P4:\n");
      printMatrix(P4, newDim);
      printf("\n");
      printf("P5:\n");
      printMatrix(P5, newDim);
      printf("\n");
      printf("P6:\n");
      printMatrix(P6, newDim);
      printf("\n");
      printf("P7:\n");
      printMatrix(P7, newDim);

      // printMatrix(x0, newDim);
      c00 = sumMatrices(subMatrices(sumMatrices(P1, P4, newDim), P5, newDim), P7, newDim);
      printf("THIS IS C00: \n" );
      printMatrix(c00, newDim);

      c01 = sumMatrices(P3, P5, newDim);
      c10 = sumMatrices(P2, P4, newDim);
      c11 = sumMatrices(subMatrices(sumMatrices(P1, P3, newDim), P2, newDim), P6, newDim);

      printf("THIS IS C01: \n" );
      printMatrix(c01, newDim);

      printf("THIS IS C10: \n" );
      printMatrix(c10, newDim);

      printf("THIS IS C22: \n" );
      printMatrix(c11, newDim);

      // for(int i = 0; i < newDim; i++){
      // 	for(int j = 0; j < newDim; j++){
      // 		printf("%d ", c00[i][j]);
      // 	}
      // 	printf("\n");
      // }


      matrixC = reglue(c00, c01, c10, c11, dimension);
      printMatrix(matrixC, dimension);
      return matrixC; 
    }
 }
/********************************************************/
 // sum two matrices 
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
 // subtract two matrices 
 int** subMatrices(int** a, int** b, int dimension){
    int** matrixSum = allocateMatrix(dimension);

    for(int i = 0; i < dimension; i++){
      for(int j = 0; j < dimension; j++){
        matrixSum[i][j] = a[i][j] - b[i][j];    
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
  printf("dimension: %d\n", dimension);
  int h;
  if (dimension <= 1){
  	h = dimension;
  }
  else{
  	h = dimension/2;
  }

  int** gluedMatrix = (int**)malloc(sizeof(int*)*dimension);
  for (int i=0; i<dimension; i++){
    gluedMatrix[i] = (int*) malloc(sizeof(int)*dimension);
  }

  printf("TESTING SHIT: %d\n", h);
  printf("RG A %d\n", a[0][0]);
  printf("RG B %d\n", b[0][0]);
  printf("RG C %d\n", c[0][0]);
  printf("RG D %d\n", d[0][0]);
  // printf("_A: %d", )
  // for (int i=0; i<h; i++){
  //   for (int j=0; j<h; j++){
  //   	printf("AAAAAAA IM HERE %d", a[i][j]);
  //   }
  //  }


  for (int i=0; i<h; i++){
    for (int j=0; j<h; j++){
      // printf("Tester A: %d\n", a[i][j]);
      // printf("Tester B: %d\n", b[i][j]);
      // printf("Tester C: %d\n", c[i][j]);
      // printf("Tester D: %d\n", d[i][j]);
      // printf("Tester GA: %d\n", gluedMatrix[i][j]);
      // printf("Tester GB: %d\n", gluedMatrix[i][j+h]);
      // printf("ih: %d\n", i+h);
      // printf("HERE %d\n", gluedMatrix[1][1]);
      // printf("Tester GC: %d\n", gluedMatrix[i+h][j]);
      // printf("Tester GD: %d\n", gluedMatrix[i+h][j+h]);
      gluedMatrix[i][j] = a[i][j];
      gluedMatrix[i][j+h] = b[i][j];
      gluedMatrix[i+h][j] = c[i][j];
      gluedMatrix[i+h][j+h] = d[i][j];
    }
  }
  printf("reglued: \n");
  printMatrix(gluedMatrix, dimension);
  printf("Printed.\n");
  return gluedMatrix; 
 }




