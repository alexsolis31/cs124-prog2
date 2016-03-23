 int** strassenAlgorithm(int dimension, int** matrixA, int** matrixB ){
    int d = dimension;
    
    // Base Case: when matrix is 1x1 (scalar multiplication)
    if (d == 1){
      matrixC[0][0] = matrixA[0][0] * matrixB[0][0];
      return matrixC; 
    }

    else{
      newDim = d/2; 
      int **a00, **a01, **a10, **a11; 
      int **b00, **b01, **b10, **b11; 
      int **c00, **c01, **c10, **c11; 
      int **x1, **x2, **x3, **x4, **x5;
      int **x6, **x7, **x8; 

      // divide matrices into four parts
      a00 = allocateQuadrant(matrixA, d, 0);
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
      x0 = strassenAlgorithm(newDim, a11, b11);
      x1 = strassenAlgorithm(newDim, a01, b10);
      x2 = strassenAlgorithm(newDim, a00, b01);
      x3 = strassenAlgorithm(newDim, a01, b11);
      x4 = strassenAlgorithm(newDim, a10, b00);
      x5 = strassenAlgorithm(newDim, a11, b10);
      x6 = strassenAlgorithm(newDim, a10, b01);
      x7 = strassenAlgorithm(newDim, a11, b11);

      c00 = sum(x0, x1);
      c01 = sum(x2, x3);
      c10 = sum(x4, x5);
      c11 = sum(x6, x7)

      matrixA = restich(c00, c01, c10, c11);
      return matrixA; 
    }
 }
/********************************************************/
 // sum two vertices 
 int** sumMatrices(int** a, int** b, int dimension){
    int** matrixSum = allocateMatrix(dimension);

    for(int i = 0, i<dimension; i++){
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

 int** restich(int** a, int** b, int** c, int** d){
 
    

 }