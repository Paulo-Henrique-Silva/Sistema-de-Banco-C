//this was made by: Paulo
//Github: Paulo-Henrique-Silva

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

FILE *pAccounts;
const char ACCOUNTS_FPATH[] = "Accounts.txt";

struct accountsInfo 
{
    char name[40], id[9], password[25], phone[15], birthday[11]; 
    long int money;
};

enum menu {Transfer = 1, Add, Update, Delete, Show, Details, ExitProgram};

int menu();

void transferMoney();
void addAccount();
void updateAccount();
void deleteAccount();
void showAccounts();
void showDetails();

int checkFiles();
//menu options

int main()
{
    int op;

    do
    {
        switch((op = menu())) //reads user input
        {
            case Transfer:
                transferMoney();
                break;
            case Add:
                addAccount();
                break;
            case Update:
                updateAccount();
                break;
            case Delete:
                deleteAccount();
                break;
            case Show:
                showAccounts();
                break;
            case Details:
                showDetails();
                break;
            case ExitProgram:
                printf("\nExiting...");
                break;
            default:
                printf("\nInvalid Input!");
                break;
        }

        getch(); //stops before closes it

    } while(op != ExitProgram);

    return 0;
}

//shows and returns user operation
int menu()
{
    int operation = 0;
    char input[1024];

    system("cls"); //clean screen

    printf("\t\t\tBank Management System");
    printf("\n\n\t\t\t[1] - Transfer Money");
    printf("\n\t\t\t[2] - Add an Account");
    printf("\n\t\t\t[3] - Update an Account");
    printf("\n\t\t\t[4] - Delete an Account");
    printf("\n\t\t\t[5] - Show Existing Accounts");
    printf("\n\t\t\t[6] - Show Details of An existing Accounts");
    printf("\n\t\t\t[7] - Exit");
    printf("\n\nType your operation: ");
    fgets(input, 1024, stdin);

    //if it fails to read the input
    if(input == NULL) 
        return 0; 

    //converts to a short
    operation = atoi(input); 

    //if it fails to convert
    if(operation == 0) 
        return 0;
    else
        return operation; 
}

void transferMoney()
{

    system("cls");

}

void addAccount()
{
    //how it is creating an account, there is no need to stop the program
    checkFiles(); 

    system("cls");
}

void updateAccount()
{
    system("cls");

}

void deleteAccount()
{

    system("cls");


}

void showAccounts()
{

    system("cls");

}

void showDetails()
{

    system("cls");

}

/*
Checks if files exist
- If it returns 0 is means that they're empty or were deleted.
- Else, it'll return 1.
*/
int checkFiles()
{
    char firstLine[1024];
    pAccounts = fopen(ACCOUNTS_FPATH, "r");
   
    //if it was deleted
    if(pAccounts == NULL) 
    {
        fclose(pAccounts);

        pAccounts = fopen(ACCOUNTS_FPATH, "w");
        fclose(pAccounts);

        return 0;
    }
    else if(fgets(firstLine, 1024, pAccounts) == NULL) //if it's empty
    {
        fclose(pAccounts);
        return 0;
    }
    else 
    {
        fclose(pAccounts);
        return 1;
    }
}
