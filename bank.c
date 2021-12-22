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
void showAccount_list(struct accountsInfo file);
int amountOf_accounts();

int isA_validId(char *id, struct accountsInfo file);

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
    printf("\n\t\t\t[6] - Show Details of an Existing Account");
    printf("\n\t\t\t[7] - Exit");
    printf("\n\nType your operation: ");
    fgets(input, 1024, stdin);

    //if it fails to convert
    if((operation = atoi(input)) == 0) 
        return 0;
    else
        return operation; 
}

int transferMoney()
{
    FILE *pTemp;
    const char TEMP_FPATH[] = "tempFile.tmp";

    struct accountsInfo user, file;

    char 
    typedId[sizeof(user.id)], typedPass_word[sizeof(user.password)], 
    numInput[1024], *end;

    int giverAccount_num, receiverAccount_num, lineCounter = 0; 
    long long moneyTo_transfer;

    system("cls");
    printf("\t\t\t\tTRANSFER MONEY\n");
    printf("\t\t------------------------------------------------------\n");

    if(amountOf_accounts() < 2) 
    {
        printf("\nIt needs at least two Accounts!");
        return 0; 
    }

    //log in
    printf("\nType your ID: ");
    if(readsStr(typedId, 'n', sizeof(typedId)) == 0)
    {
        printf("\nInvalid Input!");
        return 0;
    }

    printf("\nType your Password: ");
    if(readsStr(typedPass_word, 'c', sizeof(typedPass_word)) == 0)
    {
        printf("\nInvalid Input!");
        return 0;
    }

    if(checkFiles() == 0)
    {
        printf("\nIt seems it does not have an Account yet :/");
        return 0; 
    }

    pAccounts = fopen(ACCOUNTS_FPATH, "r"); 
    while //reads file to find the account
    (
        fscanf(pAccounts, "%s %s %s %s %s %ld", 
        &user.name, &user.id, &user.phone, &user.birthday, &user.password, &user.money) 
        != EOF
    )
    {
        lineCounter++;
        
        //if it matches the account
        if(strcmp(user.id, typedId) == 0 && strcmp(user.password, typedPass_word) == 0)
        {
            giverAccount_num = lineCounter;
            fclose(pAccounts);

            system("cls");
            showAccount_list(user);

            printf("\n\nType the Account number you want to tranfer: ");
            fgets(numInput, 1024, stdin);
            if
            (
                (receiverAccount_num = atoi(numInput)) == 0 || 
                receiverAccount_num > amountOf_accounts() ||
                receiverAccount_num == giverAccount_num
            )
            {
                printf("\nInvalid Input!");
                return 0; 
            }

            printf("\nAvailable Money: R$%ld", user.money);
            printf("\nType the Amount of money you want to Transfer: R$");
            fgets(numInput, 1024, stdin);
            if
            (
                (moneyTo_transfer = strtol(numInput, &end, 10)) <= 0 
                || moneyTo_transfer > user.money
            )
            {
                printf("\nInvalid Input!");
                return 0; 
            }

            pTemp = fopen(TEMP_FPATH, "w"); //creates a tempfile to update the money
            if(checkFiles() == 0 || pTemp == NULL)
            {
                printf("\nThe files were deleted");
                printf("\nIt's not possible to continue.");

                fclose(pTemp);
                remove(TEMP_FPATH);
                return 0; 
            }

            pAccounts = fopen(ACCOUNTS_FPATH, "r"); 
            lineCounter = 0; //resets line counter

            while 
            (
                fscanf(pAccounts, "%s %s %s %s %s %ld", 
                &file.name, &file.id, &file.phone, &file.birthday, &file.password, &file.money) 
                != EOF
            )
            {
                lineCounter++;
                
                /*
                prints all the info.
                - If it is the giver, removes the amount of money from total in file
                - If it is the receiver, adds the amount of money from total in file
                - else, just prints the infos.
                */
                if(lineCounter == giverAccount_num)
                {
                    fprintf(pTemp, "%s %s %s %s %s %ld\n", 
                    file.name, file.id, file.phone, file.birthday, file.password, 
                    file.money - moneyTo_transfer);
                }
                else if(lineCounter == receiverAccount_num)
                {
                    fprintf(pTemp, "%s %s %s %s %s %ld\n", 
                    file.name, file.id, file.phone, file.birthday, file.password, 
                    file.money + moneyTo_transfer);
                }
                else
                {
                    fprintf(pTemp, "%s %s %s %s %s %ld\n", 
                    file.name, file.id, file.phone, file.birthday, file.password, 
                    file.money);
                }
            }

            fclose(pAccounts);
            fclose(pTemp);

            remove(ACCOUNTS_FPATH);
            rename(TEMP_FPATH, ACCOUNTS_FPATH);
            //removes the old file and renames the new one with newinfo

            printf("\nTransaction Successfully made!");
            return 1; //this is always exit the while
        }
    }

    printf("\nSorry, it was not possible to find this Account :/");
    return 0; 
}

