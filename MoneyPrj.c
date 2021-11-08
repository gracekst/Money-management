#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


// necessay information
struct date
{
    int day;
    int month;
    int year;

};

struct user_info
{
    int income;
    int expense;

};

struct item_info
{   
    int amount;
    int price;
};

    
int main()
{   
    bool week = false;
    bool day = false;

    char save_type[50];

    // opening a file
    FILE *fptr = fopen("MoneyProject.txt", "w+");

    if(fptr == NULL)
    {
        fprintf(fptr, "\nError opened file\n");
        exit(1);
    }

    // ask inputs for date information

    struct date dt;
    printf("---Enter date & time that u would like to buy your items---\n");
    
    printf("Enter day: ");
    scanf("%d", &dt.day);

    printf("Enter Month: ");
    scanf("%d", &dt.month);

    printf("Enter Year: ");
    scanf("%d", &dt.year);
    
    
    // ask inputs for user's information

    printf("---Please roughly tell your income and expenses---\n");

    struct user_info uinfo;

    printf("Enter your income per month: ");
    scanf("%d", &uinfo.income);

    printf("Enter your expenses per month: ");
    scanf("%d", &uinfo.expense);

    int ext_money;
    ext_money = uinfo.income - uinfo.expense;
    printf("Extra money from expenses: %d \n", ext_money);


    //asks the price of itmes you want to buy

    printf("---Pls tell the details of items---\n");

    struct item_info itm_info;
    printf("Amount of items you want to buy: ");
    scanf("%d" , &itm_info.amount);

    //printing the infos in file

    fputs("---Date & Time that the user will buy his items---\n", fptr);
    fprintf(fptr,"Day: %2d\n", dt.day);
    fprintf(fptr,"Month: %d\n", dt.month);
    fprintf(fptr,"Year: %d\n", dt.year);

    fputs("---Income and Expenses---\n",fptr);
    fprintf(fptr,"Monthly Income: %d\n", uinfo.income);
    fprintf(fptr,"Monthly Expense: %d\n", uinfo.expense);
    fprintf(fptr,"Extra Money: %d\n", ext_money);

    fputs("---Items and their price---\n", fptr);
    fprintf(fptr,"Amount of items: %d\n", itm_info.amount);

    int i = 0;
    int total_price = 0;
    for(i = 1; i <= itm_info.amount; i++)
    {   
        printf("Enter the price for item %d:", i);
        fprintf(fptr, "The price for item %d:", i);
        scanf("%d", &itm_info.price);
        fprintf(fptr, "%d\n", itm_info.price);
        total_price = total_price + itm_info.price;
    }

    printf("The total price for all items: %d", total_price);
    fprintf(fptr,"The total price for all itmes: %d\n", total_price);

    printf("How would you like to save? (type week/day): ");
    scanf("%s", &save_type);

    if(save_type == "week")
    {
        //code
    }

    else if (save_type == "day")
    {
        //code
    }
    
    else
    {
        // code
    }

    return 0;
}
    
