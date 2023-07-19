#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_header()
{
    printf("*****************************************************\n");
    printf("*               Rock Paper Scissors                  *\n");
    printf("*****************************************************\n");
}

void print_options()
{
    printf("Choose an option:\n");
    printf("1: Rock\n");
    printf("2: Paper\n");
    printf("3: Scissors\n");
    printf("0: Exit\n");
}

void print_result(int user_choice, int comp_choice)
{
    printf("-----------------------------------------------------\n");
    printf("You chose: ");
    switch (user_choice) {
        case 1:
            printf("Rock\n");
            break;
        case 2:
            printf("Paper\n");
            break;
        case 3:
            printf("Scissors\n");
            break;
    }

    printf("Computer chose: ");
    switch (comp_choice) {
        case 1:
            printf("Rock\n");
            break;
        case 2:
            printf("Paper\n");
            break;
        case 3:
            printf("Scissors\n");
            break;
    }

    printf("Result: ");
    switch (user_choice) {
        case 1:
            switch (comp_choice) {
                case 1:
                    printf("It's a tie!\n");
                    break;
                case 2:
                    printf("You lose!\n");
                    break;
                case 3:
                    printf("You win!\n");
                    break;
            }
            break;
        case 2:
            switch (comp_choice) {
                case 1:
                    printf("You win!\n");
                    break;
                case 2:
                    printf("It's a tie!\n");
                    break;
                case 3:
                    printf("You lose!\n");
                    break;
            }
            break;
        case 3:
            switch (comp_choice) {
                case 1:
                    printf("You lose!\n");
                    break;
                case 2:
                    printf("You win!\n");
                    break;
                case 3:
                    printf("It's a tie!\n");
                    break;
            }
            break;
    }

    printf("-----------------------------------------------------\n");
}

int main()
{
    int user_choice, comp_choice;
    srand(time(NULL));

    while (1) {
        print_header();
        print_options();

        printf("\nEnter your choice: ");
        scanf("%d", &user_choice);

        if (user_choice == 0) {
            printf("Thank you for playing Rock Paper Scissors. Goodbye!\n");
            break;
        } else if (user_choice < 1 || user_choice > 3) {
            printf("Invalid option. Please choose a valid option.\n");
            continue;
        }

        comp_choice = rand() % 3 + 1;
        print_result(user_choice, comp_choice);

        printf("\n");
        printf("Press Enter to continue...");
        getchar();
        getchar();
        system("cls");
    }

    return 0;
}
