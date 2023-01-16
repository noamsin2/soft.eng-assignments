// Assignment: 3
// Author: Noam Karasso
// Score : 100
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void BuildMatrix(int*** matrix, int row, int column);
void addColumn(int*** matrix, int rows, int* columns, int* newCol, int row);
void printMatrix(int*** matrix, int rows, int columns);
void removeColumn(int*** matrix, int rows, int* columns, int colNum);
int** multiplyMatrixes(int** mat1, int** mat2, int m, int n, int k);
void transpose(int*** matrix, int* row, int* column);

int main()
{
	int** matrix = NULL;
	int option;
	int m, n, k;
	int rows, columns;
	int row, colNum;
	int* columnsP = &columns;
	int* rowsP = &rows;
	do {
		printf("Please choose an option.\n");
		printf("1 - Add Column\n");
		printf("2 - Remove Column\n");
		printf("3 - Multiply Matrixes\n");
		printf("4 - Transpose\n");
		printf("5 - Exit\n");
		scanf("%d", &option);
		switch (option) {
		case 1:
			if (matrix == NULL) {
				printf("First we need to build a matrix\n");
				printf("Please enter the amount of rows and then amount of columns.\n");
				scanf("%d%d", &rows, &columns);
				BuildMatrix(&matrix, rows, columns);
			}
			printf("Please enter row\n");
			scanf("%d", &row);
			int* newCol = (int*)malloc(row * (sizeof(int)));
			if (newCol == NULL) {
				printf("Error! memory not allocated!\n");
				exit(EXIT_FAILURE);
			}
			printf("Please enter the new column you'd like to add\n");
			for (int i = 0; i < row; i++)
				scanf("%d", (newCol + i));
			addColumn(&matrix, rows, columnsP, newCol, row);
			printMatrix(&matrix, rows, columns);
			
			break;
		case 2:
			if (matrix == NULL) {
				printf("First we need to build a matrix\n");
				printf("Please enter the amount of rows and then amount of columns.\n");
				scanf("%d%d", &rows, &columns);
				BuildMatrix(&matrix, rows, columns);
			}
			printf("Please enter the column you'd like to remove with '0' being the first column\n");
			scanf("%d", &colNum);
			removeColumn(&matrix, rows, columnsP, colNum);
			printMatrix(&matrix, rows, columns);
			break;
		case 3:
			if (matrix == NULL) {
				printf("First we need to build a matrix\n");
				printf("Please enter the amount of rows and then amount of columns.\n");
				scanf("%d%d", &m, &n);
				BuildMatrix(&matrix, m, n);
			}
			else {
				m = rows;
				n = columns;
			}
			printf("Please enter the amount of columns for the second matrix.\n");
			scanf("%d", &k);
			int** mat2 = NULL;
			BuildMatrix(&mat2, n, k);

			matrix = multiplyMatrixes(matrix, mat2, m, n, k);
			rows = m;
			columns = k;
			printMatrix(&matrix, rows, columns);
			break;
		case 4:
			transpose(&matrix, rowsP, columnsP);
			printMatrix(&matrix, rows, columns);
		}
	} while (option != 5);
	
	for (int i = 0; i < rows; i++)
		free(matrix[i]);
	free(matrix);
	matrix = NULL;

	printf("Have an awesome day! Trilili Tralala :)\n");
	exit(EXIT_SUCCESS);
}

int** multiplyMatrixes(int** mat1, int** mat2, int m, int n, int k) {
	int sum = 0;
	int index = 0;
	//create mat3 as temp
	int** mat3 = (int**)malloc(m * sizeof(int*));
	if (mat3 == NULL) {
		printf("Error! memory not allocated!\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < m; i++) {
		*(mat3 + i) = (int*)malloc(k * sizeof(int));
		if (*(mat3 + i) == NULL) {
			printf("Error! memory not allocated!\n");
			exit(EXIT_FAILURE);
		}
	}
	//multiplying matrixes mat1 and mat2 into mat3
	for (int l = 0; l < m; l++) {
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < n; j++) {
				sum += (int)mat1[l][j] * (int)mat2[j][index];
			}
			*(*(mat3 + l) + index) = sum;
			sum = 0;
			index++;
		}
		index = 0;
	}
	//realloc mat1 so we can keep using it in main
	for (int i = 0; i < m; i++) {
		*(mat1 + i) = realloc(*(mat1 + i), k * sizeof(int));
		if (*(mat1 + i) == NULL) {
			printf("Error! memory not allocated!\n");
			exit(EXIT_FAILURE);
		}
	}
	//take values for mat3 and store in mat1
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			*(*(mat1 + i) + j) = *(*(mat3 + i) + j);
		}
	}
	//important to free the old matrixes after we used them!!
	for (int r = 0; r < n; r++)
		free(mat2[r]);
	free(mat2);
	mat2 = NULL;
	for (int r = 0; r < m; r++)
		free(mat3[r]);
	free(mat3);
	mat3 = NULL;

	return mat1;
}

