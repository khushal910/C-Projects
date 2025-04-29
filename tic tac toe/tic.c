#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define BOARED_SIZE 3
typedef struct
{
    int computer;
    int player;
    int draw;

} Score;

int difficulty;
Score score = {.computer = 0, .player = 0, .draw = 0};

void clear_screen(void)
{
#ifdef _WIN32
    system("cls");
#else
    syatem("clear");
#endif
}

int check_win(char board[BOARED_SIZE][BOARED_SIZE], char player)
{
    for (int i = 0; i < BOARED_SIZE; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
    }

    for (int j = 0; j < BOARED_SIZE; j++)
    {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return 1;
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return 1;

    return 0;
}

int draw(char board[BOARED_SIZE][BOARED_SIZE])
{
    for (int i = 0; i < BOARED_SIZE; i++)
    {
        for (int j = 0; j < BOARED_SIZE; j++)
        {
            if (board[i][j] == ' ')
                return 0;
        }
    }

    return 1;
}

void print_board(char board[BOARED_SIZE][BOARED_SIZE])
    {
        clear_screen();
        printf("\nScore - Player X: %d, Comuter: %d, Dra ws: %d ", score.player, score.computer, score.draw);
        printf("\nTic Tec Teo\n");

        for (int i = 0; i < BOARED_SIZE; i++)
        {
            printf("\n");
            for (int j = 0; j < BOARED_SIZE; j++)
            {
                printf(" %c", board[i][j]);
                if (j < BOARED_SIZE - 1)
                    printf(" |");
            }
            if (i < BOARED_SIZE - 1)
                printf("\n---+---+---");
        }
    }

    void input_difficulty()
    {
        while (1)
        {

            printf("\nSelect difficulty level:\n");
            printf("1 - Human(Standere)\n");
            printf("2 - God (Impossible to win)\n");
            printf("Enter your choice: ");
            scanf("%d", &difficulty);

            if (difficulty > 3)
                printf("\nInccorect choice enter (1/2)");
            else
                break;
        }
    }

    void play_game()
    {
        char board[BOARED_SIZE][BOARED_SIZE] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}};
        print_board(board);
        
    
    }


    int main()
    {
        int choice;
        input_difficulty();
        do{
            play_game();
            printf("\nPlay again? (1 for Yea, 0 fro No): ");
            scanf("%d",&choice);
        }
        while (choice==1);
        printf("\nBye Bye thanks for playing");

        return 0;
    }