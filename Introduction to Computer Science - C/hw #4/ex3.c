// Assignment: 3
// Author: Noam Karasso
// Score : 100
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int** minor(int** matrix, int size, int i, int j);
void printMatrix(int** matrix, int rows, int columns);
void freeMatrix(int*** matrix, int row);

int main()
{
	int matrixSize, temp;
	int rows, columns, i, j;
	int** minorP = NULL;
	int** matrix = NULL;
	printf("Please enter the matrix size:\n");
	scanf("%d", &matrixSize);
	rows = matrixSize;
	columns = matrixSize;
	matrixSize *= matrixSize;
	matrix = (int**)malloc(rows * sizeof(int*));
	if (matrix == NULL) {
		printf("Error! memory not allocated!\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < rows; i++) {
		*(matrix + i) = (int*)malloc(columns * sizeof(int));
		if (*(matrix + i) == NULL) {
			printf("Error! memory not allocated!\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("Please enter a matrix\n");
	for (i = 0; i < rows; i++)
		for (j = 0; j < columns; j++) {
			scanf("%d", &temp);
			*(*(matrix+i)+j) = temp;
		}
	printf("Your matrix is:\n");
	printMatrix(matrix, rows, columns);
	printf("Please enter index row i and index column j (when 0 is the first index)\n");
	scanf("%d%d", &i, &j);
	printf("Index row = %d\nIndex column = %d\n", i, j);
	minorP = minor(matrix, matrixSize, i, j);
	printf("The minor matrix with i=%d and j=%d is:\n", i, j);
	printMatrix(minorP, rows-1, columns-1);//minor matrix has 1 less row and columns than the original matrix
	freeMatrix(&matrix, rows);
	matrix = NULL;
	freeMatrix(&minorP, (rows - 1));
	minorP = NULL;
	
	exit(EXIT_SUCCESS);
}

int** minor(int** matrix, int size, int i, int j) {
	int rIndex = 0;//row index counter, increases each time we move to the next row 
	int cIndex = 0;//column index counter, increases each time we put a number and resets every row
	for (int k = 0; k < size; k++) {
		if (k * k == size)
			size = k;
	}
	size--;
	int rows = size;//rows of minor
	int columns = size;//columns of minor
	int** minorP = (int**)malloc(rows * sizeof(int*));
	if (minorP == NULL) {
		printf("Error! memory not allocated!\n");
		exit(EXIT_FAILURE);
	}
	for (int k = 0; k < rows; k++) {
		*(minorP + k) = (int*)malloc(columns * sizeof(int));
		if (*(minorP + k) == NULL) {
			printf("Error! memory not allocated!\n");
			exit(EXIT_FAILURE);
		}
	}
	for (int r = 0; r <= rows; r++) {
		if (r != i) {
			for (int c = 0; c <= columns; c++) {
				if (c != j) {
					*(*(minorP + rIndex) + cIndex) = *(*(matrix + r) + c);
					cIndex++;
				}
			}
			cIndex = 0;
			rIndex++;
		}
	}
	return minorP;
}

void printMatrix(int** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (*(*(matrix + i) + j) >= 0 && *(*(matrix + i) + j) < 10)
				printf(" %d ", *(*(matrix + i) + j));//space it for numbers 0-9 to make it look a bit more aesthetic
			else
				printf("%d ", *(*(matrix + i) + j));
		}
		printf("\n");
	}
}

void freeMatrix(int*** matrix, int row) {
	for (int i = 0; i < row; i++) {
		free(*(*(matrix) + i));
	}
	free(*(matrix));
}