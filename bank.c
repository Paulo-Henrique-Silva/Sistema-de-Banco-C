//this was made by: Paulo
//Github: Paulo-Henrique-Silva

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

FILE *pAccounts;
const char ACCOUNTS_FPATH[] = "Accounts.txt";

struct accountsInfo 
{
    char name[40], id[9], password[25], phone[15], birthday[11]; 
    long int money;
};

enum menu {Transfer = 1, Add, Update, Delete, Show, Details, ExitProgram};

int menu();

int transferMoney();
int addAccount();
int updateAccount();
int deleteAccount();
void showAccounts();
int showDetails();

int checkFiles();
int readsStr(char string[], char mode);
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
                if(addAccount())
                    printf("\nAccount Sucessfully Created!");
                else
                    printf("\nSorry, it's not possible to create the Account :/");
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

int transferMoney()
{

    system("cls");

}

int addAccount()
{
    struct accountsInfo newUser;
    char buffer[1024], *end;

    system("cls");

    printf("\nType your Name: ");
    if(readsStr(newUser.name, 'a') == 0)
    {
        printf("\nInvalid Input!");
        return 0;
    }

    printf("\nType your ID: ");
    if(readsStr(newUser.id, 'n') == 0)
    {
        printf("\nInvalid Input!");
        return 0;
    }

    printf("\nType a Phone Number: ");
    if(readsStr(newUser.phone, 'n') == 0)
    {
        printf("\nInvalid Input!");
        return 0;
    }
    
    printf("\nType your Birthday(dd/mm/yyyy): ");
    readsStr(newUser.birthday, 'c');

    printf("\nType a Password to your Account: ");
    readsStr(newUser.password, 'c');

    printf("\nType how much money You want in your account: R$");
    fgets(buffer, 1024, stdin);
    newUser.money = strtol(buffer, &end, 10);
    if(newUser.money <= 0)
    {
        printf("\nInvalid Input!");
        return 0; 
    }

    checkFiles(); //how it is adding an account there is no need to block the program

    pAccounts = fopen(ACCOUNTS_FPATH, "a");
    fprintf(pAccounts, "%s %s %s %s %s %ld\n", newUser.name, newUser.id, newUser.phone, newUser.birthday, newUser.password, newUser.money);
    fclose(pAccounts);
    return 1;
}

int updateAccount()
{

    system("cls");

}

int deleteAccount()
{
    FILE *pTemp;
    const char TEMP_FPATH[] = "tempFile.tmp";

    system("cls");
}

void showAccounts()
{

    system("cls");

}

int showDetails()
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

/*
Reads a string in a certain mode
- Returns 1, is it can reads correctly in that mode and assigns the input to the string
- Else, returns 0
Modes: 
 - 'c' - accepts all characters
 - 'a' - accepts alphabets 
 - 'n' - accepts numbers
*/
int readsStr(char string[], char mode)
{
    char buffer[1024];

    fgets(buffer, 1024, stdin);
    buffer[strlen(buffer) - 1] = '\0'; //removes \n in last char
    
    switch (mode)
    {
        case 'c':
            strcpy(string, buffer);
            return 1; 

        case 'a':
            for(int i = 0; i < strlen(buffer); i++)
            {
                if((buffer[i] < 'A' || buffer[i] > 'Z') && (buffer[i] < 'a' || buffer[i] > 'z')) 
                    return 0;
            }

            strcpy(string, buffer);
            return 1;

        case 'n':
            for(int i = 0; i < strlen(buffer); i++)
            {
                if(buffer[i] < '0' || buffer[i] > '9')
                    return 0;
            }

            strcpy(string, buffer);
            return 1;
        
        default: 
            return 0; 
    }
}