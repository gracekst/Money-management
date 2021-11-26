#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct deadline
{
    int day;
    int month;
    int year;
};

struct user_info
{
    double income;
    double expense;
};

struct item
{
    char name[20];
    double price;
};

int main()
{   
    // ask income and expenses
    struct user_info uinfo;

    printf("---Please enter your income and expenses---\n");

    printf("Enter your income per month: ");
    scanf("%lf", &uinfo.income);

    printf("Enter your expenses per month: ");
    scanf("%lf", &uinfo.expense);

    double ext_money;
    ext_money = uinfo.income - uinfo.expense;
    printf("Extra money from expenses: %.2lf \n", ext_money);

    printf("\n");

     // ask inputs for date information
    struct deadline dl;

    printf("---Enter date for deadline---\n");
    
    printf("Enter day: ");
    scanf("%d", &dl.day);

    printf("Enter Month: ");
    scanf("%d", &dl.month);

    printf("Enter Year: ");
    scanf("%d", &dl.year);

    printf("\n");

    printf("---Items Information---\n");

    // adding inputs for important items
    int amt1, i;
    printf("Enter the amount of important items: ");
    scanf("%d", &amt1);

    struct item imp[amt1]; // array structure for important items
    double totalp_imp = 0;

    printf("Note: Enter the important items by your priority!\n** The first priority will be bought first**\n\n");

    for(i = 0; i < amt1; i++)
    {
        printf("Enter the details of important item %d\n", i+1);

        printf("Enter name: ");
        scanf("%s", imp[i].name);

        printf("Enter price: ");
        scanf("%lf", &imp[i].price);
     
    }
    printf("\n");

    // adding inputs for unimportant items
    int amt2, j;
    printf("Enter the amount of unimportant items: ");
    scanf("%d", &amt2);

    struct item un_imp[amt2]; // array structure for unimportant items
    double totalp_unimp = 0;
 
    for(j = 0; j < amt2; j++)
    {
        printf("Enter the details of unimportant items\n");

        printf("Enter name: ");
        scanf("%s", un_imp[j].name);

        printf("Enter price: ");
        scanf("%lf", &un_imp[j].price);
     
    }
    printf("\n");

    // show output details for items(important + unimportant)
    for(i = 0; i < amt1; i++)
    {
        printf("Details of important item %d\n", i+1);
        printf("Name:%s\tPrice:%.2lf\n", imp[i].name, imp[i].price);
        totalp_imp = totalp_imp + imp[i].price;
    }

    
    printf("Total price of important items: %.2lf\n", totalp_imp);

    printf("\n");

    for(j = 0; j < amt2; j++)
    {
        printf("Details of unimportant item\n");
        printf("Name:%s\tPrice:%.2lf\n", un_imp[j].name, un_imp[j].price);
        totalp_unimp = totalp_unimp + un_imp[j].price;
    }

    
    printf("Total price for unimportant items: %.2lf", totalp_unimp);


    // to be contiued
    


    return 0;
}