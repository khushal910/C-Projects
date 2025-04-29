#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    int random_number, guess_number, Attempt = 0;
    char name[50];

    printf("\n\t\"Welcome to the world of Guessing Numbers\" \n");

    printf("\nEnter your name: ");
    scanf("%s", name);

    srand(time(NULL)); // Initialize the random number generator with the current time

    random_number = rand() % 100 + 1; // Generating number between 1 to 100
    // printf("%d", random_number); // Uncomment for debugging only

    do
    {
        printf("\nPlease enter your guessing number (1 to 100): ");
        scanf("%d", &guess_number);
        Attempt++;

        if (guess_number < random_number)
        {
            printf("Hint:");
            printf(" Guess a larger number\n");
        }
        else if (guess_number > random_number)
        {
            printf("Hint:");
            printf(" Guess a smaller number\n");
        }
        else
        {
            printf("Congratulations, %s!\nYou have successfully guessed the number in %d Attempts.\n", name, Attempt);
        }
    }
    while (guess_number != random_number);

    printf("\nBye Bye, Thanks for playing!");
    printf("\nDeveloped by: Khushal");

    return 0;
}
