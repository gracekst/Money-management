#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>
int day_between_date_today(int day1, int month1, int year1, int day2, int month2 ,int year2);
void print_table(double income, double expenses, double extra, double savings, char* chart);
void print_chart(double income, double expenses, double extra, double savings, char* chart, int start_month, int count);
void chart_generator(double income, double expenses, double save_pmonth[], int size, char* chart, int start_month);

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
    
int main()
{   

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
    int m;
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
        for(int year = todayYear; year <= dt.year; year++)
        {
            if(year == todayYear)
            {
                m = m + (12 - todayMonth) +1;
            }
            else if(year == dt.year)
            {
                m = m + dt.month;
            }
            else
            {
                m = m+12;
            }
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
        for(int year = todayYear; year <= dt.year; year++)
        {
            if(year == todayYear)
            {
                for(int x = todayMonth; x < 12; x++)
                {
                    dayEachMonth[i++] = day_between_date_today(1,x,year,1,x+1,year);
                }
                dayEachMonth[i++] = day_between_date_today(1,12,year,1,1,year+1);
            }
            else if(year == dt.year)
            {
                for(int x = 1; x <= dt.month; x++)
                {
                    dayEachMonth[i++] = day_between_date_today(1,x,year,1,x+1,year);
                }
            }
            else
            {
                for(int x = 1; x < 12; x++)
                {
                    dayEachMonth[i++] = day_between_date_today(1,x,year,1,x+1,year);
                }
                dayEachMonth[i++] = day_between_date_today(1,12,year,1,1,year+1);
            }
        }
    }

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
            printf("Please extend the deadline\n");
        }
    }
    else
    {
        printf("Please extend the deadline\n");
    }
    
    //open output file and print table and piechart
    FILE *chart;
    chart = fopen("chart.html", "w");
    fprintf(chart,"<!DOCTYPE HTML>\n");
    fprintf(chart,"<html>\n");
    fprintf(chart,"<head>\n");
    fprintf(chart,"<title>Money management-Pie chart</title>\n");
    int size = sizeof(save_pmonth)/sizeof(save_pmonth[0]);
    print_table(uinfo.income/30, uinfo.expense/30, (uinfo.income/30)-save_pday, save_pday, chart);
    fprintf(chart,"<br></br>\n");
    chart_generator(uinfo.income, uinfo.expense, save_pmonth, size, chart, todayMonth);
    fprintf(chart,"</body></html>");
    fclose(chart);
    
    return 0;
}

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

//printing table of savings per day
void print_table(double income, double expenses, double extra, double savings, char* chart)
{
    fprintf(chart,"<style>\n");
    fprintf(chart,"h1{color: black; font-size: 30px; display: flex; justify-content: center;}");
    fprintf(chart,"h2{color: #7C743C; font-size: 25px; display: flex; justify-content: center;}");
    fprintf(chart,"table, td, tr{border: 1px solid black; height: 70px; text-align: center;}\n");
    fprintf(chart,"table{width: 100%%; border-collapse: collapse; margin-right: auto; width: 100%%}");
    fprintf(chart,"</style></head><body>\n");

    fprintf(chart,"<h1>Money management</h1>\n");
    fprintf(chart,"<h2>Approximate amount of savings per day</h2>\n");
    fprintf(chart,"<table>\n");
    fprintf(chart,"<tr><td>Income</td>\n");
    fprintf(chart,"<td>%.2lf</td></tr>\n", income);
    fprintf(chart,"<tr><td>Expenses</td>\n");
    fprintf(chart,"<td>%.2lf</td></tr>\n", expenses);
    fprintf(chart,"<tr><td>Extra money</td>\n");
    fprintf(chart,"<td>%.2lf</td></tr>\n", extra);
    fprintf(chart,"<tr><td>Savings</td>\n");
    fprintf(chart,"<td>%.2lf</td></tr>\n", savings);
    fprintf(chart,"</table>\n");
}

