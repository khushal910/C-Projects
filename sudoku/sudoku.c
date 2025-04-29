#include <stdio.h>
#include <time.h>

int sudoku[9][9];

void print_sudoku(int sudoku[9][9]);
int valid_value(int sudoku[9][9], int row, int col, int value);
int solve_sudoku(int sudoku[9][9], int row, int col);

int valid_value(int sudoku[9][9], int row, int col, int value)
{

    for (int j = 0; j < 9; j++) // check row
    {
        if (sudoku[row][j] == value)
        {
            return 0;
        }
    }

    for (int i = 0; i < 9; i++) // check col
    {
        if (sudoku[i][col] == value)
        {
            return 0;
        }
    }

    // valid square
    int r = row - row % 3;
    int c = col - col % 3;

    for (int i = r; i <= r + 2; i++) // check block
    {
        for (int j = c; j <= c + 2; j++)
        {
            if (sudoku[i][j] == value)
            {
                return 0;
            }
        }
    }

    return 1;
}

int solve_sudoku(int sudoku[9][9], int row, int col)
{
    if (col == 9)
    {
        if (row == 8)
        {
            return 1; // sudoku solved
        }
        col = 0;
        row++;
    }

    if (sudoku[row][col] > 0)
    {
        return solve_sudoku(sudoku, row, col + 1);
    }

    for (int i = 1; i <= 9; i++)
    {
        if (valid_value(sudoku, row, col, i))
        {
            sudoku[row][col] = i;
            if (solve_sudoku(sudoku, row, col + 1))
            {
                return 1;
            }
            sudoku[row][col] = 0;
        }
    }
    return 0;
}

void print_sudoku(int sudoku[9][9])
{
    printf("\n +--------+--------+--------+\n");
    for (int row = 0; row < 9; row++)
    {   
        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0)
                printf(" | ");

            if (sudoku[row][col] != 0)
                printf(" %d", sudoku[row][col]);
            else
                printf("  ");
        }
        printf(" |\n");
        if (row == 2 || row == 5)
            printf(" |--------+--------+--------|\n");
    }
    printf(" +--------+--------+--------+\n");
}

int main()
{

    printf("\nPleas enter zero(0) for empty space\n");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("\nEnter value of %d row and %d column: ",i+1,j+1);
            scanf("%d",&sudoku[i][j]);
        }
        
    }
    
    clock_t t;
    t = clock();

    printf("\nThe orignal sudoku\n");
    print_sudoku(sudoku);

    printf("\nThe solved sudoku\n");
    if (solve_sudoku(sudoku, 0, 0)){
        print_sudoku(sudoku);
    }
    else
        printf("\nSudoku not solvable");

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Sudoku Solve in %f sec\n\n", time_taken);

    return 0;
}