int addAccount()
{
    struct accountsInfo newUser;
    char buffer[1024], *end;

    system("cls");
    printf("\t\t\t\tADD AN ACCOUNT\n");
    printf("\t\t------------------------------------------------------\n");

    if(amountOf_accounts() == 10) 
    {
        printf("\nSorry, max amount of Accounts reached! (10)");
        return 0; 
    }

    printf("\nType your First Name: ");
    if(readsStr(newUser.name, 'a', sizeof(newUser.name)) == 0)
    {
        printf("\nInvalid Input! DO NOT TYPE:");
        printf("\n - Blank spaces");
        printf("\n - Not alphabet chars");
        printf("\n - Names bigger than %d chars.", sizeof(newUser.name) - 1);
        //-1 because it has the last char '\0'
        return 0;
    }
    strupr(newUser.name); //lowercase to upper case

    printf("\nType your ID: ");
    if
    (
        readsStr(newUser.id, 'n', sizeof(newUser.id)) == 0 || 
        isA_validId(newUser.id, newUser) == 0
    )
    {
        printf("\nInvalid Input! DO NOT TYPE:");
        printf("\n - Repeated IDs");
        printf("\n - Blank spaces");
        printf("\n - Not Numeric chars");
        printf("\n - Ids bigger than %d chars.", sizeof(newUser.id) - 1);
        return 0;
    }

    printf("\nType a Phone Number: ");
    if(readsStr(newUser.phone, 'n', sizeof(newUser.phone)) == 0)
    {
        printf("\nInvalid Input! DO NOT TYPE:");
        printf("\n - Blank spaces");
        printf("\n - Not Numeric chars");
        printf("\n - Phone Numbers bigger than %d chars.", sizeof(newUser.phone) - 1);
        return 0;
    }
    
    printf("\nType your Birthday(dd/mm/yyyy): ");
    if(readsStr(newUser.birthday, 'c', sizeof(newUser.birthday)) == 0)
    {
      printf("\nInvalid Input! DO NOT TYPE:");  
      printf("\n- Dates bigger than %d chars", sizeof(newUser.birthday) - 1);  
    }

    printf("\nType a Password to your Account: ");
    if(readsStr(newUser.password, 'c', sizeof(newUser.password)) == 0)
    {
        printf("\nInvalid Input! DO NOT TYPE:");  
        printf("\n- Passwords bigger than %d chars", sizeof(newUser.birthday) - 1);  
    }

    printf("\nType how much money You want in your account: R$");
    fgets(buffer, 1024, stdin);
    if((newUser.money = strtol(buffer, &end, 10)) <= 0)
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
    FILE *pTemp;
    const char TEMP_FPATH[] = "tempFile.tmp";

    struct accountsInfo file;

    char 
    //log in 
    typedId[sizeof(file.id)], typedPass_word[sizeof(file.password)],

    //num input from user
    inputNum[1024], 

    //new infos
    newName[sizeof(file.name)], newID[sizeof(file.id)], newPhone[sizeof(file.phone)],
    newBirth[sizeof(file.birthday)], newPass_word[sizeof(file.password)],

    *end; //<- used to convert

    int infoNum;
    long long newMoney; 

    system("cls");
    printf("\t\t\t\t    UPDATE AN ACCOUNT\n");
    printf("\t\t------------------------------------------------------\n");

    //user log in

    printf("\nType your ID: ");
    if(readsStr(typedId, 'n', sizeof(typedId)) == 0)
    {
        printf("\nInvalid Input!");
        return 0;
    }

    printf("\nType your Password: ");
    if(readsStr(typedPass_word, 'c', sizeof(typedPass_word)) == 0)
    {
        printf("\nInvalid Input!");
        return 0;
    }

    if(checkFiles() == 0)
    {
        printf("\nIt seems it does not have an Account yet :/");
        return 0; 
    }

    pAccounts = fopen(ACCOUNTS_FPATH, "r"); 
    while //reads file to find the account
    (
        fscanf(pAccounts, "%s %s %s %s %s %ld", 
        &file.name, &file.id, &file.phone, &file.birthday, &file.password, &file.money) 
        != EOF
    )
    {
        //if the account matches, shows the info.
        if(strcmp(file.id, typedId) == 0 && strcmp(file.password, typedPass_word) == 0)
        {
            system("cls");

            //shows the info and gets the old info
            printf("\t\t\t\t  ACCOUNT INFO");
            printf("\n\n\t\t\t\t1 - NAME: %s", strcpy(newName, file.name));
            printf("\n\n\t\t\t\t2 - ID: %s", strcpy(newID, file.id));
            printf("\n\n\t\t\t\t3 - PHONE: %s", strcpy(newPhone, file.phone));
            printf("\n\n\t\t\t\t4 - BIRTHDAY: %s", strcpy(newBirth, file.birthday));
            printf("\n\n\t\t\t\t5 - PASSWORD: %s", strcpy(newPass_word, file.password));
            printf("\n\n\t\t\t\t6 - MONEY: R$%ld", newMoney = file.money);

            fclose(pAccounts); 

            printf("\n\nType the Info Number to Change: ");
            fgets(inputNum, 1024, stdin); //takes user input and converts to an integer

            switch((infoNum = atoi(inputNum))) //goes to change the respective info
            {
                case 1:
                    printf("\nType the new Name: ");
                    if(readsStr(newName, 'a', sizeof(file.name)) == 0)
                    {
                        printf("\nInvalid Input!");
                        return 0;
                    }
                    strupr(newName);
                    break;
                case 2:
                    printf("\nType the new ID: ");
                    if(readsStr(newID, 'n', sizeof(file.id)) == 0)
                    {
                        printf("\nInvalid Input!");
                        return 0;
                    }
                    break;
                case 3:
                    printf("\nType the new Phone Number: ");
                    if(readsStr(newPhone, 'n', sizeof(file.phone)) == 0)
                    {
                        printf("\nInvalid Input!");
                        return 0;
                    }
                    break;
                case 4:
                    printf("\nType the new Bithday: ");
                    if(readsStr(newBirth, 'c', sizeof(file.birthday)) == 0)
                    {
                        printf("\nInvalid Input!");
                        return 0;
                    }
                    break;
                case 5:
                    printf("\nType the new Password: ");
                    if(readsStr(newPass_word, 'c', sizeof(file.password)) == 0)
                    {
                        printf("\nInvalid Input!");
                        return 0;
                    }
                    break;
                case 6:
                    printf("\nType the new Amount of Money: R$");
                    fgets(inputNum, 1024, stdin);
                    if((newMoney = strtol(inputNum, &end, 10)) <= 0)
                    {
                        printf("\nInvalid Input!");
                        return 0;
                    }
                    break;
                default:
                    printf("\nInvalid Input");
                    return 0;
            }

            pTemp = fopen(TEMP_FPATH, "w"); //creates a tempfile to recreates the info

            if(checkFiles() == 0 || pTemp == NULL)
            {
                printf("\nThe files were deleted");
                printf("\nIt's not possible to continue.");

                fclose(pTemp);
                remove(TEMP_FPATH);
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
                //reads from old file and paste in new file, except for the newinfo.
                if(strcmp(file.id, typedId) == 0 && strcmp(file.password, typedPass_word) == 0)
                {
                    fprintf(pTemp, "%s %s %s %s %s %ld\n", 
                    newName, newID, newPhone, newBirth, newPass_word, newMoney);
                }
                else
                {
                    fprintf(pTemp, "%s %s %s %s %s %ld\n", 
                    file.name, file.id, file.phone, file.birthday, file.password, file.money);
                }
            }

            fclose(pAccounts);
            fclose(pTemp);

            remove(ACCOUNTS_FPATH);
            rename(TEMP_FPATH, ACCOUNTS_FPATH);
            //removes the old file and renames the new one with newinfo

            printf("\nUpdate Successfully made!");
            return 1; //this is always exit the while
        }
    } 

    printf("\nSorry it was not possible to Find this Account :/");
    return 0;
}

