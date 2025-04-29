#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX_USER 10

typedef struct
{
  char name[100];
  char password[100];
} detail;

detail ruser[MAX_USER];
int number_of_user = 0;

void hide_password(char * password)
{
  char ch;
  int j = 0;
  while ((ch = getch()) != '\r') // Read until Enter key is pressed
  {
    if (ch == '\b' && j > 0) // Handle backspace
    {
      printf("\b \b"); // Erase the asterisk
      j--;
    }
    else if (ch != '\b') // Handle regular input
    {
      printf("*");
      password[j] = ch; // Store character in password array
      j++;
    }
  }
  password[j] = '\0'; // Null-terminate the password
}

void fix_newline(char *string)
{
  int posi = strcspn(string, "\n");
  string[posi] = '\0';
}

void register_user()
{
  if (number_of_user >= MAX_USER)
  {
    printf("Mximum %d user are supported! No more registration allowd!!!\n",MAX_USER);
    return;
  }
  printf("\nRegister a new user\nEnter username: ");
  fgets(ruser[number_of_user].name, sizeof(ruser[number_of_user].name), stdin);

  fix_newline(ruser[number_of_user].name);
  

  printf("Enter password(masking enabled): ");
  hide_password(ruser[number_of_user].password);

  printf("\nRegistration successful!\n");
  number_of_user++;
}

void login_user()
{
  detail luser;
  printf("\nEnter username: ");
  fgets(luser.name, sizeof(luser.name), stdin);

  fix_newline(luser.name);

  printf("Enter password(masking enabled): ");
  hide_password(luser.password);

  int found = 0;
  for (int j = 0; j < number_of_user; j++)
  {
    if (strcmp(ruser[j].name, luser.name) == 0 && strcmp(ruser[j].password, luser.password) == 0)
    {
      found = 1;
      break;
    }
  }
  if (found == 1)
    printf("\nLogin Successful! Welcome, %s.\n", luser.name);
  else
    printf("\nLogin Failed! Username or Password Incorrect.\n");
}

int main()
{
  int choice;

  while (1)
  {
    printf("\n1. Register\n2. Login\n3. Exit\n");
    printf("Select an option: ");
    scanf("%d", &choice);

    getchar(); // Consume the newline character left by scanf

    switch (choice)
    {
    case 1:
      register_user();
      break;
    case 2:
      login_user();
      break;
    case 3:
      return 0;
      break;
    default:
      printf("\nEnter a valid choice.\n");
    }
  }

  return 0;
}
