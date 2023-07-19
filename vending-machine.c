#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct vending_machine
{
    char product_name[50];
    float price;
    int quantity;
    int item_code;
};

void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void display_menu(struct vending_machine p[], int count)
{
    printf("=============================================\n");
    printf("             VENDING MACHINE MENU            \n");
    printf("=============================================\n");
    printf("Item Code |    Item Name     |  Price  | Quantity\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-9d | %-15s | $%-5.2f  | %-8d\n", p[i].item_code, p[i].product_name, p[i].price, p[i].quantity);
    }
    printf("=============================================\n");
}

bool authenticate(char username[], char password[])
{
    char user[20];
    char pass[20];
    printf("=============================================\n");
    printf("              AUTHENTICATION                 \n");
    printf("=============================================\n");
    printf("Enter username: ");
    scanf(" %[^\n]", user);
    printf("Enter password: ");
    scanf(" %[^\n]", pass);
    getchar();
    printf("Press Enter to continue...");
    getchar();
    clear_screen();
    return (strcmp(username, user) == 0 && strcmp(password, pass) == 0);
}

void add_new_item(struct vending_machine p[], int *count)
{
    clear_screen();
    printf("=============================================\n");
    printf("               ADD NEW ITEM                   \n");
    printf("=============================================\n");
    if (*count >= 100)
    {
        printf("Vending machine is full!\n");
        return;
    }
    printf("Enter item name: ");
    scanf(" %[^\n]", p[*count].product_name);
    printf("Enter price: ");
    scanf("%f", &p[*count].price);
    printf("Enter quantity: ");
    scanf("%d", &p[*count].quantity);
    p[*count].item_code = *count + 1;
    (*count)++;
    printf("Item added successfully!\n");
    getchar();
    printf("Press Enter to continue...");
    getchar();
    clear_screen();
}

void delete_item(struct vending_machine p[], int *count)
{
    clear_screen();
    printf("=============================================\n");
    printf("               DELETE ITEM                    \n");
    printf("=============================================\n");
    display_menu(p, *count);
    if (*count == 0)
    {
        printf("No items in the vending machine.\n");
        return;
    }
    int item_code;
    printf("Enter the item code of the item to be removed: ");
    scanf("%d", &item_code);
    int item_index = -1;
    for (int i = 0; i < *count; i++)
    {
        if (item_code == p[i].item_code)
        {
            item_index = i;
            break;
        }
    }
    if (item_index == -1)
    {
        printf("Item not found.\n");
        return;
    }
    for (int i = item_index; i < *count - 1; i++)
    {
        strcpy(p[i].product_name, p[i + 1].product_name);
        p[i].price = p[i + 1].price;
        p[i].item_code = p[i + 1].item_code;
        p[i].quantity = p[i + 1].quantity;
    }
    (*count)--;
    printf("Item removed successfully!\n");
    getchar(); // Consume newline character
    printf("Press Enter to continue...");
    getchar(); // Wait for user to press Enter
    clear_screen();
}

int main()
{
    int count = 3;
    char username[] = "seller_123";
    char password[] = "seller_123";
    struct vending_machine p[100] = {
        {"Mango Juice", 2, 5, 1},
        {"Apple Juice", 2.5, 5, 2},
        {"Lime Juice", 1.5, 5, 3}
    };

    while (1)
    {
        clear_screen();
        printf("\n=============================================\n");
        printf("            WELCOME TO VENDING MACHINE        \n");
        printf("=============================================\n");
        printf("1. Seller Menu\n");
        printf("2. Consumer Menu\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        int option;
        scanf("%d", &option);

        switch (option)
        {
            case 0:
                clear_screen();
                printf("\nThank you for using the vending machine. Goodbye!\n");
                return 0;

            case 1:
                clear_screen();
                printf("\n=============================================\n");
                printf("                  SELLER MENU                 \n");
                printf("=============================================\n");
                if (!authenticate(username, password))
                {
                    printf("Authentication failed. Access denied.\n");
                    break;
                }
                int seller_option;
                printf("\nSeller Options:\n");
                printf("1. Add New Item\n");
                printf("2. Delete Item\n");
                printf("0. Back\n");
                printf("Select an option: ");
                scanf("%d", &seller_option);
                switch (seller_option)
                {
                    case 1:
                        add_new_item(p, &count);
                        break;
                    case 2:
                        delete_item(p, &count);
                        break;
                    case 0:
                        clear_screen();
                        printf("Returning to main menu.\n");
                        break;
                    default:
                        clear_screen();
                        printf("Invalid option. Please try again.\n");
                        break;
                }
                break;

            case 2:
                clear_screen();
                printf("\n=============================================\n");
                printf("                CONSUMER MENU                 \n");
                printf("=============================================\n");
                display_menu(p, count);
                printf("Enter the item code of the item to be bought: ");
                int item_code;
                scanf("%d", &item_code);
                if (item_code >= 1 && item_code <= count)
                {
                    int quantity;
                    printf("Enter the quantity of items to be dispatched: ");
                    scanf("%d", &quantity);
                }
                else
                {
                    printf("Invalid item code. Please try again.\n");
                }
                getchar();
                printf("Press Enter to continue...");
                getchar();
                clear_screen();
                break;

            default:
                clear_screen();
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
}
