#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 100

struct voter_info
{
    char name[50];
    char password[20];
    int age;
    char voter_id[9];
    bool casted_vote;
};

struct candidate
{
    char name[50];
    char voter_id[9];
    int age;
    int candidate_id;
    int num_of_votes;
};

void cls_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void registration_voter(struct voter_info v[], int num_of_voters, int min_voter_age, int *voter_count)
{
    system("cls");
    printf("==== Voter Registration ====\n");

    if (*voter_count >= num_of_voters)
    {
        printf("Maximum number of voters reached!\n");
        sleep(3);
        return;
    }

    printf("Enter name: ");
    scanf(" %[^\n]", v[*voter_count].name);

    printf("Enter age (%d or above): ", min_voter_age);
    if (scanf("%d", &v[*voter_count].age) != 1)
    {
        cls_input_buffer();
        printf("Invalid input! Age must be a valid integer.\n");
        sleep(3);
        system("cls");
        return;
    }
    cls_input_buffer();

    if (v[*voter_count].age < min_voter_age)
    {
        printf("Not eligible!\n");
        sleep(3);
        system("cls");
        return;
    }

    while (true)
    {
        for (int i = 0; i < 8; i++)
        {
            v[*voter_count].voter_id[i] = rand() % 10 + '0';
        }
        v[*voter_count].voter_id[8] = '\0';

        bool id_exists = false;
        for (int i = 0; i < *voter_count; i++)
        {
            if (strcmp(v[i].voter_id, v[*voter_count].voter_id) == 0)
            {
                id_exists = true;
                break;
            }
        }

        if (!id_exists)
        {
            break;
        }
    }

    printf("Voter ID: %s\n", v[*voter_count].voter_id);

    while (true)
    {
        printf("Choose a password (6-20 characters): ");
        scanf(" %[^\n]", v[*voter_count].password);
        cls_input_buffer();

        if (strlen(v[*voter_count].password) < 6 || strlen(v[*voter_count].password) > 20)
        {
            printf("Invalid password length! Please enter a password between 6 and 20 characters.\n");
        }
        else
        {
            break;
        }
    }

    printf("Registration completed successfully.\n");
    sleep(2);
    system("cls");

    (*voter_count)++;
}

void registration_candidate(struct candidate c[], struct voter_info v[], int num_of_candidates, int min_candidate_age, int *candidate_count, int voter_count)
{
    system("cls");
    printf("==== Candidate Application ====\n");

    if (*candidate_count >= num_of_candidates)
    {
        printf("Maximum number of candidates reached!\n");
        sleep(3);
        system("cls");
        return;
    }

    char voter_id[9];
    char password[20];

    printf("Enter Voter ID: ");
    scanf(" %[^\n]", voter_id);
    cls_input_buffer();

    printf("Enter password: ");
    scanf(" %[^\n]", password);
    cls_input_buffer();

    int identifier = -1;
    for (int i = 0; i < voter_count; i++)
    {
        if ((strcmp(v[i].voter_id, voter_id) == 0) && strcmp(v[i].password, password) == 0)
        {
            identifier = i;
            break;
        }
    }

    if (identifier == -1)
    {
        printf("Authentication failed!\n");
        sleep(3);
        system("cls");
        return;
    }

    if (v[identifier].age < min_candidate_age)
    {
        printf("Not eligible!\n");
        sleep(3);
        system("cls");
        return;
    }

    strcpy(c[*candidate_count].name, v[identifier].name);
    strcpy(c[*candidate_count].voter_id, v[identifier].voter_id);
    c[*candidate_count].age = v[identifier].age;
    c[*candidate_count].candidate_id = *candidate_count + 1;
    c[*candidate_count].num_of_votes = 0;

    printf("Candidate application submitted successfully.\n");
    sleep(2);
    system("cls");

    (*candidate_count)++;
}

