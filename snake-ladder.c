#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define RED     "\033[41m"
#define GREEN   "\033[42m"
#define BLUE    "\033[44m"
#define YELLOW  "\033[43m"
#define CYAN    "\033[46m"
#define MAGENTA "\033[45m"
#define WHITE   "\033[47m"
#define RESET_COLOR "\033[0m"

#define text_RED "\033[1;31m"
#define text_GREEN "\033[1;32m"
#define text_YELLOW "\033[1;33m"
#define text_BLUE "\033[1;34m"
#define text_MAGENTA "\033[1;35m"
#define text_CYAN "\033[1;36m"
#define text_BLACK "\033[0;30m"
#define text_RESET_COLOR "\033[0m"

struct snake
{
    int start;
    int end;
};

struct ladder
{

    int start;
    int end;
};

void print_board(struct snake s[], struct ladder l[], int position_p1, int position_p2)
{
    printf("=================================================================================\n");
    printf("=============================== Snake & Ladder ==================================\n");
    printf("=================================================================================\n\n");

    printf("---------------------------------------------------------------------------------\n");

    for (int i = 9; i >= 0; i--)
    {
        if (i%2 == 0)
        {
            for (int j = 1; j <= 10; j++)
            {
                int position = i*10 + j;
                printf("%s", RESET_COLOR);
                printf("|");
                if (position_p1 == position && position_p2 == position)
                {
                    printf("%s", YELLOW);
                }
                else if (position_p1 == position)
                {
                    printf("%s", RED);
                }
                else if (position_p2 == position)
                {
                    printf("%s", GREEN);
                }
                if (position == 1)
                {
                    printf(" start ");
                    continue;
                }
                else if (position == 100)
                {
                    printf("  end  ");
                    continue;
                }
                int flag = 0;
                for (int i = 0; i < 10; i++)
                {
                    if (position == s[i].start)
                    {
                        printf("%s%s", text_BLACK, WHITE);
                        printf("   S   ");
                        printf("%s%s", text_RESET_COLOR, RESET_COLOR);
                        flag = 1;
                        break;
                    }
                    else if (position == l[i].start)
                    {
                        printf("%s%s", text_BLACK, WHITE);
                        printf("   L   ");
                        printf("%s%s", text_RESET_COLOR, RESET_COLOR);
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1)
                {
                    continue;
                }
                printf(" %4d  ", position);
            }
        }
        if (i%2 != 0)
        {
            for (int j = 10; j >= 1; j--)
            {
                int position = i*10 + j;
                printf("%s", RESET_COLOR);
                printf("|");
                if (position_p1 == position && position_p2 == position)
                {
                    printf("%s", YELLOW);
                }
                else if (position_p1 == position)
                {
                    printf("%s", RED);
                }
                else if (position_p2 == position)
                {
                    printf("%s", GREEN);
                }
                if (position == 1)
                {
                    printf(" start ");
                    continue;
                }
                else if (position == 100)
                {
                    printf("  end  ");
                    continue;
                }
                int flag = 0;
                for (int i = 0; i < 10; i++)
                {
                    if (position == s[i].start)
                    {
                        printf("%s%s", text_BLACK, WHITE);
                        printf("   S   ");
                        printf("%s%s", text_RESET_COLOR, RESET_COLOR);
                        flag = 1;
                        break;
                    }
                    else if (position == l[i].start)
                    {
                        printf("%s%s", text_BLACK, WHITE);
                        printf("   L   ");
                        printf("%s%s", text_RESET_COLOR, RESET_COLOR);
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1)
                {
                    continue;
                }
                printf(" %4d  ", position);
            }
        }
        printf("%s", RESET_COLOR);
        printf("|\n");
        printf("---------------------------------------------------------------------------------\n");
    }
}

void move_check(struct snake s[], struct ladder l[], int *position, int dice_roll)
{
    int new_position = *position + dice_roll;
    for (int i = 0; i < 10; i++)
    {
        if (new_position == s[i].start)
        {
            printf("Oops! You got bitten by a snake!\n");
            sleep(2);
            *position = s[i].end;
            return;
        }
        if (new_position == l[i].start)
        {
            printf("Congrats! You climbed a ladder!\n");
            sleep(2);
            *position = l[i].end;
            return;
        }
    }
    *position = new_position;
    return;
}
bool check_win(int position, int player)
{
    if (position == 100)
    {
        printf("player-%d won!\n", player);
        sleep(3);
        printf("\npress enter to play again...\n");
        getchar();
        system("cls");
        return true;
    }
    return false;
}

bool move_validity(int *position, int dice_roll)
{
    int new_position = *position + dice_roll;
    if (new_position > 100)
    {
        printf("Invalid move!\n");
        sleep(2);
        printf("\npress enter to continue or 0 to exit...\n");
        return false;
    }
    return true;
}


int main()
{
    srand(time(NULL));
    struct snake s[10] = {{27, 7}, {35, 5}, {39, 3},{50, 34}, {59, 46}, {66, 24}, {76, 63}, {89, 67}, {97, 86}, {99, 26}};
    struct ladder l[10] = {{2, 23}, {7, 29}, {22, 41}, {28, 77}, {30, 32}, {44, 58}, {54, 69}, {70, 90}, {80, 83}, {87, 93}};
    int position_p1;
    int position_p2;
main_menu:
    position_p1 = 1;
    position_p2 = 1;
    int current_player = 1;
    while(1)
    {
        print_board(s, l, position_p1, position_p2);
        printf("\nplayer-1 (RED): %d\n", position_p1);
        printf("player-2 (GREEN): %d\n", position_p2);
        int dice_roll = rand()%6+1;
        printf("\npress enter to roll a dice...\n");
        getchar();
        system("cls");
        printf("Player-%d rolled a dice and got %d!\n", current_player, dice_roll);
        if (current_player == 1)
        {
            if(!move_validity(&position_p1, dice_roll))
            {
                current_player = 2;
                continue;
            }
            move_check(s, l, &position_p1, dice_roll);
            if(check_win(position_p1, current_player))
            {
                if (getchar() == '0')
                {
                    system("cls");
                    break;
                }
                system("cls");
                goto main_menu;
            }
        }
        else
        {
            if(!move_validity(&position_p2, dice_roll))
            {
                current_player = 1;
                continue;
            }
            move_check(s, l, &position_p2, dice_roll);
            if(check_win(position_p2, current_player))
            {
                if (getchar() == '0')
                {
                    system("cls");
                    break;
                }
                system("cls");
                goto main_menu;
            }

        }
        if (dice_roll == 6)
        {
            printf("Congrats! You get another turn!\n");
            printf("press enter to continue...\n");
            getchar();
            system("cls");
            continue;
        }
        current_player = (current_player == 1)?2:1;
        printf("press enter to continue...\n");
        getchar();
        system("cls");
    }
    return 0;
}
