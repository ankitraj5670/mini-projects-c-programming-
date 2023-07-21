#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX 100

enum roles {ASSISTANT_PROFESSOR, ASSOCIATE_PROFESSOR, HEAD_OF_DEPARTMENT, DIRECTOR, PRINCIPAL, DEAN};

enum gender {MALE, FEMALE, OTHER};

struct employee
{
    char name[50];
    char password[20];
    char contact_info[20];
    enum roles designation;
    char eid[7];
    enum gender type;
    int age;
    float base_salary;
    float HRA;
    float income_tax;
    float bonus;
    float ctc;
    bool leave_applied;
    int nos;
    int prev_leave;
    bool approval_leave;
};

const char* enumToString(int val)
{
    switch (val)
    {
    case ASSISTANT_PROFESSOR:
        return "Assistant Professor";
    case ASSOCIATE_PROFESSOR:
        return "Associate Professor";
    case HEAD_OF_DEPARTMENT:
        return "Head of Department";
    case DIRECTOR:
        return "Director";
    case PRINCIPAL:
        return "Principal";
    case DEAN:
        return "Dean";
    default:
        return "Unknown";
    }
}

const char* enumToString_(int val)
{
    switch (val)
    {
    case MALE:
        return "male";
    case FEMALE:
        return "female";
    case OTHER:
        return "other";
    default:
        return "unknown";
    }
}

void add_new(struct employee e[], int count)
{
    printf("------------------------------------\n");
    printf("======= Employee Information =======\n");
    printf("------------------------------------\n");
    printf("\n[1] Enter name: ");
    scanf(" %[^\n]", e[count].name);
    while(1)
    {
        printf("\n[2] Enter age: ");
        scanf("%d", &e[count].age);
        if (e[count].age <= 0)
        {
            printf("\nEnter a valid age!\n");
            continue;
        }
        break;
    }
    printf("\n[3] Enter contact information: ");
    scanf(" %[^\n]", e[count].contact_info);
    while(1)
    {
        printf("\n[4] Select gender:\n1: Male    2: Female    3: Other\nSelect: ");
        int opt3;
        scanf("%d", &opt3);
        if (opt3 == 1)
        {
            e[count].type = MALE;
        }
        else if (opt3 == 2)
        {
            e[count].type = FEMALE;
        }
        else if (opt3 == 3)
        {
            e[count].type = OTHER;
        }
        else
        {
            printf("\nEnter a valid option!\n");
            continue;
        }
        break;
    }
    char e_id[7];
    while(1)
    {
        for (int i = 0; i < 6; i++)
        {
            e_id[i] = rand()%10 + '0';
        }
        e_id[6] = '\0';
        int i;
        for (i = 0; i < count; i++)
        {
            if (strcmp(e_id, e[i].eid) == 0)
            {
                break;
            }
        }
        if (i != count)
        {
            continue;
        }
        break;
    }
    strcpy(e[count].eid, e_id);
    printf("\n[5] Employee ID: %s\n", e[count].eid);
    char e_pass[20];
    for (int i = 0; i < 8; i++)
    {
        e_pass[i] = rand()%10 + '0';
    }
    e_pass[8] = '\0';
    strcpy(e[count].password, e_pass);
    printf("\n[6] Employee dummy password: %s\n", e[count].password);
    int opt4;
    while(1)
    {
        printf("\n[7] Select designation:\n");
        printf("1: Assistant Professor    2: Associate Professor    3: Head of Department\n");
        printf("4: Director               5: Principal              6: Dean\nSelect: ");
        scanf("%d", &opt4);
        if (opt4 < 1 || opt4 > 6)
        {
            printf("\nSelect a valid option!\n");
            continue;
        }
        break;
    }
    e[count].designation = opt4 - 1;
    while(1)
    {
        printf("\n[8] Enter Basic salary per annum: ");
        scanf("%f", &e[count].base_salary);
        if (e[count].base_salary < 0)
        {
            printf("\nInvalid input!\n");
            continue;
        }
        break;
    }
    e[count].HRA = 40;
    e[count].bonus = 10;
    if (e[count].base_salary <= 300000)
    {
        e[count].income_tax = 0;
    }
    else if (e[count].base_salary > 300000 && e[count].base_salary <= 600000)
    {
        e[count].income_tax = 5;
    }
    else if (e[count].base_salary > 600000 && e[count].base_salary <= 900000)
    {
        e[count].income_tax = 10;
    }
    else if (e[count].base_salary > 900000 && e[count].base_salary <= 1200000)
    {
        e[count].income_tax = 15;
    }
    else if (e[count].base_salary > 1200000 && e[count].base_salary <= 1500000)
    {
        e[count].income_tax = 20;
    }
    else
    {
        e[count].income_tax = 30;
    }
    e[count].ctc = e[count].base_salary + e[count].base_salary*0.4 + e[count].base_salary*0.1 - e[count].base_salary*(e[count].income_tax/100);
    e[count].leave_applied = false;
    e[count].approval_leave = true;
    e[count].nos = 0;
    e[count].prev_leave = 0;
    getchar();
    printf("\nPress enter to continue...\n");
    getchar();
    system("cls");
}