//printing piechart for each month
void print_chart(double income, double expenses, double extra, double savings, char* chart, int start_month, int count)
{
    //calculate the proportion on piechart for each part
    double percent_expenses = (expenses/income)*360;
    double percent_extra = (extra/income)*360;
    double percent_savings = (savings/income)*360;

    double green, blue, yellow;
    char g, b, y;

    //find the value of each parts in html css pie chart
    if (percent_expenses <= percent_extra && percent_expenses <= percent_savings){
        green = percent_expenses;
        g = 'e';
        if(percent_extra <= percent_savings){
            blue = percent_extra+percent_expenses;
            b = 'x';
            yellow = percent_savings+percent_extra+percent_expenses;
            y = 's';
        }
        else{
            blue = percent_savings+percent_expenses;
            b = 's';
            yellow = percent_extra+percent_savings+percent_expenses;
            y = 'x';
        }
    }
    else if (percent_extra <= percent_expenses && percent_extra <= percent_savings){
        green = percent_extra;
        g = 'x';
        if(percent_expenses <= percent_savings){
            blue = percent_expenses+percent_extra;
            b = 'e';
            yellow = percent_savings+percent_expenses+percent_extra;
            y = 's';
        }
        else{
            blue = percent_savings+percent_extra;
            b = 's';
            yellow = percent_expenses+percent_savings+percent_extra;
            y = 'e';
        }
    }
    else{
        green = percent_savings;
        g = 's';
        if(percent_extra <= percent_expenses){
            blue = percent_extra+percent_savings;
            b = 'x';
            yellow = percent_expenses+percent_extra+percent_savings;
            y = 'e';
        }
        else{
            blue = percent_expenses+percent_savings;
            b = 'e';
            yellow = percent_extra+percent_expenses+percent_savings;
            y = 'x';
        }
    }

    //printing html code to a file
    fprintf(chart,"<style>\n");
    fprintf(chart,"body{background-color: #FBF8DD}\n");
    fprintf(chart,".piechart%d\n", count);
    fprintf(chart,"{border-radius: 50%% ;margin-top: 50px; margin-left: 300px; display: inline-block;");
    fprintf(chart,"position: absolute; width: 300px;height: 300px;");
    fprintf(chart,"background-image: conic-gradient");
    fprintf(chart,"(#5C9215 %lfdeg,#1CA2A3 0 %lfdeg,#B4AF21 0 %lfdeg);}", green, blue, yellow);
    fprintf(chart,"h3{color: #7C743C; font-size: 25px; display: flex; justify-content: center;text-decoration: underline;}");
    fprintf(chart,".income{font-size: 20px; display: flex; margin-top:70px; margin-left: 1100px;}");

    if(g == 'e')
        fprintf(chart,".expenses\n");
    else if (g == 'x')
        fprintf(chart,".extra\n");
    else
        fprintf(chart,".savings\n");
    fprintf(chart,"{color: #5C9215; font-size: 20px; display: flex; margin-top:50px; margin-left: 1100px;}\n");

    if(b == 'e')
        fprintf(chart,".expenses\n");
    else if (b == 'x')
        fprintf(chart,".extra\n");
    else
        fprintf(chart,".savings\n");
    fprintf(chart,"{color: #1CA2A3; font-size: 20px; display: flex; margin-top:50px; margin-left: 1100px;}\n");

    if(y == 'e')
        fprintf(chart,".expenses\n");
    else if (y == 'x')
        fprintf(chart,".extra\n");
    else
        fprintf(chart,".savings\n");
    fprintf(chart,"{color: #B4AF21; font-size: 20px; display: flex; margin-top:50px; margin-left: 1100px;}\n");

    fprintf(chart,"</style></head><body>");
    fprintf(chart,"<h3>Month %d</h3><div class=\"piechart%d\"></div>", start_month, count);
    fprintf(chart,"<div class=\"income\">Income: %.2lf</div>", income);
    fprintf(chart,"<div class=\"expenses\">Expenses: %.2lf (%.2lf%%)</div>", expenses, expenses/income*100);
    fprintf(chart,"<div class=\"extra\">Extra money: %.2lf (%.2lf%%)</div>", extra, extra/income*100);
    fprintf(chart,"<div class=\"savings\">Savings: %.2lf (%.2lf%%)</div>", savings, savings/income*100);

}

void chart_generator(double income, double expenses, double save_pmonth[], int size, char* chart, int start_month)
{
    //loop over a month and print html piechart code by calling function
    int month_count = start_month;
    for(int i = 0; i < size; i++)
    {
        if (month_count == 13)
            month_count = 1;
        double extra_money = income-expenses-save_pmonth[i];
        print_chart(income, expenses, extra_money, save_pmonth[i], chart, month_count, i);
        fprintf(chart,"<br></br><br></br><br></br><br></br>");
        month_count++;
    }
}
