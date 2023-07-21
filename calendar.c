#include <stdio.h>
#include <stdlib.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET_COLOR "\033[0m"


int isValidDate(int year, int month, int day)
{
    if (year < 1 || month < 1 || month > 12 || day < 1)
        return 0;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;

    return day <= daysInMonth[month - 1];
}

int getDayOfWeek(int year, int month, int day)
{
    if (month < 3)
    {
        month += 12;
        year--;
    }
    int k = year % 100;
    int j = year / 100;
    int h = (day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    return (h + 5) % 7;
}

void printCalendar(int year, int month, int day)
{
    system("cls");
    const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;

    int dayOfWeek = getDayOfWeek(year, month, 1);

    printf("\n============================\n");
    printf("%s%15s %d%s\n", YELLOW, months[month - 1], year, RESET_COLOR);
    printf("============================\n");
    printf("%sSun Mon Tue Wed Thu Fri Sat%s\n", RED, RESET_COLOR);

    for (int i = 0; i < dayOfWeek; i++)
        printf("    ");

    int currentDay = 1;
    while (currentDay <= daysInMonth[month - 1])
    {
        if ((dayOfWeek + currentDay) % 7 == 1)
        {
            printf("%s", RED);
        }
        if (currentDay == day){
            printf("%s", BLUE);
        }
        printf("%3d ", currentDay);
        printf("%s", RESET_COLOR);

        if ((dayOfWeek + currentDay) % 7 == 0)
            printf("\n");

        currentDay++;
    }
    printf("\n============================\n");
    getchar();
    printf("press enter to continue...\n");
    getchar();
    system("cls");
}

int main()
{
    int year, month, day;
    while (1)
    {
        system("cls");
        printf("----------------------------\n");
        printf("========= Calendar =========\n");
        printf("----------------------------\n\n");
        printf("Select Year: ");
        if (scanf("%d", &year) != 1)
        {
            printf("\nInvalid input for year!\n");
            getchar();
            continue;
        }

        printf("Select Month (1-12): ");
        if (scanf("%d", &month) != 1)
        {
            printf("\nInvalid input for month!\n");
            getchar();
            continue;
        }

        printf("Select Day (1-31): ");
        if (scanf("%d", &day) != 1)
        {
            printf("\nInvalid input for day!\n");
            getchar();
            continue;
        }

        if (!isValidDate(year, month, day))
        {
            printf("\nInvalid date!\n");
            getchar();
            continue;
        }
        printCalendar(year, month, day);
        while(1)
        {
            system("cls");
            printf("\n[0] exit\n");
            printf("[1] navigate (month)\n");
            printf("[2] navigate (year)\n");
            printf("[3] navigate (day)\nselect: ");
            int option;
            scanf("%d", &option);
            switch (option)
            {
            case 0:
                break;
            case 1:
                printf("< or > : ");
                getchar();
                if (getchar() == '<')
                {
                    printCalendar(year, month - 1,day);
                    month--;
                }
                else
                {
                    printCalendar(year, month + 1, day);
                    month++;
                }
                break;
            case 2:
                printf("< or > : ");
                getchar();
                if (getchar() == '<')
                {
                    printCalendar(year - 1, month, day);
                    year--;
                }
                else
                {
                    printCalendar(year + 1, month, day);
                    year++;
                }
                break;
            case 3:
                printf("< or > : ");
                getchar();
                if (getchar() == '<')
                {
                    printCalendar(year, month, day-1);
                    day--;
                }
                else
                {
                    printCalendar(year, month, day+1);
                    day++;
                }
                break;
            }
            if (option == 0){
                break;
            }
        }
    }
    return 0;
}
