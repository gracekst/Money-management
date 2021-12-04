# Description
-This program will ask for users’ monthly income and expenses to calculate for the nearest date users can save money and buy the item they want. Items in this program can be classified into 2 categories which are important items and unimportant items. Important item is an item users want to buy as soon as possible. Users will also be asked to prioritize the order of the items in these categories, so the most prioritized items will get calculated first. For unimportant items categories, all items will get calculated together at once.\
\
-Users will also be asked for a deadlines, they want to buy this items, and if their savings is not enough for buying items they want, program will also output a total date it needs to be delayed in order to buy those items.

# Library
In this program we need 1 more libraby other than standard libraby that we normally use in C\
\
**Standard library**
  * stdio.h
<!-- -->
**Additional library**
  * time.h

# Function Explanation
1. `int day_between_date(int day1, int month1, int year1, int day2, int month2 ,int year2)`\
function that will calculate *number of days + 1* between two dates (+1, for including the first date)\
\
` days = day_between_date(25,11,2021,3,3,2022);`\
the value of variable days is equal to ***99***

2. ` struct tm buying_date(int day, int month, int year, int num)`\
  function that will return structure tm which contain *date* after num-1 days (-1, for including the first day that we start to save money)\
  \
  **For example**
     * if date of the fist day that we start to save money is 15/11/2021 and we need only 1 day for buying an item.Thus, buying date will be the same with fisrt date
     * `struct tm buy = buying_date(29,11,2021,40);`\
    the result date is *7/11/2022*\
  \
  **Remind**
    * In usual, struct tm will return month in rang of 0-11 and year in 2xxx-1900, but for struct tm that is returning from this function,it already be in a normal form that we're using in our life  
  
3. `int count_day(double price, double *price_pt, int today_day, int today_month, int today_year, double income, double expenses)`  
function that will return the total day of saving in order to buy specific item that item's price has been put in at a price parameter  
\
`total_day = count_day(10000, &price_pt, 29, 11, 2021, 10000, 5000);`\
the value of total_day will be ***34***  
  
4. `void print_table(char name[], int day, int month, int year, FILE *file)`  
function that will printing a html code that generate a table to a file pointer that pass in to a function.


# Member
1) Kasita Sansanthad 64011426  
2) Pantila Kosalaraksa 64011517  
3) Theint Nandarsu 64011752  
