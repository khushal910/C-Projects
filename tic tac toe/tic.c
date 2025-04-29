#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void clear_screen(void);
void print();
void human_mode();
void initialize_board();

char tic[3][3];
int x_score = 0, c_score = 0, Draw = 0;

void initialize_board()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tic[i][j] = ' ';
}

void clear_screen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void score_board()
{
    printf("\nScore -Player X: %d, Computer: %d , Draw: %d\n", x_score, c_score, Draw);

    
}
void print()
{
    //  printf("\nScore -Player X: 0, Computer: 0 , Draw: 0\n");
    score_board();
    printf("Tic Tac Toe\n\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("  %c", tic[i][j]);
            if (j != 2)
                printf(" |");
        }
        if (i == 0 || i == 1)
            printf("\n---+---+---\n");
    }
}

void human_value()
{

    int r, c;
    while (1)
    {
        printf("\n\nPlayer X's Turn.");
        printf("\nEnter row and column(1 - 3) for X: ");
        scanf("%d %d", &r, &c);

        char ch = '0';

        if (tic[r - 1][c - 1] != ch)
        {
            tic[r - 1][c - 1] = 'X';
            break;
        }
    }

    clear_screen();
    print();
}

void computer_value()
{

    while (1)
    {
        int i = rand() % 3;
        int j = rand() % 3;
        char ch = 'X';
        if (tic[i][j] != ch)
        {
            tic[i][j] = '0';
            break;
        }
    }
}

void human_mode()
{
    computer_value();

    print();

    human_value();
}

int main()
{
    int choice;
    printf("\n\nSelect difficulty level:\n");
    printf("1 - Human(Standere)\n2 - God (Impossible to win)\nChoice: ");
    scanf("%d", &choice);

    void initialize_board();
    srand(time(NULL));

    while (1)
    {

        clear_screen();

        switch (choice)
        {
        case 1:
            human_mode();
            break;
        case 2:
            break;
        default:
            printf("\nEnter valid choice");
        }
    }
    return 0;
}