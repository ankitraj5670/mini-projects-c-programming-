#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define max 21

void generate_password(char password[], int strength, int length) {
    char letter[] = "abcdefghijklmnopqrstuvwxyz";
    char LETTER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char num[] = "0123456789";
    char symbol[] = "!@#$%^&*_+:<|?>/.";

    if (strength == 1) {
        for (int i = 0; i < length; i++) {
            password[i] = letter[rand() % 26];
        }
        password[length] = '\0';
    }
    else if (strength == 2) {
        for (int i = 0; i < length; i++) {
            int random_generator = rand() % 2;
            if (random_generator == 0) {
                password[i] = letter[rand() % 26];
            }
            else {
                password[i] = LETTER[rand() % 26];
            }
        }
        password[rand() % length] = letter[rand() % 26];
        password[rand() % length] = LETTER[rand() % 26];
        password[length] = '\0';
    }
    else if (strength == 3) {
        for (int i = 0; i < length; i++) {
            int random_generator = rand() % 3;
            if (random_generator == 0) {
                password[i] = letter[rand() % 26];
            }
            else if (random_generator == 1) {
                password[i] = LETTER[rand() % 26];
            }
            else {
                password[i] = num[rand() % 10];
            }
        }
        password[rand() % length] = letter[rand() % 26];
        password[rand() % length] = LETTER[rand() % 26];
        password[rand() % length] = num[rand() % 10];
        password[length] = '\0';
    }
    else if (strength == 4) {
        for (int i = 0; i < length; i++) {
            int random_generator = rand() % 4;
            if (random_generator == 0) {
                password[i] = letter[rand() % 26];
            }
            else if (random_generator == 1) {
                password[i] = LETTER[rand() % 26];
            }
            else if (random_generator == 2) {
                password[i] = num[rand() % 10];
            }
            else {
                password[i] = symbol[rand() % 17];
            }
        }
        password[rand() % length] = letter[rand() % 26];
        password[rand() % length] = LETTER[rand() % 26];
        password[rand() % length] = num[rand() % 10];
        password[rand() % length] = symbol[rand() % 17];
        password[length] = '\0';
    }
}

bool has_ambiguous_characters(const char password[]) {
    const char ambiguous[] = {'l', '1', 'I', 'o', '0', 'O'};
    const int password_length = strlen(password);

    for (int i = 0; i < password_length; i++) {
        for (int j = 0; j < sizeof(ambiguous) / sizeof(char); j++) {
            if (password[i] == ambiguous[j]) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    srand(time(NULL));
    int strength, length;
    char password[max];

    printf("=====================================\n");
    printf("         PASSWORD GENERATOR          \n");
    printf("=====================================\n\n");

    printf("1: Weak\n2: Moderate\n3: Strong\n4: Very Strong\n");
    printf("Select the desired strength (1-4): ");
    scanf("%d", &strength);

    printf("Select the desired length (6-20): ");
    scanf("%d", &length);

    if (strength < 1 || strength > 4 || length < 6 || length > 20) {
        printf("\nInvalid input!\n");
        exit(0);
    }

    while (1) {
        generate_password(password, strength, length);

        system("cls");

        printf("\n=====================================\n");
        printf("         GENERATED PASSWORD          \n");
        printf("=====================================\n");

        printf("\n%s\n", password);

        if (has_ambiguous_characters(password)) {
            printf("\nNote: The password contains ambiguous characters.\n");
        }

        printf("\n=====================================\n");
        printf("            TRY AGAIN?               \n");
        printf("=====================================\n");

        printf("\n1: YES\n2: NO\n\nSelect an option: ");
        int again;
        scanf("%d", &again);

        if (again == 2) {
            break;
        }

        system("cls");
    }

    printf("\n=====================================\n");
    printf("          THANK YOU FOR USING         \n");
    printf("          PASSWORD GENERATOR!           \n");
    printf("=====================================\n");

    return 0;
}
