#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// struct edge {
// 	int src;
// 	int dest;
// 	float weight;
// };

// struct element {
// 	struct element* parent;
// 	int number;
// 	int rank;
// };

int readFile(char* fileName, int dimension);
void printMatrix(int** matrix, int dimension);
int** allocateQuadrant(int** matrix, int d, int quadrant);
int** strassenAlgorithm(int dimension, int** matrixA, int** matrixB);
int** sumMatrices(int** a, int** b, int dimension);
int** allocateMatrix(int d);
int** reglue(int** a, int** b, int** c, int** d, int dimension);

// int** allocateUpperLeft(int** matrix, int dimension);
// int** allocateUpperRight(int** matrix, int dimension);
// int** allocateBottomLeft(int** matrix, int dimension);
// int** allocateBottomRight(int** matrix, int dimension);
