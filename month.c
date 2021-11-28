#include <stdio.h>
#include <time.h>
#include <math.h>
struct tm buying_date(int day, int month, int year, int num);

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

int main()
{
    int k = day_between_date(25,11,2021,28,11,2021);
    printf("\n%d\n",k);
    struct tm buy = buying_date(25,11,2021,4);
    printf("%d/%d/%d", buy.tm_mday, buy.tm_mon, buy.tm_year);
    return 0;
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