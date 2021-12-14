#include<stdio.h>
#include <time.h>
int day_between_date(int day1, int month1, int year1, int day2, int month2 ,int year2);
struct tm buying_date(int day, int month, int year, int num);
int count_day(double price, double *price_pt, int today_day, int today_month, int today_year, double income, double expenses);
void print_table(char name[], int day, int month, int year, FILE *file);

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

    if(ext_money <= 0)
        printf("unable to buy any items\n");
    
    time_t today;
    time(&today);
    struct tm today_s;
    today_s = *localtime(&today);
    int todayMonth = today_s.tm_mon + 1;
    int todayYear = today_s.tm_year + 1900;
    
    //important items
    int total_imp_day[amt1];
    double remainder = 0;
    for(int k = 0; k < amt1; k++)
    {
        if(k != 0)
            remainder = imp[k-1].price;
        int imp_day = 0;
        imp_day = count_day((imp[k].price)-remainder, &imp[k].price, today_s.tm_mday, todayMonth, todayYear, uinfo.income, uinfo.expense);
        if(remainder != 0)
            imp_day++;
        total_imp_day[k] = imp_day;
    }
    //non-important items
    double tmp_unimp = totalp_unimp;
    int un_imp_day = count_day(tmp_unimp, &tmp_unimp, today_s.tm_mday, todayMonth, todayYear, uinfo.income, uinfo.expense);

    FILE* file = fopen("file.html", "w");
    fprintf(file,"<style>\n");
    fprintf(file,"body{background-color: #FBF8DD}\n");
    fprintf(file,"h1{color: black; font-size: 30px; display: flex; justify-content: center;}");
    fprintf(file,"h2{color: #7C743C; font-size: 25px; display: flex; justify-content: center;}");
    fprintf(file,"table, td, tr{border: 1px solid black; height: 70px; text-align: center;}\n");
    fprintf(file,"table{width: 100%%; border-collapse: collapse; margin-right: auto; width: 100%%}");
    fprintf(file,"</style></head><body>\n");

    fprintf(file,"<h1>Money management</h1>\n");
    fprintf(file,"<h2>Savings per month</h2>\n");
    fprintf(file,"<table>\n");
    fprintf(file,"<tr><td>Income</td>\n");
    fprintf(file,"<td>%.2lf</td></tr>\n", uinfo.income);
    fprintf(file,"<tr><td>Expenses</td>\n");
    fprintf(file,"<td>%.2lf</td></tr>\n", uinfo.expense);
    fprintf(file,"<tr><td>Savings</td>\n");
    fprintf(file,"<td>%.2lf</td></tr>\n", uinfo.income-uinfo.expense);
    fprintf(file,"</table>\n<br></br><br></br>");

    fprintf(file,"<h2>Item name and date that can be bought for important item</h2>\n");
    fprintf(file,"<table>\n");
    fprintf(file,"<tr><td>Name</td>\n");
    fprintf(file,"<td>Date</td></tr>\n");

    struct tm imp_buy_date[amt1];
    imp_buy_date[0] = buying_date(today_s.tm_mday, todayMonth, todayYear, total_imp_day[0]);
    print_table(imp[0].name, imp_buy_date[0].tm_mday, imp_buy_date[0].tm_mon, imp_buy_date[0].tm_year, file);
    for(int l = 1; l < amt1; l++)
    {
        imp_buy_date[l] = buying_date(imp_buy_date[l-1].tm_mday, imp_buy_date[l-1].tm_mon, imp_buy_date[l-1].tm_year, total_imp_day[l]);
        print_table(imp[l].name, imp_buy_date[l].tm_mday, imp_buy_date[l].tm_mon, imp_buy_date[l].tm_year, file);
    }
    fprintf(file,"</table>\n");

    fprintf(file,"<h2>Item name and date that can be bought for unimportant item</h2>\n");
    fprintf(file,"<table>\n");
    fprintf(file,"<tr><td>Name</td>\n");
    fprintf(file,"<td>Date</td></tr>\n");
    struct tm unimp_buy_date = buying_date(imp_buy_date[amt1-1].tm_mday,imp_buy_date[amt1-1].tm_mon,imp_buy_date[amt1-1].tm_year, un_imp_day);
    for(int l = 0; l < amt2; l++)
    {
        print_table(un_imp[l].name, unimp_buy_date.tm_mday, unimp_buy_date.tm_mon, unimp_buy_date.tm_year, file);
    }
    fprintf(file,"</table>\n");

    fclose(file);
    
    int delay = day_between_date(dl.day, dl.month, dl.year, unimp_buy_date.tm_mday,unimp_buy_date.tm_mon,unimp_buy_date.tm_year);
    if(unimp_buy_date.tm_year > dl.year)
        printf("\nDeadlines need need to be delayed by %d days, inorder to buy all items.\n", delay);

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

int count_day(double price, double *price_pt, int today_day, int today_month, int today_year, double income, double expenses)
{
    int day = 0;
    int month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int fm = day_between_date(today_day, today_month, today_year, month_day[today_month-1], today_month, today_year);
    //saving per day for each month
    double saving = income - expenses;
    double month_saving[4] = {saving/28, saving/29, saving/30, saving/31};

    //check for leap year
    if(today_year % 4 == 0 && today_year % 100 != 0)
        month_day[1] = 29;
    else
        month_day[1] = 28;

    int j = 0;
    while(price > 0)
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
            while(k < fm && price > 0)
            {
                price -= current_month_saving;
                day++;
                k++;
            }
        }
        else
        {
            while(k < current_month && price > 0)
            {
                price -= current_month_saving;
                day++;
                k++;
            }
        }
        today_month++;
        j++;
    }
    *price_pt = price;
    return day;
}

void print_table(char name[], int day, int month, int year, FILE *file)
{
    fprintf(file,"<tr><td>%s</td>\n", name);
    fprintf(file,"<td>%d/ %d/ %d</td></tr>\n", day, month, year);
}
