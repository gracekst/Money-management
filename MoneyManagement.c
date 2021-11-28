#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
int day_between_date(int day1, int month1, int year1, int day2, int month2 ,int year2);
struct tm buying_date(int day, int month, int year, int num);

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


    time_t today;
    time(&today);
    struct tm today_s;
    today_s = *localtime(&today);
    int todayMonth = today_s.tm_mon + 1;
    int todayYear = today_s.tm_year + 1900;


    return 0;
}

//find days between two dates
int day_between_date(int day1, int month1, int year1, int day2, int month2 ,int year2)
{
    time_t day1_t, day2_t;
    struct tm day1_date,day2_date;

    //assign time
    day1_t = time(NULL);
    day2_t = day1_t;

    //assign time to struct
    day1_date = *localtime(&day1_t);
    day2_date = *localtime(&day2_t);

    //change date month and year
    day1_date.tm_mday = day1;
    day1_date.tm_mon = month1-1;
    day1_date.tm_year = year1-1900;

    day2_date.tm_mday = day2;
    day2_date.tm_mon = month2-1;
    day2_date.tm_year = year2-1900;

    //change information in struct to sec 
    day1_t = mktime(&day1_date);
    day2_t = mktime(&day2_date);

    //find different sec and day between two dates
    int diff_sec, diff_day;
    diff_sec = difftime(day2_t,day1_t);
    diff_day = diff_sec / (60*60*24);

    //return amount of days between two dates | plus 1 for including the last date
    return diff_day+1;
}

struct tm buying_date(int day, int month, int year, int num)
{
    time_t day_t, buy_time;

    // assign date into struct tm name day_s
    struct tm day_s = *localtime(&day_t);
    day_s.tm_mday = day;
    day_s.tm_mon = month-1;
    day_s.tm_year = year-1900;

    // change struct day_s to second and put it in variable name day_t
    day_t = mktime(&day_s);

    // find time of the day we will buy the item
    buy_time = day_t + ((num-1) * 24 * 60 * 60);

    // change buy_time to be in strcut
    // plus month by 1 and plus year by 1900 due to strcut tm_mon is ranging from 0-11
    // and tm_year is strcating count from 1900
    struct tm buying_date_struct = *localtime(&buy_time);
    buying_date_struct.tm_mon += 1;
    buying_date_struct.tm_year += 1900;

    // return struct tm
    return buying_date_struct;
}
