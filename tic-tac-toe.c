#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

void clearScreen() {
    system(CLEAR_SCREEN);
}

void display(char arr[][3]) {
    clearScreen();

    printf("\n");
    printf("\033[1;36mTIC-TAC-TOE\033[0m\n\n");

    printf("\033[1;37m");
    printf(" %c \033[1;33m| \033[1;37m%c \033[1;33m| \033[1;37m%c \033[0m\n", arr[0][0], arr[0][1], arr[0][2]);
    printf("\033[1;33m---+---+---\033[0m\n");
    printf("\033[1;37m");
    printf(" %c \033[1;33m| \033[1;37m%c \033[1;33m| \033[1;37m%c \033[0m\n", arr[1][0], arr[1][1], arr[1][2]);
    printf("\033[1;33m---+---+---\033[0m\n");
    printf("\033[1;37m");
    printf(" %c \033[1;33m| \033[1;37m%c \033[1;33m| \033[1;37m%c \033[0m\n", arr[2][0], arr[2][1], arr[2][2]);

    printf("\n");
}

int isValidMove(char arr[][3], int block) {
    int row = (block - 1) / 3;
    int col = (block - 1) % 3;
    return (block >= 1 && block <= 9 && arr[row][col] != 'X' && arr[row][col] != 'O');
}

void makeMove(char arr[][3], int block, char symbol) {
    int row = (block - 1) / 3;
    int col = (block - 1) % 3;
    arr[row][col] = symbol;
}

int checkWin(char arr[][3]) {
    for (int i = 0; i < 3; i++) {
        if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2])
            return 1;
    }

    for (int i = 0; i < 3; i++) {
        if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i])
            return 1;
    }

    if ((arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]) ||
        (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0]))
        return 1;

    return 0;
}

int main() {
    char arr[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    int currentPlayer = 1;
    int block;
    char symbol;

    while (1) {
        display(arr);

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        symbol = (currentPlayer == 1) ? 'X' : 'O';

        printf("\nPlayer-%d (\033[1;31m%c\033[0m)\n", currentPlayer, symbol);
        printf("Select a block: ");
        scanf("%d", &block);

        if (!isValidMove(arr, block)) {
            printf("Invalid block! Please try again.\n");
            continue;
        }

        makeMove(arr, block, symbol);

        if (checkWin(arr)) {
            display(arr);
            printf("\nPlayer-%d (\033[1;31m%c\033[0m) wins!\n", currentPlayer, symbol);
            break;
        }

        int isFull = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (arr[i][j] != 'X' && arr[i][j] != 'O') {
                    isFull = 0;
                    break;
                }
            }
            if (!isFull)
                break;
        }

        if (isFull) {
            display(arr);
            printf("\nThe game ends in a draw!\n");
            break;
        }
    }

    return 0;
}