int deleteAccount()
{
    FILE *pTemp;
    const char TEMP_FPATH[] = "tempFile.tmp";

    struct accountsInfo file;
    int lineCounter = 0, lineNum = 0;
    char input[1024];

    system("cls");
    printf("\t\t\t\t    DELETE AN ACCOUNT\n");
    printf("\t\t------------------------------------------------------\n");

    if(checkFiles() == 0)
    {
        printf("\nIt seems it does not have an Account yet :/"); 
        return 0;
    }

    showAccount_list(file);

    printf("\n\nType the Account Number to Delete it: ");
    fgets(input, 1024, stdin);
    lineNum = atoi(input); //converts to integer

    if(lineNum <= 0 || lineNum > amountOf_accounts()) //if it is greater than the amount of lines
    {
        printf("\nInvalid Input!"); 
        return 0;
    }
    else
    {
        pTemp = fopen(TEMP_FPATH, "w"); 

        if(checkFiles() == 0 || pTemp == NULL)
        {
            printf("\nThe files were deleted");
            printf("\nIt's not possible to continue.");

            fclose(pTemp);
            remove(TEMP_FPATH);
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
            lineCounter++;

            //print in file all accounts except for the one that User wants to delete
            if(lineCounter != lineNum) 
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

    system("cls");
    printf("\t\t\t\t\tACCOUNTS\n");
    printf("\t\t------------------------------------------------------\n");
    
    if(checkFiles() == 0)
    {
        printf("\nIt seems it does not have an Account Yet :/");
        return 0;
    }

    showAccount_list(file);

    return 1;
}

int showDetails()
{
    struct accountsInfo file;
    char typedId[sizeof(file.id)], typedPass_word[sizeof(file.password)];

    system("cls");
    printf("\t\t\t\t\tDETAILS\n");
    printf("\t\t------------------------------------------------------\n");

    if(checkFiles() == 0)
    {
        printf("\nIt seems it does not have an Account yet :/");
        return 0;
    }

    printf("\nType your ID: ");
    if(readsStr(typedId, 'n', sizeof(typedId)) == 0)
    {
        printf("\nInvalid Input!");
        return 0;
    }

    printf("\nType your Password: ");
    if(readsStr(typedPass_word, 'c', sizeof(typedPass_word)) == 0)
    {
        printf("\nInvalid Input!");
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
        //if the account matches, shows the info.
        if(strcmp(file.id, typedId) == 0 && strcmp(file.password, typedPass_word) == 0)
        {
            system("cls");
            printf("\t\t\t\t\t%s\n", file.name);
            printf("\t\t------------------------------------------------------");
            
            printf("\n\n\t\t\t\tID: %s", file.id);
            printf("\n\n\t\t\t\tPHONE: %s", file.phone);
            printf("\n\n\t\t\t\tBIRTHDAY: %s", file.birthday);
            printf("\n\n\t\t\t\tPASSWORD: %s", file.password);
            printf("\n\n\t\t\t\tMONEY: R$%ld", file.money);

            fclose(pAccounts);
            return 1;
        }
    }
    fclose(pAccounts);

    printf("\nSorry it was not possible to Find this Account :/");
    return 0;
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
    char buffer[1024];

    fgets(buffer, sizeOf_str, stdin);

    if(strchr(buffer, '\n') == NULL) //checks if the input is bigger than size of str
    {
        char extra_chars;

        while((extra_chars = getc(stdin)) != '\n' && extra_chars != EOF); 
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

/*
Show the list of accounts in file
 - Check if the file was deleted before use it
*/
void showAccount_list(struct accountsInfo file)
{
    int lineCounter = 0;

    pAccounts = fopen(ACCOUNTS_FPATH, "r");
    while
    (
        fscanf(pAccounts, "%s %s %s %s %s %ld", 
        &file.name, &file.id, &file.phone, &file.birthday, &file.password, &file.money) 
        != EOF
    )
    {
        lineCounter++;
        printf("\t\t\tNUMBER: %d - NAME: %s - PHONE: %s\n\n", lineCounter, file.name, file.phone);
    } 
    fclose(pAccounts);
    //prints the files data
}

/*
Returns the amount of lines(Accounts in file)
*/
int amountOf_accounts()
{
    int amountOf_lines = 0;
    char line[1024];

    pAccounts = fopen(ACCOUNTS_FPATH, "r");

    while(fgets(line, 1024, pAccounts) != NULL)
        amountOf_lines++;

    fclose(pAccounts);

    return amountOf_lines;
}

/*
    Checks if the id repeated
    - Returns 0 if it repeated 
    - else, returns 1
*/
int isA_validId(char *id, struct accountsInfo file)
{
    pAccounts = fopen(ACCOUNTS_FPATH, "r");

    while
    (
        fscanf(pAccounts, "%s %s %s %s %s %ld", 
        &file.name, &file.id, &file.phone, &file.birthday, &file.password, &file.money) 
        != EOF
    )
    {
        if(strcmp(id, file.id) == 0) 
            return 0;
    } 

    fclose(pAccounts);

    return 1;
}