#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct item{
    char name[20];
    double price;
};
int* imp_count_day(struct item imp[], int a_imp, int today_day, int today_month, int today_year, double income, double expenses);
int day_between_date(int day1, int month1, int year1, int day2, int month2 ,int year2);

int main() {
    struct item imp[2];
    strcpy("Ipad", imp[0].name);
    imp[0].price = 20000;
    strcpy("Calculator", imp[1].name);
    imp[1].price = 850;

    int *n = imp_count_day(&imp[2], 2, 28, 11, 2021, 10000, 5000);
    for(int i = 0; i < 2; i++)
    {
        printf("%d", *n+i);
    }
    free(n);
}

int* imp_count_day(struct item imp[], int a_imp, int today_day, int today_month, int today_year, double income, double expenses)
{
    int* day_amount = calloc(a_imp, sizeof(int));
    for(int i = 0; i < a_imp; i++)
    {
        int month_day[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int fm = day_between_date(today_day, today_month, today_year, month_day[today_month-1], today_month, today_year);
        //saving per day for each month
        double saving = income - expenses;
        double month_saving[4] = {saving/28, saving/29, saving/30, saving/31};

        //check for leap year
        if(today_year % 4 == 0 && today_year % 100 != 0)
            month_day[1] = 28;
        else
            month_day[1] = 29;

        day_amount[i] = 0;
        int j = 0;
        while(imp[i].price >= 0)
        {
            //checking for the end for a year
            if(today_month == 13)
            {
                today_month = 1;
                //check for leap year
                today_year++;
                if(today_year % 4 == 0 && today_year % 100 != 0)
                    month_day[1] = 28;
                else
                    month_day[1] = 29;
            }

            int current_month = (month_day[today_month-1]);
            double current_month_saving;
            if(current_month == 28)
                current_month_saving = month_saving[0];
            else if(current_month == 29)
                current_month_saving = month_saving[1];
            else if(current_month == 30)
                current_month_saving = month_saving[2];
            else if(current_month == 31)
                current_month_saving = month_saving[3];

            int k = 0;
            if(j == 0)
            {
                while(k < fm && imp[i].price > 0)
                {
                    imp[i].price -= current_month_saving;
                    day_amount[i]++;
                    k++;
                }
            }
            else
            {
                while(k < current_month && imp[i].price > 0)
                {
                    imp[i].price -= current_month_saving;
                    k++;
                    day_amount[i]++;
                }
            }
            today_month++;
            j++;
        }
    }
    return day_amount;
}

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