void transpose(int*** matrix, int* row, int* column) {
	int newRow = *column;
	int newColumn = *row;
	int** transmat = (int**)malloc(newRow * sizeof(int*));
	if (transmat == NULL) {
		printf("Error! memory not allocated!\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < newRow; i++) {
		*(transmat + i) = (int*)malloc(newColumn * sizeof(int));
		if (*(transmat + i) == NULL) {
			printf("Error! memory not allocated\n");
			exit(EXIT_FAILURE);
		}
	}
	for (int i = 0; i < newRow; i++) {
		for (int j = 0; j < newColumn; j++) {
			*(*(transmat + i) + j) = *(*(*(matrix) + j) + i);
		}
	}
	//freeing the old and ugly matrix
	for (int i = 0; i < *row; i++)
		free(*(*(matrix)+i));
	free(*(matrix));
	//moving the pointer to the new and improved matrix
	*(matrix) = transmat;
	*column = newColumn;
	*row = newRow;
}

void removeColumn(int*** matrix, int rows, int* columns, int colNum) {
	if (colNum < *columns && colNum > 0) {//happens if the collumn we'd like to remove is in the matrix range.
		int newColumns = *columns - 1;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j <= *columns; j++) {
				if (j >= colNum && j < (newColumns))//happens until it reaches the last column
					*(*(*(matrix)+i) + j) = *(*(*(matrix)+i) + j + 1);
			}
			*(*(matrix)+i) = realloc(*(*(matrix)+i), newColumns * sizeof(int));
			if (*(*(matrix)+i) == NULL) {
				printf("Error! memory not allocated\n");
				exit(EXIT_FAILURE);
			}
		}
		*columns = newColumns;
	}
	else if (colNum <*columns && colNum ==0) {
		free(*(*(matrix)));
		free(*(matrix));
	}
	else
		printf("Out of matrix range, can't remove!\n");
}

void addColumn(int*** matrix, int rows, int* columns, int* newCol, int row) {
	if (row == rows) {
		int newColumns = (*columns + 1);
		for (int i = 0; i < rows; i++) {
			matrix[0][i] = realloc(matrix[0][i], newColumns * sizeof(int));
			if (matrix[0][i] == NULL) {
				printf("Error! memory not allocated\n");
				exit(EXIT_FAILURE);
			}
		}
		for (int i = 0; i < rows; i++) {
			matrix[0][i][*columns] = newCol[i];
		}
		free(newCol);// free the column after we put it in the matrix
		newCol = NULL;
		*columns += 1;
	}
	
	else
		printf("can't add this column to the matrix!\n");
}

void BuildMatrix(int*** matrix, int row, int column) {
	int temp;
	*(matrix) = (int**)malloc(row * sizeof(int*));//*(matrix) because its a pointer that's pointing to the 2d array
	if (*(matrix) == NULL) {
		printf("Error! memory not allocated!\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < row; i++) {
		*(*(matrix)+i) = (int*)malloc(column * sizeof(int));
		if (*(*(matrix)+i) == NULL) {
			printf("Error! memory not allocated\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("Please enter the matrix\n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			scanf("%d", &temp);
			*(*(*(matrix) + i) + j) = temp;
		}
	}
}

void printMatrix(int*** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (*(*(*(matrix)+ i) + j) >= 0 && *(*(*(matrix) + i) + j) < 10)//space it for numbers 0-9 to make it look a bit more aesthetic
				printf(" %d ", (int)matrix[0][i][j]);//[0][i][j] because its a pointer that's pointing to the 2d array
			else
				printf("%d ", (int)matrix[0][i][j]);
		}
		printf("\n");
	}
}