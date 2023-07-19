#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COLOR_RESET "\033[0m"
#define COLOR_HEADER "\033[1;34m"
#define COLOR_MENU "\033[1;36m"
#define COLOR_SUCCESS "\033[1;32m"
#define COLOR_ERROR "\033[1;31m"

enum account_type { SAVING, CURRENT };
enum transaction_type { DEPOSIT, WITHDRAW, TRANSFER };

struct transaction_history {
    char trans_id[9];
    enum transaction_type trans_type;
    float amount;
};

struct account {
    char name[50];
    int age;
    char account_number[17];
    char username[20];
    char password[20];
    int account_balance;
    enum account_type account_type;

    struct transaction_history history[100];
};

void sign_up(struct account a[], int count);
int sign_in(struct account a[], int count);
void deposit(struct account a[], struct transaction_history h[], int identifier, int *count);
void withdraw(struct account a[], struct transaction_history h[], int identifier, int *count);
void transfer(struct account a[], struct transaction_history h[], int identifier, int count, int *count1);
void search(struct account a[], struct transaction_history h[], int count1);
void balance_enq(struct account a[], int identifier);
void display(struct transaction_history h[], int count1);
const char* enumToString(enum transaction_type type);

void clear_screen() {
    system("cls");
}

void print_header() {
    printf("\n%s===================================\n", COLOR_HEADER);
    printf("====   Bank Management System   ====\n");
    printf("===================================%s\n\n", COLOR_RESET);
}

void print_menu() {
    printf("%s1. Sign up for a new account\n", COLOR_MENU);
    printf("2. Sign in to an existing account\n");
    printf("0. Exit%s\n\n", COLOR_RESET);
    printf("Select an option: ");
}

void print_sub_menu() {
    printf("\n%s1. Deposit\n", COLOR_MENU);
    printf("2. Withdraw\n");
    printf("3. Transfer\n");
    printf("4. Search transaction\n");
    printf("5. Balance enquiry\n");
    printf("6. Transaction history\n");
    printf("0. Exit%s\n", COLOR_RESET);
    printf("Choice: ");
}

void print_separator() {
    printf("%s-----------------------------------%s\n", COLOR_RESET, COLOR_RESET);
}

void print_success_message(const char* message) {
    printf("\n%s%s\n", COLOR_SUCCESS, message);
    getchar();
}

void print_invalid_option() {
    printf("%sInvalid option.%s\n", COLOR_ERROR, COLOR_RESET);
}

void print_invalid_credentials() {
    printf("%sInvalid credentials.%s\n", COLOR_ERROR, COLOR_RESET);
}

void print_insufficient_balance() {
    printf("%sInsufficient balance.%s\n", COLOR_ERROR, COLOR_RESET);
}

void print_max_accounts_reached() {
    printf("%sMaximum number of accounts reached.%s\n", COLOR_ERROR, COLOR_RESET);
}

void print_account_details(const struct account* acc) {
    printf("Account Number: %s\n", acc->account_number);
    printf("Name: %s\n", acc->name);
    printf("Age: %d\n", acc->age);
    printf("Account Type: %s\n", acc->account_type == SAVING ? "Saving" : "Current");
    printf("Balance: %d\n", acc->account_balance);
}

void print_transaction(const struct transaction_history* trans) {
    printf("%s | %s | %.2f\n", trans->trans_id, enumToString(trans->trans_type), trans->amount);
}