void cast_vote(struct voter_info v[], struct candidate c[], int num_of_candidates, int voter_count)
{
    system("cls");
    printf("==== Vote Casting ====\n");

    char voter_id[9];
    char password[20];

    printf("Voter ID: ");
    scanf(" %[^\n]", voter_id);
    cls_input_buffer();

    printf("Password: ");
    scanf(" %[^\n]", password);
    cls_input_buffer();

    int identifier = -1;
    for (int i = 0; i < voter_count; i++)
    {
        if ((strcmp(v[i].voter_id, voter_id) == 0) && (strcmp(v[i].password, password) == 0))
        {
            identifier = i;
            break;
        }
    }

    if (identifier == -1)
    {
        printf("Authentication failed!\n");
        sleep(3);
        system("cls");
        return;
    }

    if (v[identifier].casted_vote)
    {
        printf("You have already casted your vote.\n");
        sleep(3);
        system("cls");
        return;
    }

    printf("==== Cast Your Vote ====\n");
    printf("Candidate ID | Name\n");
    printf("----------------------\n");
    for (int i = 0; i < num_of_candidates; i++)
    {
        printf("%-13d| %s\n", c[i].candidate_id, c[i].name);
    }
    printf("----------------------\n");

    int vote;
    printf("Cast your vote (1-%d): ", num_of_candidates);
    if (scanf("%d", &vote) != 1)
    {
        cls_input_buffer();
        printf("Invalid input! Please enter a valid candidate ID.\n");
        sleep(3);
        system("cls");
        return;
    }
    cls_input_buffer();

    if (vote < 1 || vote > num_of_candidates)
    {
        printf("Invalid candidate ID! Please enter a valid candidate ID.\n");
        sleep(3);
        system("cls");
        return;
    }

    v[identifier].casted_vote = true;
    c[vote - 1].num_of_votes++;

    printf("Vote casted successfully.\n");
    sleep(2);
    system("cls");
}

void display_candidates(struct candidate c[], int candidate_count)
{
    system("cls");
    printf("==== Candidate Information ====\n");
    printf("Candidate ID | Name       | Age | Votes\n");
    printf("------------------------------------\n");
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%-13d| %-11s | %-3d | %-5d\n", c[i].candidate_id, c[i].name, c[i].age, c[i].num_of_votes);
    }
    printf("------------------------------------\n");
    printf("Press enter to continue...\n");
    cls_input_buffer();
    getchar();
    system("cls");
}

void display_voters(struct voter_info v[], int voter_count)
{
    system("cls");
    printf("==== Voter Information ====\n");
    printf("Voter ID    | Name       | Age | Casted Vote\n");
    printf("------------------------------------------\n");
    for (int i = 0; i < voter_count; i++)
    {
        printf("%-11s | %-11s | %-3d | %s\n", v[i].voter_id, v[i].name, v[i].age, (v[i].casted_vote ? "Yes" : "No"));
    }
    printf("------------------------------------------\n");
    printf("Press enter to continue...\n");
    cls_input_buffer();
    getchar();
    system("cls");
}

void display_result(struct candidate c[], int candidate_count, int min_vote_percentage)
{
    system("cls");
    printf("==== Election Result ====\n");
    printf("Candidate ID | Votes Received\n");
    printf("------------------------------------\n");
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%-13d| %d\n", c[i].candidate_id, c[i].num_of_votes);
    }
    printf("------------------------------------\n");

    int max_votes = c[0].num_of_votes;
    int winner_id = 0;
    bool no_winner = false;
    int total_votes = 0;

    for (int i = 1; i < candidate_count; i++)
    {
        if (c[i].num_of_votes > max_votes)
        {
            max_votes = c[i].num_of_votes;
            winner_id = i;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        total_votes += c[i].num_of_votes;
    }

    if (total_votes == 0 || (float)max_votes / total_votes * 100 < min_vote_percentage)
    {
        no_winner = true;
    }

    if (no_winner)
    {
        printf("No winner.\n");
    }
    else
    {
        float vote_percentage = (float)max_votes / total_votes * 100;
        printf("\n");
        printf("==== WINNER ====\n");
        printf("Name: %s\n", c[winner_id].name);
        printf("Voter ID: %s\n", c[winner_id].voter_id);
        printf("Age: %d\n", c[winner_id].age);
        printf("Candidate ID: %d\n", c[winner_id].candidate_id);
        printf("Vote Percentage: %.2f%%\n", vote_percentage);
    }

    printf("Press enter to continue...\n");
    cls_input_buffer();
    getchar();
    system("cls");
}

