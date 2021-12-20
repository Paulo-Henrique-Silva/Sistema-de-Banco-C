//this was made by: Paulo
//Github: Paulo-Henrique-Silva

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

FILE *pAccounts;

enum menu {Transfer = 1, Add, Update, Delete, Show, Details, ExitProgram};

int menu();

int transferMoney();
int addAccount();
int updateAccount();
int deleteAccount();
void showAccounts();
int showDetails();
//menu options

int main()
{
    int op;

    do
    {
        switch((op = menu())) //reads user input
        {
            case Transfer:
                //transferMoney();
                break;
            case Add:
                addAccount();
                break;
            case Update:
                //updateAccount();
                break;
            case Delete:
                //deleteAccount();
                break;
            case Show:
                //showAccounts();
                break;
            case Details:
                //showDetails();
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

    system("cls");
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

    if(input == NULL) //if it fails to read the input
        return 0; 

    operation = atoi(input); 
    //converts to a short

    if(operation == 0) //if it fails to convert
        return 0;
    else
        return operation; 
}

int transferMoney()
{

}

int addAccount()
{

}

int updateAccount()
{

}

int deleteAccount()
{

}

void showAccounts()
{

}

int showDetails()
{

}