void sign_up(struct account a[], int count) {
    clear_screen();
    print_header();
    printf("Enter name: ");
    scanf(" %[^\n]", a[count].name);

    printf("Enter age: ");
    scanf("%d", &a[count].age);
    fflush(stdin);

    int flag = 0;
    while (1) {
        printf("Enter username: ");
        scanf(" %[^\n]", a[count].username);

        for (int i = 0; i < count; i++) {
            if (strcmp(a[i].username, a[count].username) == 0) {
                printf("Username already taken!\n");
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            break;
        }
    }

    printf("Enter password: ");
    scanf(" %[^\n]", a[count].password);

    printf("Select an account type:\n1: Saving\n2: Current\n\n");
    printf("Choice: ");
    int choice;
    scanf("%d", &choice);
    fflush(stdin);

    if (choice == 1) {
        a[count].account_type = SAVING;
    } else if (choice == 2) {
        a[count].account_type = CURRENT;
    } else {
        printf("Invalid account type. Setting as Saving by default.\n");
        a[count].account_type = SAVING;
    }

    char acc[17];
    int flag1 = 0;
    while (1) {
        for (int i = 0; i < 16; i++) {
            acc[i] = rand() % 10 + '0';
        }
        acc[16] = '\0';

        for (int i = 0; i < count; i++) {
            if (strcmp(acc, a[i].account_number) == 0) {
                flag1 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            break;
        }
    }

    strcpy(a[count].account_number, acc);

    printf("\nAccount successfully created!\n");
    printf("Account number: %s\n\n", a[count].account_number);
    a[count].account_balance = 0;

    print_success_message("Press enter to continue...");
}

int sign_in(struct account a[], int count) {
    clear_screen();
    print_header();
    printf("Enter username: ");
    char user_name[20];
    scanf(" %[^\n]", user_name);

    printf("Enter password: ");
    char pass[20];
    scanf(" %[^\n]", pass);
    fflush(stdin);

    for (int i = 0; i < count; i++) {
        if ((strcmp(user_name, a[i].username) == 0) && (strcmp(pass, a[i].password) == 0)) {
            return i;
        }
    }

    return -1;
}

void deposit(struct account a[], struct transaction_history h[], int identifier, int *count1) {
    clear_screen();
    print_header();
    printf("Enter the amount to be deposited: ");
    float depo;
    scanf("%f", &depo);
    fflush(stdin);

    if (depo <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    a[identifier].account_balance += depo;

    print_success_message("Amount deposited successfully!");
    print_separator();

    char id[9];
    int flag2 = 0;
    while (1) {
        for (int i = 0; i < 8; i++) {
            id[i] = rand() % 10 + '0';
        }
        id[8] = '\0';

        strcpy(h[*count1].trans_id, id);

        for (int i = 0; i < *count1; i++) {
            if (strcmp(h[*count1].trans_id, h[i].trans_id) == 0) {
                flag2 = 1;
                break;
            }
        }

        if (flag2 == 0) {
            break;
        }
    }

    h[*count1].trans_type = DEPOSIT;
    h[*count1].amount = depo;
    (*count1)++;
}

void withdraw(struct account a[], struct transaction_history h[], int identifier, int *count1) {
    clear_screen();
    print_header();
    printf("Enter the amount to be withdrawn: ");
    float withdraw;
    scanf("%f", &withdraw);
    fflush(stdin);

    if (withdraw <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    if (withdraw > a[identifier].account_balance) {
        print_insufficient_balance();
        return;
    }

    a[identifier].account_balance -= withdraw;

    print_success_message("Amount withdrawn successfully!");
    print_separator();

    char id[9];
    int flag2 = 0;
    while (1) {
        for (int i = 0; i < 8; i++) {
            id[i] = rand() % 10 + '0';
        }
        id[8] = '\0';

        strcpy(h[*count1].trans_id, id);

        for (int i = 0; i < *count1; i++) {
            if (strcmp(h[*count1].trans_id, h[i].trans_id) == 0) {
                flag2 = 1;
                break;
            }
        }

        if (flag2 == 0) {
            break;
        }
    }

    h[*count1].trans_type = WITHDRAW;
    h[*count1].amount = withdraw;
    (*count1)++;
}

void transfer(struct account a[], struct transaction_history h[], int identifier, int count, int *count1) {
    clear_screen();
    print_header();
    printf("Enter the receiver's account number: ");
    char acc_num[17];
    scanf(" %[^\n]", acc_num);
    fflush(stdin);

    acc_num[16] = '\0';

    int flag3 = 0;
    int identifier1;

    for (int i = 0; i < count; i++) {
        if (strcmp(acc_num, a[i].account_number) == 0) {
            flag3 = 1;
            identifier1 = i;
            break;
        }
    }

    if (flag3 == 0) {
        printf("Invalid account number!\n");
        return;
    }

    printf("Enter the amount: ");
    float amt;
    scanf("%f", &amt);
    fflush(stdin);

    if (amt <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    if (amt > a[identifier].account_balance) {
        print_insufficient_balance();
        return;
    }

    a[identifier].account_balance -= amt;
    a[identifier1].account_balance += amt;

    print_success_message("Amount transferred successfully!");
    print_separator();

    char id[9];
    int flag2 = 0;
    while (1) {
        for (int i = 0; i < 8; i++) {
            id[i] = rand() % 10 + '0';
        }
        id[8] = '\0';

        strcpy(h[*count1].trans_id, id);

        for (int i = 0; i < *count1; i++) {
            if (strcmp(h[*count1].trans_id, h[i].trans_id) == 0) {
                flag2 = 1;
                break;
            }
        }

        if (flag2 == 0) {
            break;
        }
    }

    h[*count1].trans_type = TRANSFER;
    h[*count1].amount = amt;
    (*count1)++;
}

void search(struct account a[], struct transaction_history h[], int count1) {
    clear_screen();
    print_header();
    printf("Enter the transaction ID: ");
    char transId[9];
    scanf(" %[^\n]", transId);
    fflush(stdin);

    int flag4 = 0;
    int identifier2;

    for (int i = 0; i < count1; i++) {
        if (strcmp(transId, h[i].trans_id) == 0) {
            flag4 = 1;
            identifier2 = i;
            break;
        }
    }

    if (flag4 == 0) {
        printf("Record not found.\n");
        return;
    }

    print_separator();
    printf("Transaction details\n");
    printf("Transaction ID: %s\n", h[identifier2].trans_id);
    printf("Transaction type: %s\n", enumToString(h[identifier2].trans_type));
    printf("Amount: %.2f\n", h[identifier2].amount);
    print_separator();

    print_success_message("Press enter to continue...");
}

void balance_enq(struct account a[], int identifier) {
    clear_screen();
    print_header();
    printf("Bank balance: %d\n", a[identifier].account_balance);
    print_separator();

    print_success_message("Press enter to continue...");
}

void display(struct transaction_history h[], int count1) {
    clear_screen();
    print_header();
    printf("Transaction history\n");
    printf("Transaction ID | Transaction type | Amount\n");

    for (int i = 0; i < count1; i++) {
        print_transaction(&h[i]);
    }
    print_separator();

    print_success_message("Press enter to continue...");
}

const char* enumToString(enum transaction_type type) {
    switch (type) {
        case DEPOSIT:
            return "Deposit";
        case WITHDRAW:
            return "Withdraw";
        case TRANSFER:
            return "Transfer";
        default:
            return "Unknown";
    }
}

int main() {
    srand(time(NULL));
    struct account a[100];
    struct transaction_history h[100];
    int count = 0, identifier, count1 = 0;

    while (1) {
        clear_screen();
        print_header();
        print_menu();

        int opt;
        scanf("%d", &opt);
        fflush(stdin);

        clear_screen();

        switch (opt) {
            case 0:
                exit(0);
                break;

            case 1:
                if (count < 100) {
                    sign_up(a, count);
                    count++;
                } else {
                    print_max_accounts_reached();
                }
                break;

            case 2:
                identifier = sign_in(a, count);
                clear_screen();

                if (identifier == -1) {
                    print_invalid_credentials();
                } else {
                    print_header();
                    print_account_details(&a[identifier]);
                    print_separator();
                    print_sub_menu();

                    int opt2;
                    scanf("%d", &opt2);
                    fflush(stdin);

                    clear_screen();

                    switch (opt2) {
                        case 0:
                            exit(0);
                            break;

                        case 1:
                            deposit(a, h, identifier, &count1);
                            break;

                        case 2:
                            withdraw(a, h, identifier, &count1);
                            break;

                        case 3:
                            transfer(a, h, identifier, count, &count1);
                            break;

                        case 4:
                            search(a, h, count1);
                            break;

                        case 5:
                            balance_enq(a, identifier);
                            break;

                        case 6:
                            display(h, count1);
                            break;

                        default:
                            print_invalid_option();
                    }
                }
                break;

            default:
                print_invalid_option();
        }
    }
    return 0;
}
