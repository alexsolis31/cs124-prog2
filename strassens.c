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

  int flag = strtoul(argv[1],NULL, 10);
  int dimension = strtoul(argv[2], NULL, 10);
  int d;

  if (dimension % 2 == 0){
    d = dimension;
  }
  else{
    d = dimension + 1;
  }

  if (flag == 0){
    flag = 1;
  }

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

  // Timer 

  clock_t start, end; 
  double cpu_time_used; 


  start = clock();
  int** strassenMatrix = strassenAlgorithm(dimension, matrixA, matrixB, flag);
  end = clock(); 

  // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("CPU time used: %f\n", cpu_time_used);

  // printf("Strassen Done Matrix: \n");
  // printMatrix(strassenMatrix, dimension);
  // printf("\n");

  // int** traditionalMatrix = regularMult(dimension, matrixA, matrixB);
  // printf("Traditional Done Matrix: \n");
  // printMatrix(traditionalMatrix, dimension);
  // printf("\n");

  int** strassenCleaned = cleanMatrix(strassenMatrix, dimension);
  // printf("Cleaned Strassen Matrix: \n");
  printMatrix(strassenCleaned, dimension);
  printf("\n");

  // int** traditionalCleaned = cleanMatrix(traditionalMatrix, dimension);
  // printf("Cleaned Traditional  Matrix: \n");
  // printMatrix(traditionalCleaned, dimension);
  // printf("\n");

  // printf("Are they the same tho?\n");
  // if(compareMatrices(strassenCleaned, traditionalCleaned, dimension) == 0)
  //   printf("Yes they are \n");
  

  freeMatrix(matrixA, dimension);
  freeMatrix(matrixB, dimension);
  freeMatrix(strassenMatrix, dimension);

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

    int numberUsed = 2 * d * d - 1; 
    int holdingArray[numberUsed];
    int counter = 0;

    while((read = getline(&line, &len, fp)) != -1 && counter <= numberUsed){
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

void freeMatrix(int** matrix, int d){
  for (int i=0; i<d; i++){
    int* currentPtr = matrix[i];
    free(currentPtr);
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
  return newQuadrant;
}
 
int** strassenAlgorithm(int dimension, int** matrixA, int** matrixB, int n0){
    int d = dimension;

    int** matrixC = allocateMatrix(d);
    
    // Base Case: when matrix is 1x1 (scalar multiplication)
    if (d <= n0){
      matrixC = regularMult(dimension, matrixA, matrixB);
      return matrixC; 

    }

    else{
      countess++; 
      int newDim = d/2; 

      int **a00, **a01, **a10, **a11; 
      int **b00, **b01, **b10, **b11; 
      int **c00, **c01, **c10, **c11; 
      int **P1, **P2, **P3, **P4;
      int **P5, **P6, **P7; 

      // divide matrices into four parts
      a00 = allocateQuadrant(matrixA, d, 0);
      a01 = allocateQuadrant(matrixA, d, 1);
      a10 = allocateQuadrant(matrixA, d, 2);
      a11 = allocateQuadrant(matrixA, d, 3);


      // free Matrix A here

      b00 = allocateQuadrant(matrixB, d, 0);
      b01 = allocateQuadrant(matrixB, d, 1);
      b10 = allocateQuadrant(matrixB, d, 2);
      b11 = allocateQuadrant(matrixB, d, 3);

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

      // compute A11, B11, ... A22, B22 
      P1 = strassenAlgorithm(newDim, sumMatrices(a00, a11, newDim), sumMatrices(b00, b11, newDim), n0);
      P2 = strassenAlgorithm(newDim, sumMatrices(a10, a11, newDim), b00, n0);
      P3 = strassenAlgorithm(newDim, a00, subMatrices(b01, b11, newDim), n0);
      P4 = strassenAlgorithm(newDim, a11, subMatrices(b10, b00, newDim), n0);
      P5 = strassenAlgorithm(newDim, sumMatrices(a00, a01, newDim), b11, n0);
      P6 = strassenAlgorithm(newDim, subMatrices(a10, a00, newDim), sumMatrices(b00, b01, newDim), n0);
      P7 = strassenAlgorithm(newDim, subMatrices(a01, a11, newDim), sumMatrices(b10, b11, newDim), n0);

      // printMatrix(x0, newDim);
      c00 = sumMatrices(subMatrices(sumMatrices(P1, P4, newDim), P5, newDim), P7, newDim);
      c01 = sumMatrices(P3, P5, newDim);
      c10 = sumMatrices(P2, P4, newDim);
      c11 = sumMatrices(subMatrices(sumMatrices(P1, P3, newDim), P2, newDim), P6, newDim);

      matrixC = reglue(c00, c01, c10, c11, dimension);
      // printMatrix(matrixC, dimension);
      freeMatrix(P1, newDim);
      freeMatrix(P2, newDim);
      freeMatrix(P3, newDim);
      freeMatrix(P4, newDim);
      freeMatrix(P5, newDim);
      freeMatrix(P6, newDim);
      freeMatrix(P7, newDim);

      freeMatrix(c00, newDim);
      freeMatrix(c01, newDim);
      freeMatrix(c10, newDim);
      freeMatrix(c11, newDim);

      freeMatrix(a00, newDim);
      freeMatrix(a01, newDim);
      freeMatrix(a10, newDim);
      freeMatrix(a11, newDim);

      freeMatrix(b00, newDim);
      freeMatrix(b01, newDim);
      freeMatrix(b10, newDim);
      freeMatrix(b11, newDim);

      return matrixC; 
    }
 }

int** regularMult(int dimension, int** matrixA, int** matrixB){
  int** regularMatrix = allocateMatrix(dimension);
  int sum = 0; 

  for (int i = 0; i < dimension; i++){
      for (int j = 0; j < dimension; j++){
          for (int k = 0; k < dimension; k++){
              sum = sum + matrixA[i][k] * matrixB[k][j];
          }

          regularMatrix[i][j] = sum;
          sum = 0; 
      }

  }        

  return regularMatrix; 
}

// sum two matrices
/********************************************************/ 
 int** sumMatrices(int** a, int** b, int dimension){
    int** matrixSum = allocateMatrix(dimension);

    for(int i = 0; i < dimension; i++){
      for(int j = 0; j < dimension; j++){
        matrixSum[i][j] = a[i][j] + b[i][j];    
      }
    }  

    return matrixSum; 
 }

 // subtract two matrices 
 // sub two matrices
/********************************************************/
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


  for (int i=0; i<h; i++){
    for (int j=0; j<h; j++){
      gluedMatrix[i][j] = a[i][j];
      gluedMatrix[i][j+h] = b[i][j];
      gluedMatrix[i+h][j] = c[i][j];
      gluedMatrix[i+h][j+h] = d[i][j];
    }
  }

  return gluedMatrix; 
 }
/********************************************************/
// function that returns only diagonal of a matrix
  int** cleanMatrix(int** matrix, int d){
    for(int i = 0; i < d; i++){
      for(int j = 0; j < d; j++){
        if(i != j){
          matrix[i][j] = 0; 
        }
      }
    }
    return matrix; 
  }
/********************************************************/
// function to compare two matrices
  int compareMatrices(int** matrixA, int**matrixB, int d){
     int notEqual = 0; 
     for(int i = 0; i < d; i++){
        if(matrixA[i][i] != matrixB[i][i]){
          notEqual = 1; 
          printf("Not Equal at [%d][%d]", matrixA[i][i], matrixB[i][i]);
        }

     }
     return notEqual; 
  }