int main()
{
    srand(time(NULL));
    int num_of_voters, num_of_candidates, min_voter_age, min_candidate_age, min_vote_percentage;
    struct voter_info voters[MAX_VOTERS];
    struct candidate candidates[MAX_CANDIDATES];
    int voter_count = 0;
    int candidate_count = 0;

    while (1)
    {
        printf("\033[1;33m");
    printf("=====================================\n");
    printf("|         Voting System             |\n");
    printf("=====================================\n");
    printf("| 1. Conduct an Election            |\n");
    printf("| 2. Voter Registration             |\n");
    printf("| 3. Apply for Candidacy            |\n");
    printf("| 4. Cast Your Vote                 |\n");
    printf("| 5. View Candidate Information     |\n");
    printf("| 6. View Voter Information         |\n");
    printf("| 7. View Election Result           |\n");
    printf("| 0. Exit                           |\n");
    printf("=====================================\n");
    printf("\033[0m");

        int option;
        printf("Select an option: ");
        if (scanf("%d", &option) != 1)
        {
            cls_input_buffer();
            printf("Invalid input! Please enter a valid option.\n");
            sleep(2);
            system("cls");
            continue;
        }
        cls_input_buffer();
        system("cls");

        switch (option)
        {
        case 0:
            exit(0);
            break;
        case 1:
            printf("Enter the number of voters: ");
            if (scanf("%d", &num_of_voters) != 1)
            {
                cls_input_buffer();
                printf("Invalid input! Number of voters must be a valid integer.\n");
                sleep(3);
                system("cls");
                continue;
            }
            cls_input_buffer();

            printf("Enter the number of candidates: ");
            if (scanf("%d", &num_of_candidates) != 1)
            {
                cls_input_buffer();
                printf("Invalid input! Number of candidates must be a valid integer.\n");
                sleep(3);
                system("cls");
                continue;
            }
            cls_input_buffer();

            printf("Specify the minimum age for voters: ");
            if (scanf("%d", &min_voter_age) != 1)
            {
                cls_input_buffer();
                printf("Invalid input! Minimum voter age must be a valid integer.\n");
                sleep(3);
                system("cls");
                continue;
            }
            cls_input_buffer();

            printf("Specify the minimum age for candidates: ");
            if (scanf("%d", &min_candidate_age) != 1)
            {
                cls_input_buffer();
                printf("Invalid input! Minimum candidate age must be a valid integer.\n");
                sleep(3);
                system("cls");
                continue;
            }
            cls_input_buffer();

            printf("Specify the minimum percentage of votes to win the election: ");
            if (scanf("%d", &min_vote_percentage) != 1)
            {
                cls_input_buffer();
                printf("Invalid input! Minimum vote percentage must be a valid integer.\n");
                sleep(3);
                system("cls");
                continue;
            }
            cls_input_buffer();

            system("cls");
            break;
        case 2:
            registration_voter(voters, num_of_voters, min_voter_age, &voter_count);
            break;
        case 3:
            registration_candidate(candidates, voters, num_of_candidates, min_candidate_age, &candidate_count, voter_count);
            break;
        case 4:
            cast_vote(voters, candidates, num_of_candidates, voter_count);
            break;
        case 5:
            display_candidates(candidates, candidate_count);
            break;
        case 6:
            display_voters(voters, voter_count);
            break;
        case 7:
            display_result(candidates, candidate_count, min_vote_percentage);
            break;
        default:
            printf("Invalid option! Please select a valid option.\n");
            sleep(2);
            system("cls");
            break;
        }
    }
    return 0;
}
