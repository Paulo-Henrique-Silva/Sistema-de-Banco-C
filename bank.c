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
    char name[15], id[9], password[25], phone[15], birthday[12]; 
    long int money;
};

enum menu {Transfer = 1, Add, Update, Delete, Show, Details, ExitProgram};

int menu();

int transferMoney();
int addAccount();
int updateAccount();
int deleteAccount();
int showAccounts();
int showDetails();
//menu options

int checkFiles();
int readsStr(char *string, char mode, int sizeOf_str);

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

    //converts to a int
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

    printf("\nType your First Name: ");
    if(readsStr(newUser.name, 'a', sizeof(newUser.name)) == 0)
    {
        printf("\nInvalid Input! DO NOT TYPE:");
        printf("\n - Blank spaces");
        printf("\n - Not alphabet chars");
        printf("\n - Names bigger than %d chars.", sizeof(newUser.name));
        return 0;
    }
    strupr(newUser.name); //lowercase to upper case

    printf("\nType your ID: ");
    if(readsStr(newUser.id, 'n', sizeof(newUser.id)) == 0)
    {
        printf("\nInvalid Input! DO NOT TYPE:");
        printf("\n - Blank spaces");
        printf("\n - Not Numeric chars");
        printf("\n - Ids bigger than %d chars.", sizeof(newUser.id));
        return 0;
    }

    printf("\nType a Phone Number: ");
    if(readsStr(newUser.phone, 'n', sizeof(newUser.phone)) == 0)
    {
        printf("\nInvalid Input! DO NOT TYPE:");
        printf("\n - Blank spaces");
        printf("\n - Not Numeric chars");
        printf("\n - Phone Numbers bigger than %d chars.", sizeof(newUser.phone));
        return 0;
    }
    
    printf("\nType your Birthday(dd/mm/yyyy): ");
    if(readsStr(newUser.birthday, 'c', sizeof(newUser.birthday)) == 0)
    {
      printf("\nInvalid Input! DO NOT TYPE:");  
      printf("\n- Dates bigger than %d chars", sizeof(newUser.birthday));  
    }

    printf("\nType a Password to your Account: ");
    if(readsStr(newUser.password, 'c', sizeof(newUser.password)) == 0)
    {
        printf("\nInvalid Input! DO NOT TYPE:");  
        printf("\n- Passawords bigger than %d chars", sizeof(newUser.birthday));  
    }

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

    printf("\nAccount Sucessfully Added"); 
    return 1;
}

int updateAccount()
{
    char passWord;
    system("cls");

}

int deleteAccount()
{
    FILE *pTemp;
    const char TEMP_FPATH[] = "tempFile.tmp";

    struct accountsInfo file;
    int i = 0, lineNum = 0;
    char input[1024];

    system("cls");
    printf("\t\t\t\t    DELETE AN ACCOUNT\n");
    printf("\t\t------------------------------------------------------\n");

    if(checkFiles() == 0)
    {
        printf("\nIt seems it does not have an Account yet :/"); 
        return 0;
    }

    pAccounts = fopen(ACCOUNTS_FPATH, "r");
    while
    (
        fscanf(pAccounts, "%s %s %s %s %s %ld", 
        &file.name, &file.id, &file.phone, &file.birthday, &file.password, &file.money) 
        != EOF
    )
    {
        i++;
        printf("\t\t\tNUMBER: %d - NAME: %s - PHONE: %s\n\n", i, file.name, file.phone);
    } 
    fclose(pAccounts);
    //prints the files data

    printf("\n\nType the Account Number to Delete it: ");
    fgets(input, 1024, stdin);
    lineNum = atoi(input); //converts to integer

    if(lineNum < 1 || lineNum > i) //if it is greater than the amount of lines
    {
        printf("\nInvalid Input!"); 
        return 0;
    }
    else
    {
        pTemp = fopen(TEMP_FPATH, "w"); 
        i = 0;

        if(checkFiles() == 0 || pTemp == NULL)
        {
            printf("\nThe files were deleted");
            printf("\nIt's not possible to continue.");

            fclose(pAccounts);
            fclose(pTemp);
            return 0; 
        }

        pAccounts = fopen(ACCOUNTS_FPATH, "r");

        while
        (
            fscanf(pAccounts, "%s %s %s %s %s %ld", 
            &file.name, &file.id, &file.phone, &file.birthday, &file.password, &file.money)
            != EOF
        )
        {
            i++;

            //print in file all accounts except for the one that User wants to delete
            if(i != lineNum) 
            {
                fprintf(pTemp, "%s %s %s %s %s %ld\n", 
                file.name, file.id, file.phone, file.birthday, file.password, file.money);
            }
        }

        fclose(pAccounts);
        fclose(pTemp);

        remove(ACCOUNTS_FPATH);
        rename(TEMP_FPATH, ACCOUNTS_FPATH);
        //removes the old file and renames the new one without that account

        printf("\nSuccessfully Removed!"); 
        return 1; 
    }
}

int showAccounts()
{
    struct accountsInfo file;
    char *buffer;
    int i = 0;

    system("cls");
    printf("\t\t\t\t\tACCOUNTS\n");
    printf("\t\t------------------------------------------------------\n");
    
    if(checkFiles() == 0)
    {
        printf("\nIt seems it does not have an Account Yet :/");
        return 0;
    }

    pAccounts = fopen(ACCOUNTS_FPATH, "r");
    while
    (
        fscanf(pAccounts, "%s %s %s %s %s %ld", 
        &file.name, &file.id, &file.phone, &file.birthday, &file.password, &file.money) 
        != EOF
    )
    {
        i++;
        printf("\t\t\tNUMBER: %d - NAME: %s - PHONE: %s\n\n", i, file.name, file.phone);
    }
    fclose(pAccounts);

    return 1;
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
Reads a string with a specific size, in a certain mode
- Returns 1, if it can reads correctly in that mode and assigns the input to the string
- Else, returns 0
Modes: 
 - 'c' - accepts all characters
 - 'a' - accepts alphabets 
 - 'n' - accepts numbers
*/
int readsStr(char *string, char mode, int sizeOf_str)
{
    char buffer[sizeOf_str];

    fgets(buffer, sizeOf_str, stdin);

    if(strchr(buffer, '\n') == NULL) //checks if the input is bigger than size of str
    {
        char extra_chars;

        while((extra_chars = getc(stdin) != '\n' && extra_chars != EOF)); 
        //colects the extra chars to avoid errors

        return 0;
    }

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