void grant_promo(struct employee e[], int count)
{
    system("cls");
    printf("\nEnter the ID of employee to be promoted: ");
    char emp_id[7];
    int identifier;
    int flag = 0;
    scanf(" %[^\n]", emp_id);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(emp_id, e[i].eid) == 0)
        {
            identifier = i;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("\nInvalid ID!\n");
        getchar();
        printf("press enter to continue...\n");
        getchar();
        system("cls");
        return;
    }
    if (e[identifier].designation == DEAN)
    {
        printf("\nCan't promote any further!\n");
        getchar();
        printf("press enter to continue...\n");
        getchar();
        system("cls");
        return;
    }
    printf("\nEmployee ID: %s is now %s!\n", e[identifier].eid, enumToString(e[identifier].designation + 1));
    e[identifier].designation++;
    getchar();
    printf("\npress enter to continue...\n");
    getchar();
    system("cls");
}

void update_salary(struct employee e[], int count)
{
    system("cls");
    printf("\nEnter the ID of employee whose salary is to be updated: ");
    char empid[7];
    int identifier;
    int flag = 0;
    scanf(" %[^\n]", empid);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(empid, e[i].eid) == 0)
        {
            identifier = i;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("\nInvalid ID\n");
        getchar();
        printf("press enter to continue...\n");
        getchar();
        system("cls");
        return;
    }
    printf("\nEnter increment in percent: ");
    float inc;
    scanf("%f", &inc);
    if (inc < 0)
    {
        printf("\nInvalid input!\n");
        getchar();
        printf("press enter to continue...\n");
        getchar();
        system("cls");
        return;
    }
    e[identifier].base_salary += e[identifier].base_salary * (inc / 100);
    e[identifier].ctc = e[identifier].base_salary + e[identifier].base_salary*0.4 + e[identifier].base_salary*0.1 - e[identifier].base_salary*(e[identifier].income_tax/100);
    getchar();
    printf("\npress enter to continue...\n");
    getchar();
    system("cls");
}

void get_data(struct employee e[], int count)
{
    system("cls");
    printf("------------------------------------\n");
    printf("========== Employee Data ===========\n");
    printf("------------------------------------\n\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("| Employee ID |   Employee Name   | Age | Gender | Contact Info  |      Designation      |    Annual Salary    |\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("| %-11s | %-17s | %-3d | %-6s | %-13s | %-21s | $%-18.2f |\n", e[i].eid, e[i].name, e[i].age, enumToString_(e[i].type), e[i].contact_info, enumToString(e[i].designation), e[i].ctc);
    }
    printf("----------------------------------------------------------------------------------------------------------------\n");
    getchar();
    printf("press enter to continue...\n");
    getchar();
    system("cls");
}

