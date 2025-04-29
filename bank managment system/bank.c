#include <stdio.h>
#include <string.h>
#include <conio.h>    

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();
void fix_newline(char *s);
void hide_password(char *pwd);

const char *ACCOUNT_FILE = "account.dat";

typedef struct {
    char name[50];
    char pin[50];
    int  acc_no;
    float balance;
} Account;

void fix_newline(char *s) {
    int posi=strcspn(s, "\n");
    s[posi] = '\0';
}

void hide_password(char *pwd) {
    int  j = 0;
    char ch;
    while ((ch = getch()) != '\r' && ch != '\n') {
        if (ch == '\b' && j > 0) {
            printf("\b \b");
            j--;
        } else if (ch >= 32 && ch <= 126) {
            printf("*");
            pwd[j++] = ch;
        }
    }
    pwd[j] = '\0';
    printf("\n");
}

void create_account() {
    FILE *f = fopen(ACCOUNT_FILE, "ab+");
    if (!f) { perror("Opening file"); return; }

    Account acc;
    printf("\nEnter your Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    fix_newline(acc.name);

    printf("Enter your Account Number: ");
    scanf("%d", &acc.acc_no);
    getchar();

    printf("Set your PIN: ");
    hide_password(acc.pin);

    acc.balance = 0.0f;
    fwrite(&acc, sizeof(acc), 1, f);
    fclose(f);

    printf("\nAccount created successfully!\n");
}

void deposit_money() {
    FILE *f = fopen(ACCOUNT_FILE, "rb+");
    if (!f) { perror("Opening file"); return; }

    int  acc_no;
    char pin[50];
    float amt;
    Account acc;

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    getchar();

    printf("Enter your PIN: ");
    hide_password(pin);

    while (fread(&acc, sizeof(acc), 1, f)) {
        if (acc.acc_no == acc_no && strcmp(acc.pin, pin) == 0) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amt);

            acc.balance += amt;
            fseek(f, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, f);
            fclose(f);

            printf("\nSuccessfully deposited Rs. %.2f\nNew balance: Rs. %.2f\n",
                   amt, acc.balance);
            return;
        }
    }

    printf("\nDeposit failed: account not found or PIN incorrect.\n");
    fclose(f);
}

void withdraw_money() {
    FILE *f = fopen(ACCOUNT_FILE, "rb+");
    if (!f) { perror("Opening file"); return; }

    int  acc_no;
    char pin[50];
    float amt;
    Account acc;

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    getchar();

    printf("Enter your PIN: ");
    hide_password(pin);

    while (fread(&acc, sizeof(acc), 1, f)) {
        if (acc.acc_no == acc_no && strcmp(acc.pin, pin) == 0) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amt);

            if (amt > acc.balance) {
                printf("\nInsufficient funds. Your balance is Rs. %.2f\n", acc.balance);
            } else {
                acc.balance -= amt;
                fseek(f, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, f);
                printf("\nSuccessfully withdrawn Rs. %.2f\nRemaining balance: Rs. %.2f\n",
                       amt, acc.balance);
            }

            fclose(f);
            return;
        }
    }

    printf("\nWithdrawal failed: account not found or PIN incorrect.\n");
    fclose(f);
}

void check_balance() {
    FILE *f = fopen(ACCOUNT_FILE, "rb");
    if (!f) { perror("Opening file"); return; }

    int acc_no;
    char pin[50];
    Account acc;

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    getchar();

    printf("Enter your PIN: ");
    hide_password(pin);

    while (fread(&acc, sizeof(acc), 1, f)) {
        if (acc.acc_no == acc_no && strcmp(acc.pin, pin) == 0) {
            printf("\nYour current balance is Rs. %.2f\n", acc.balance);
            fclose(f);
            return;
        }
    }

    printf("\nLookup failed: account not found or PIN incorrect.\n");
    fclose(f);
}

int main() {
    // If you ever change the structure, delete the old account.dat so it doesn't mis-align.
    while (1) {
        printf("\n*** Bank Management System ***\n"
               "1. Create Account\n"
               "2. Deposit Money\n"
               "3. Withdraw Money\n"
               "4. Check Balance\n"
               "5. Exit\n"
               "Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) break;
        getchar();

        switch (choice) {
            case 1: create_account();  break;
            case 2: deposit_money();   break;
            case 3: withdraw_money();  break;
            case 4: check_balance();   break;
            case 5: printf("\nGoodbye!\n"); return 0;
            default: printf("\nInvalid choice.\n");
        }
    }
    return 0;
}
