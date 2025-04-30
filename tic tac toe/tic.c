#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define BOARED_SIZE 3
#define X 'X'
#define O 'O'
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
    printf("\nScore - Player X: %d, Computer: %d, Draws: %d ", score.player, score.computer, score.draw);
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

int is_valid_move(char board[BOARED_SIZE][BOARED_SIZE], int row, int col)
{
    return (row < 0 || col < 0 || row > 2 || col > 2 || board[row][col] != ' ');
}

void human_move(char board[BOARED_SIZE][BOARED_SIZE])
{
    // if only one place is left
    int count = 0, i = 0, j = 0;
    for (i = 0; i < BOARED_SIZE; i++)
    {
        for (j = 0; j < BOARED_SIZE; j++)
        {
            if (board[i][j] == ' ')
                count++;
        }
    }
    if (count == 1)
        board[i][j] = X;

    int row, col;
    do
    {
        printf("\n\nPlayer X's turn.\n");
        printf("Enter tow and column(1 - 3) for X: ");
        scanf("%d %d", &row, &col);
        row--;
        col--; // converting to zero base
    } while (is_valid_move(board, row, col));

    board[row][col] = X;
}

void computer_move(char board[BOARED_SIZE][BOARED_SIZE])
{
    // 1. play for immediate move
    for (int i = 0; i < BOARED_SIZE; i++)
    {
        for (int j = 0; j < BOARED_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                if (check_win(board, O))
                {
                    return;
                }
                else
                    board[i][j] = ' ';
            }
        }
    }

    // 2. play for immediate block
    for (int i = 0; i < BOARED_SIZE; i++)
    {
        for (int j = 0; j < BOARED_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = X;
                if (check_win(board, X))
                {
                    board[i][j] = O;
                    return;
                }
                else
                    board[i][j] = ' ';
            }
        }
    }
    // GOD mode
    if (difficulty == 2)
    {
        // 3. Play Center if available
        if (board[1][1] == ' ')
        {
            board[1][1] = O;
            return;
        }

        // 4. play Corner if available
        if (board[0][0] == ' ')
        {
            board[0][0] = O;
            return;
        }
        else if (board[0][2] == ' ')
        {
            board[0][2] = O;
            return;
        }
        else if (board[2][0] == ' ')
        {
            board[2][0] = O;
            return;
        }
        else if (board[2][2] == ' ')
        {
            board[2][2] = O;
            return;
        }
    }

    // 5. play first available move
    for (int i = 0; i < BOARED_SIZE; i++)
    {
        for (int j = 0; j < BOARED_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                return;
            }
        }
    }
}

void play_game()
{
    char board[BOARED_SIZE][BOARED_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    char current_player = rand() % 2 == 0 ? X : O;
    print_board(board);

    while (1)
    {

        if (current_player == X)
        {
            human_move(board);
            print_board(board);

            if (check_win(board, X))
            {
                score.player++;
                print_board(board);
                printf("\n\nCongratulation You have won!!!");
                break;
            }
            current_player = O;
        }
        else
        {
            computer_move(board);
            print_board(board);

            if (check_win(board, O))
            {
                score.computer++;
                print_board(board);
                printf("\n\nI won !!! Try again Buddy.");
                break;
            }
            current_player = X;
        }

        if (draw(board))
        {
            score.draw++;
            print_board(board);
            printf("\n\nIt's draw!");
            break;
        }
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
            printf("\nIncorect choice enter (1/2)");
        else
            break;
    }
}

int main()
{
    srand(time(NULL));
    int choice;

    do
    {
        input_difficulty();
        play_game();
        printf("\nPlay again? (1 for Yea, 0 for No): ");
        scanf("%d", &choice);

    } while (choice == 1);
    printf("\nBye Bye thanks for playing.");

    return 0;
}