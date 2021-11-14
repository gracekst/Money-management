#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>
#include <math.h>
#include <limits.h>

// necessay information
struct date
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

struct item_info
{   
    int amount;
    double price;
};

//find days between two dates
int day_between_date_today(int day1, int month1, int year1, int day2, int month2 ,int year2)
{
    //struct tm range of tm_mon = 0-11
    --month1;
    --month2;

    //year in struct tm is count from 1900 | for 1901 tm_year = 1
    year1 -= 1900;
    year2 -= 1900;

    time_t day1_t, day2_t;
    struct tm day1_date,day2_date;

    //assign time
    time(&day1_t);
    time(&day2_t);

    //assign time to struct
    day1_date = *localtime(&day1_t);
    day2_date = *localtime(&day2_t);

    //change date month and year
    day1_date.tm_mday = day1;
    day1_date.tm_mon = month1;
    day1_date.tm_year = year1;

    day2_date.tm_mday = day2;
    day2_date.tm_mon = month2;
    day2_date.tm_year = year2;

    //change information in struct to sec 
    day1_t = mktime(&day1_date);
    day2_t = mktime(&day2_date);

    //find different sec and day between two dates
    int diff_sec, diff_day;
    diff_sec = difftime(day2_t,day1_t);
    diff_day = diff_sec / (60*60*24);

    //return amount of days between two dates
    return diff_day;
}
    
int main()
{   
    bool week_bool = false;

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
    scanf("%lf", &uinfo.income);

    printf("Enter your expenses per month: ");
    scanf("%lf", &uinfo.expense);

    double ext_money;
    ext_money = uinfo.income - uinfo.expense;
    printf("Extra money from expenses: %.2lf \n", ext_money);


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
    fprintf(fptr,"Monthly Income: %.2lf\n", uinfo.income);
    fprintf(fptr,"Monthly Expense: %.2lf\n", uinfo.expense);
    fprintf(fptr,"Extra Money: %.2lf\n", ext_money);

    fputs("---Items and their price---\n", fptr);
    fprintf(fptr,"Amount of items: %d\n", itm_info.amount);

    int i = 0;
    double total_price = 0;
    for(i = 1; i <= itm_info.amount; i++)
    {   
        printf("Enter the price for item %d:", i);
        fprintf(fptr, "The price for item %d:", i);
        scanf("%lf", &itm_info.price);
        fprintf(fptr, "%.2lf\n", itm_info.price);
        total_price = total_price + itm_info.price;
    }

    printf("The total price for all items: %.2lf\n", total_price);
    fprintf(fptr,"The total price for all itmes: %.2lf\n", total_price);

    time_t today;
    time(&today);
    struct tm today_s;
    today_s = *localtime(&today);
    int todayMonth = today_s.tm_mon + 1;
    int todayYear = today_s.tm_year + 1900;

    //how many days left
    int days = day_between_date_today(today_s.tm_mday, todayMonth, todayYear, dt.day, dt.month, dt.year);

    /*how many days in each month*/
    //how many month
    int m,f,s;
    if(todayYear == dt.year)
    {
        if(todayMonth != 12)
        {
            m = (dt.month - todayMonth)+1;
        }
        else
        {
            m = 1;
        }
    }
    else
    {
        f = (12 - todayMonth) + 1;
        s = dt.month;
        m = f+s;
    }

    //days in each month
    int dayEachMonth[m];
    if(todayYear == dt.year)
    {
        int x = 0;
        for(int i = todayMonth; i <= dt.month; i++)
        {
            dayEachMonth[x++] = day_between_date_today(1,i,todayYear,1,i+1,dt.year);
        }
    }
    else
    {
        int i = 0;
        for(int x = 0; x < f-1; x++)
        {
            dayEachMonth[i++] = day_between_date_today(1,todayMonth++,todayYear,1,todayMonth+1,todayYear); 
        }
        dayEachMonth[i++] = day_between_date_today(1,todayMonth,todayYear,1,1,dt.year);
        int jan = 1;
        for(int x = 0; x <= s; x++)
        {
            dayEachMonth[i++] = day_between_date_today(1,jan++,dt.year,1,jan+1,dt.year);
        }
    }

    //find largest days
    int first_mon_day = dayEachMonth[0] - today_s.tm_mday;
    int last_mon_day = dt.day;

    //how much to save
    double save_pday, save_pmonth[m], largest_value = 0;
    //see if total price excess money left(every month)
    if(total_price < (ext_money*m))
    {
        //save per day
        save_pday = total_price / days;
    
        //save per month
        for(int p = 0; p < m; p++)
        {
            if(p == 0)
            {
                save_pmonth[p] = save_pday * first_mon_day;
            }
            else if(p == (m-1))
            {
                save_pmonth[p] = save_pday * last_mon_day;
            }
            else
            {
                save_pmonth[p] = save_pday *dayEachMonth[p];
            }
        }

        //find the largest values that user need to save per month
        for(int p = 0; p < m; p++)
        {
            if(save_pmonth[p] > largest_value)
            {
                largest_value = save_pmonth[p];
            }
        }

        //if the value is more than money has left
        if(largest_value > ext_money)
        {
            save_pday = 0;
            for(int p = 0; p < m; p++)
            {
                save_pmonth[p] = 0;
            }
            printf("Please exten the deadline\n");
        }
    }
    else
    {
        printf("Please exten the deadline\n");
    }
    
    return 0;
}