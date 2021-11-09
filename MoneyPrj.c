#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>
#include <math.h>

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

//money to save per day
double daily_save(int days, double money)
{
    double save_pday;

    //calculate amount per day
    save_pday = money / days;

    return save_pday;
}

//money to save per week
double weekly_save(int week, double money)
{
    double save_pweek;

    save_pweek = money / week;
    return save_pweek;
}
    
int main()
{   
    bool week = false;

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

    printf("The total price for all items: %d\n", total_price);
    fprintf(fptr,"The total price for all itmes: %d\n", total_price);

    while(1)
    {
        printf("How would you like to save? (type week/day): ");
        scanf("%s", &save_type);

        if(strcmp(save_type,"week") == 0)
        {
            week = true;
            break;
        }
        else if (strcmp(save_type,"day") == 0)
        {
            week = false;
            break;
        }
        else
        {
            printf("Erro, please try agian.\n");
        }
    }

    time_t today;
    time(&today);
    struct tm today_s;
    today_s = *localtime(&today);
    int todayMonth = today_s.tm_mon + 1;
    int todayYear = today_s.tm_year + 1900;

    int days = day_between_date_today(today_s.tm_mday, todayMonth, todayYear, dt.day, dt.month, dt.year);

    int m,f,s;
    if(todayYear == dt.year)
    {
        m = dt.month - todayMonth;
    }
    else
    {
        f = (12 - todayMonth) + 1;
        s = dt.month - 1;
        m = f+s;
    }

    int dayEachMonth[m];

    if(todayYear == dt.year)
    {
        int x = 0;
        for(int i = todayMonth; i < dt.month; i++)
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
        for(int x = 0; x < s; x++)
        {
            dayEachMonth[i++] = day_between_date_today(1,jan++,dt.year,1,jan+1,dt.year);
        }
    }

    double price_type[2];
    double price = total_price;
    int howManyMonth = 0;
    int aMonth = m;
    int dDay = days;
    int x = 0;
    while(price > 0)
    {
        if(price > ext_money && dDay > dayEachMonth[x])
        {
            price_type[0] = ext_money;
            price -= ext_money;
            dDay -= dayEachMonth[x++];
            howManyMonth++;
            aMonth--;
        }
        else
        {
            price_type[1] = price;
            break;
        }
    }

    double save[2];
    int dayLeft = days;
    int weekLeft;
    int totalday = 0;
    int totalweek;

    if(aMonth > 0)
    {
        for(int j = 0; j < howManyMonth; j++)
        {
            dayLeft -= dayEachMonth[j];
            totalday += dayEachMonth[j];
        }

        if(week == true)
        {
            totalweek = totalday / 7;
            weekLeft = (dayLeft + (totalday % 7)) / 7;

            save[0] = weekly_save(totalweek, price_type[0]) ;
            save[1] = weekly_save(weekLeft, price_type[1]);
        }
        else
        {
            save[0] = daily_save(totalday, price_type[0]);
            save[1] = daily_save(dayLeft, price_type[1]);
        }
    }
    else if(aMonth == 0 && days == dayEachMonth[0])
    {
        if(week == true)
        {
            totalweek = days / 7;

            save[0] = weekly_save(totalweek, price_type[0]) ;
        }
        else
        {
            save[0] = daily_save(days, price_type[0]);
        }
    }
    else
    {
        printf("Invalid date");
    }

    printf("%lf %lf %lf %d %d %d %d\n",price_type[0], price_type[1],price,howManyMonth,aMonth,dDay,x);
    printf("%lf %lf %d %d %d %d\n",save[0],save[1],dayLeft,weekLeft,totalday,totalweek);
    printf("%d %d\n ",days, m);
    for(int i = 0; i < m; i++)
    {
        printf("%d ", dayEachMonth[i]);
    }
    
    return 0;
}