void remove_employee(struct employee e[], int count)
{
    system("cls");
    printf("------------------------------------------------\n");
    printf("Enter the ID of employee to be removed: ");
    char empid[7];
    int identifier;
    int flag = 0;
    scanf(" %[^\n]", empid);
    printf("------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        if (strcmp(empid, e[i].eid) == 0)
        {
            identifier = i;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("Invalid ID\n");
        printf("press enter to continue...\n");
        getchar();
        system("cls");
        return;
    }
    for (int i = identifier; i < count; i++)
    {
        strcpy(e[i].eid, e[i + 1].eid);
        strcpy(e[i].name, e[i + 1].name);
        e[i].age = e[i + 1].age;
        e[i].type = e[i + 1].type;
        strcpy(e[i].contact_info, e[i + 1].contact_info);
        e[i].designation = e[i + 1].designation;
        e[i].ctc = e[i + 1].ctc;
    }
    getchar();
    printf("\npress enter to continue...\n");
    getchar();
    system("cls");
}

int sign_in(struct employee e[], int count)
{
    char s_id[7];
    char s_pass[20];
    printf("------------------------------------\n");
    printf("============== Sign In =============\n");
    printf("------------------------------------\n");
    printf("Enter employee ID: ");
    scanf(" %[^\n]", s_id);
    printf("\nEnter employee password: ");
    scanf(" %[^\n]", s_pass);
    int flag = 0;
    int identifier = -1;
    for (int i = 0; i < count; i++)
    {
        if ((strcmp(s_id, e[i].eid) == 0) && (strcmp(s_pass, e[i].password) == 0))
        {
            identifier = i;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("Invalid credentials\n");
        getchar();
        printf("press enter to continue...\n");
        getchar();
        system("cls");
        return -1;
    }
    getchar();
    printf("\npress enter to continue...\n");
    getchar();
    system("cls");
    return identifier;
}

void leave_approval(struct employee e[], int count)
{
    system("cls");
    int flag = 0, identifier11 = 0;
    printf("---------------------------------------\n");
    printf("| Employee ID | Days | Previous leave |\n");
    while(1)
    {
        for (int i = identifier11; i < count; i++)
        {
            if (e[i].leave_applied == true)
            {
                identifier11 = i;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("---------------------------------------\n");
            printf("No pending leave application!\n");
            getchar();
            printf("press enter to continue...\n");
            getchar();
            system("cls");
            return;
        }
        printf("| %11s | %4d | %14d |\n", e[identifier11].eid, e[identifier11].nos, e[identifier11].prev_leave);
        printf("---------------------------------------\n");
        printf("\napprove leave?\n1: yes\n2: no\n\nSelect: ");
        int apr;
        scanf("%d", &apr);
        if (apr == 1)
        {
            e[identifier11].approval_leave = true;
            e[identifier11].leave_applied = false;
            e[identifier11].prev_leave += e[identifier11].nos;
        }
        else if (apr == 2)
        {
            e[identifier11].approval_leave = false;
            e[identifier11].leave_applied = false;
        }
        if (identifier11 == count - 1)
        {
            return;
        }
    }
    getchar();
    printf("press enter to continue...\n");
    getchar();
    system("cls");
}

void view_info(struct employee e[], int identifier)
{
    system("cls");
    printf("------------------------------------\n");
    printf("========== Employee Data ===========\n");
    printf("------------------------------------\n\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("| Employee ID |   Employee Name   | Age | Gender | Contact Info  |      Designation      |    Annual Salary    |\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("| %-11s | %-17s | %-3d | %-6s | %-13s | %-21s | $%-18.2f |\n", e[identifier].eid, e[identifier].name, e[identifier].age, enumToString_(e[identifier].type), e[identifier].contact_info, enumToString(e[identifier].designation), e[identifier].ctc);
    printf("----------------------------------------------------------------------------------------------------------------\n\n");
    printf("------------------------------------\n");
    printf("========= Salary Break-down ========\n");
    printf("------------------------------------\n\n");
    printf("Basic salary: %.2f\n", e[identifier].base_salary);
    printf("HRA: %.2f\n", e[identifier].HRA);
    printf("Bonus: %.2f\n", e[identifier].bonus);
    printf("Income tax: %.2f\n", e[identifier].income_tax);
    getchar();
    printf("\npress enter to continue...\n");
    getchar();
    system("cls");
}

void update_contact_info(struct employee e[], int identifier)
{
    char e_cont[20];
    system("cls");
    printf("Enter new contact information: ");
    scanf(" %[^\n]", e_cont);
    strcpy(e[identifier].contact_info, e_cont);
    getchar();
    printf("press enter to continue...\n");
    getchar();
    system("cls");
}

void change_password(struct employee e[], int identifier)
{
    char e_pass[20];
    system("cls");
    printf("Enter new password: ");
    scanf(" %[^\n]", e_pass);
    strcpy(e[identifier].password, e_pass);
    getchar();
    printf("press enter to continue...\n");
    getchar();
    system("cls");
}

void leave_apply(struct employee e[], int identifier)
{
    system("cls");
    printf("Are you sure you want to apply for leave?\n1: yes\n2: no\n\nSelect: ");
    int opt5;
    scanf("%d", &opt5);
    if (opt5 == 2)
    {
        system("cls");
        return;
    }
    e[identifier].leave_applied = true;
    printf("Specify the number of days: ");
    scanf("%d", &e[identifier].nos);
    getchar();
    printf("press enter to continue...\n");
    getchar();
    system("cls");
}

void check_status(struct employee e[], int identifier)
{
    system("cls");
    if (e[identifier].leave_applied == true)
    {
        printf("Status: Pending\n");
        getchar();
        printf("press enter to continue...\n");
        getchar();
        system("cls");
        return;
    }
    if (e[identifier].leave_applied == false && e[identifier].approval_leave == false)
    {
        printf("Status: Rejected\n");
        getchar();
        printf("press enter to continue...\n");
        getchar();
        system("cls");
        return;
    }
    if (e[identifier].leave_applied == false && e[identifier].approval_leave == true)
    {
        printf("Status: Accepted\n");
        getchar();
        printf("press enter to continue...\n");
        getchar();
        system("cls");
        return;
    }
}

void resign(struct employee e[], int identifier, int count)
{
    system("cls");
    printf("are you sure you want to resign?\n1: yes     2: no\nselect: ");
    int opt6;
    scanf("%d", &opt6);
    for (int i = identifier; i < count; i++)
    {
        strcpy(e[i].eid, e[i + 1].eid);
        strcpy(e[i].name, e[i + 1].name);
        e[i].age = e[i + 1].age;
        e[i].type = e[i + 1].type;
        strcpy(e[i].contact_info, e[i + 1].contact_info);
        e[i].designation = e[i + 1].designation;
        e[i].ctc = e[i + 1].ctc;
    }
    getchar();
    printf("press enter to continue...\n");
    getchar();
    system("cls");
}

int main()
{
    srand(time(NULL));
    struct employee e[MAX];
    char username_admin[] = "admin_123";
    char password_admin[] = "admin_123";
    int count = 0;
    while(1)
    {
main_menu:
        printf("------------------------------------\n");
        printf("==== Employee management system ====\n");
        printf("------------------------------------\n");
        printf("   [1] Sign in as administrator\n");
        printf("   [2] Sign in as staff\n");
        printf("   [0] Exit\n");
        printf("------------------------------------\n");
        int opt;
        printf("\nSelect an option: ");
        scanf("%d", &opt);
        if (opt != 0 && opt != 1 && opt != 2)
        {
            printf("\nInvalid option. Please try again!\n");
            sleep(3);
            continue;
        }
        system("cls");
        switch(opt)
        {
        case 0:
            exit(0);
        case 1:
        {
            char user_name[20];
            char user_pass[20];
            printf("------------------------------------\n");
            printf("========== Admin sign in ===========\n");
            printf("------------------------------------\n");
            printf("\nEnter username: ");
            scanf(" %[^\n]", user_name);
            printf("\nEnter password: ");
            scanf(" %[^\n]", user_pass);
            getchar();
            printf("\npress enter to continue...\n");
            getchar();
            if (!((strcmp(username_admin, user_name) == 0) && (strcmp(password_admin, user_pass) == 0)))
            {
                printf("Invalid credentials\n");
                printf("press enter to continue...\n");
                getchar();
                system("cls");
                break;
            }
            system("cls");
            while(1)
            {
                printf("------------------------------------\n");
                printf("======== Administrator menu ========\n");
                printf("------------------------------------\n");
                printf("     [1] Add a new employee\n");
                printf("     [2] Grant promotion\n");
                printf("     [3] Update salary\n");
                printf("     [4] Get employee data\n");
                printf("     [5] Leave approval\n");
                printf("     [6] Remove an employee\n");
                printf("     [7] Change password\n");
                printf("     [8] Log out\n");
                printf("     [0] Exit\n");
                printf("------------------------------------\n");
                int opt2;
                printf("\nSelect an option: ");
                scanf("%d", &opt2);
                switch(opt2)
                {
                case 0:
                    exit(0);
                case 1:
                    system("cls");
                    while(count < MAX)
                    {
                        add_new(e, count);
                        count++;
                        break;
                    }
                    break;
                case 2:
                    grant_promo(e, count);
                    break;
                case 3:
                    update_salary(e, count);
                    break;
                case 4:
                    get_data(e, count);
                    break;
                case 5:
                    leave_approval(e, count);
                    break;
                case 6:
                    remove_employee(e, count);
                    count--;
                    break;
                case 7:
                {
                    char new_password[20];
                    system("cls");
                    printf("Enter new password: ");
                    scanf(" %[^\n]", new_password);
                    strcpy(password_admin, new_password);
                    getchar();
                    printf("\npress enter to continue...\n");
                    getchar();
                    system("cls");
                    break;
                }
                case 8:
                    system("cls");
                    goto main_menu;
                    break;
                }
            }
        }
        case 2:
        {
            int identifier = sign_in(e, count);
            if (identifier == -1)
            {
                break;
            }
            int opt4;
            while(1)
            {
                printf("------------------------------------\n");
                printf("=========== Employee menu ==========\n");
                printf("------------------------------------\n");
                printf("     [1] View details\n");
                printf("     [2] Update contact information\n");
                printf("     [3] Change password\n");
                printf("     [4] Apply for leave\n");
                printf("     [5] Check leave status\n");
                printf("     [6] resign\n");
                printf("     [7] log out\n");
                printf("     [0] Exit\n\n");
                printf("------------------------------------\n");
                printf("Select an option: ");
                scanf("%d", &opt4);
                if (opt4 < 0 || opt4 > 7)
                {
                    printf("Invalid option\n");
                    printf("press enter to continue...\n");
                    getchar();
                    system("cls");
                    continue;
                }
                switch(opt4)
                {
                case 0:
                    exit(0);
                case 1:
                    view_info(e, identifier);
                    break;
                case 2:
                    update_contact_info(e, identifier);
                    break;
                case 3:
                    change_password(e, identifier);
                    break;
                case 4:
                    leave_apply(e, identifier);
                    break;
                case 5:
                    check_status(e, identifier);
                    break;
                case 6:
                    resign(e, identifier, count);
                    count--;
                    goto main_menu;
                    break;
                case 7:
                    system("cls");
                    goto main_menu;
                    break;
                }
            }
        }
        }
    }
    return 0;
}
