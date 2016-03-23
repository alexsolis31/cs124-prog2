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
int** allocateUpperLeft(int** matrix, int dimension);
int** allocateUpperRight(int** matrix, int dimension);
int** allocateBottomLeft(int** matrix, int dimension);
int** allocateBottomRight(int** matrix, int dimension);
// struct element* find(struct element* el);
// struct element* makeset(int x, struct element* el);
// struct element* link(struct element* i, struct element* j);
// struct element join(struct element a, struct element b);
// void generategraph(int n, int dimension, struct edge* array);
// void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));