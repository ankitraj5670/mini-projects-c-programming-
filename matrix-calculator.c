#include <stdio.h>
#include <stdlib.h>

#define N 100

void clearScreen() {
    system("clear || cls");
}

void printHeader() {
    printf("======================================\n");
    printf("         Matrix Operations Menu        \n");
    printf("======================================\n");
}

void printMenu() {
    printf("\n1. Matrix Addition/Subtraction\n");
    printf("2. Determinant of a Matrix\n");
    printf("3. Matrix Multiplication\n");
    printf("4. Inverse of a Matrix\n");
    printf("0. Exit\n");
}

void printMatrix(int matrix[N][N], int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void readMatrix(int matrix[N][N], int rows, int columns) {
    printf("Enter elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void matrixAdditionSubtraction() {
    int rows1, columns1;
    int matrix1[N][N];

    printf("Matrix-1\n");
    printf("Rows (1-100): ");
    scanf("%d", &rows1);
    printf("Columns (1-100): ");
    scanf("%d", &columns1);

    readMatrix(matrix1, rows1, columns1);

    int rows2, columns2;
    int matrix2[N][N];

    printf("Matrix-2\n");
    printf("Rows (1-100): ");
    scanf("%d", &rows2);
    printf("Columns (1-100): ");
    scanf("%d", &columns2);

    readMatrix(matrix2, rows2, columns2);

    clearScreen();

    if (rows1 != rows2 || columns1 != columns2) {
        printf("Matrix operation not possible!\n");
        return;
    }

    printf("Matrix Addition/Subtraction:\n");
    printf("============================\n");

    printf("Matrix-1:\n");
    printMatrix(matrix1, rows1, columns1);

    printf("\n");

    printf("Matrix-2:\n");
    printMatrix(matrix2, rows2, columns2);

    printf("\n");

    printf("Result:\n");
    printf("=======\n");

    printf("1: Addition\n");
    printf("2: Subtraction\n");
    printf("Select an option: ");
    int choice;
    scanf("%d", &choice);

    int result[N][N];

    if (choice == 1) {
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
    } else if (choice == 2) {
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                result[i][j] = matrix1[i][j] - matrix2[i][j];
            }
        }
    }

    printMatrix(result, rows1, columns1);
}

int determinant(int matrix[N][N], int size) {
    int det = 0;

    if (size == 1) {
        return matrix[0][0];
    } else if (size == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    } else {
        int temp[N][N];
        int sign = 1;

        for (int col = 0; col < size; col++) {
            int submatrix_row = 0;

            for (int i = 1; i < size; i++) {
                int submatrix_col = 0;

                for (int j = 0; j < size; j++) {
                    if (j != col) {
                        temp[submatrix_row][submatrix_col] = matrix[i][j];
                        submatrix_col++;
                    }
                }
                submatrix_row++;
            }

            det += sign * matrix[0][col] * determinant(temp, size - 1);
            sign = -sign;
        }
    }

    return det;
}

void matrixDeterminant() {
    int rows, columns;
    int matrix[N][N];

    printf("Matrix\n");
    printf("Rows (1-100): ");
    scanf("%d", &rows);
    printf("Columns (1-100): ");
    scanf("%d", &columns);

    if (rows != columns) {
        printf("Matrix must be square for determinant calculation.\n");
        return;
    }

    readMatrix(matrix, rows, columns);

    clearScreen();

    printf("Matrix:\n");
    printMatrix(matrix, rows, columns);

    printf("\n");

    int det = determinant(matrix, rows);
    printf("Determinant of the matrix is: %d\n", det);
}

void matrixMultiplication() {
    int rows1, columns1;
    int matrix1[N][N];

    printf("Matrix-1\n");
    printf("Rows (1-100): ");
    scanf("%d", &rows1);
    printf("Columns (1-100): ");
    scanf("%d", &columns1);

    readMatrix(matrix1, rows1, columns1);

    int rows2, columns2;
    int matrix2[N][N];

    printf("Matrix-2\n");
    printf("Rows (1-100): ");
    scanf("%d", &rows2);
    printf("Columns (1-100): ");
    scanf("%d", &columns2);

    readMatrix(matrix2, rows2, columns2);

    clearScreen();

    if (columns1 != rows2) {
        printf("Matrix multiplication not possible!\n");
        return;
    }

    printf("Matrix Multiplication:\n");
    printf("======================\n");

    printf("Matrix-1:\n");
    printMatrix(matrix1, rows1, columns1);

    printf("\n");

    printf("Matrix-2:\n");
    printMatrix(matrix2, rows2, columns2);

    printf("\n");

    int result[N][N];

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < columns2; j++) {
            result[i][j] = 0;

            for (int k = 0; k < columns2; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    printf("Result:\n");
    printMatrix(result, rows1, columns2);
}

void matrixInverse() {
    int rows, columns;
    int matrix[N][N];

    printf("Matrix\n");
    printf("Rows (1-100): ");
    scanf("%d", &rows);
    printf("Columns (1-100): ");
    scanf("%d", &columns);

    if (rows != columns) {
        printf("Matrix must be square for inverse calculation.\n");
        return;
    }

    readMatrix(matrix, rows, columns);

    clearScreen();

    printf("Matrix:\n");
    printMatrix(matrix, rows, columns);

    printf("\n");

    double temp;
    double ratio;
    double inverse[N][N];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (i == j)
                inverse[i][j] = 1.0;
            else
                inverse[i][j] = 0.0;
        }
    }

    for (int i = 0; i < rows; i++) {
        if (matrix[i][i] == 0.0) {
            printf("Inverse does not exist.\n");
            return;
        }

        for (int j = 0; j < rows; j++) {
            if (j != i) {
                ratio = matrix[j][i] / matrix[i][i];

                for (int k = 0; k < rows; k++) {
                    matrix[j][k] -= ratio * matrix[i][k];
                    inverse[j][k] -= ratio * inverse[i][k];
                }
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        temp = matrix[i][i];

        for (int j = 0; j < rows; j++) {
            matrix[i][j] /= temp;
            inverse[i][j] /= temp;
        }
    }

    printf("Inverse Matrix:\n");
    printMatrix(inverse, rows, columns);
}

int main() {
    while (1) {
        clearScreen();
        printHeader();
        printMenu();

        int option;
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option) {
            case 0:
                exit(0);
            case 1:
                clearScreen();
                printHeader();
                matrixAdditionSubtraction();
                break;
            case 2:
                clearScreen();
                printHeader();
                matrixDeterminant();
                break;
            case 3:
                clearScreen();
                printHeader();
                matrixMultiplication();
                break;
            case 4:
                clearScreen();
                printHeader();
                matrixInverse();
                break;
            default:
                printf("Invalid option! Please try again.\n");
                break;
        }

        printf("\nPress Enter to continue...");
        getchar(); // Consume the newline character
        getchar(); // Wait for Enter key
    }

    return 0;
}
