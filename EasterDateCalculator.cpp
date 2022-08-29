/**
 Developer: Niraj Nepal
 Date: 2022-08-28
 Program Name: When's Easter Day!
 Summary: This program will calculate the date of Easter Day for a given year.
 Credits: Notes from Program Description, Few resources from internet, Research on Golden Number.
 Inspired by https://www.daniweb.com/programming/software-development/threads/463261/c-easter-day-calculation ( Some variable naming are similar ).
 **/

#include <iostream>
using namespace std;

int main()
{
    int goldenNumber, year, a, b, c, d, e, f, g, h, i, k, l, m, p, EasterMonth, EasterDay;
    bool leapYear;

    cout << "Please Enter the year > ";
    cin >> year;

    a = year % 19;                                              // calculates the Golden Number, which is a number used to determine the date of Easter.
    b = year / 100;                                             // calculates the century of the year.
    c = year % 100;                                             // calculates the year within the century.
    d = b / 4;                                                  // calculates the number of years since the year was divided by 4.
    e = b % 4;                                                  // calculates the number of years since the year was divided by 4.
    f = (b + 8) / 25;                                           // calculates the number of years since the year was divided by 25.
    g = (b - f + 1) / 3;                                        // calculates the number of years since the year was divided by 3.
    h = (19 * a + b - d - g + 15) % 30;                         // calculates the number of days since the year was divided by 30.
    i = c / 4;                                                  // calculates the number of years since the year was divided by 4.
    k = c % 4;                                                  // calculates the number of years since the year was divided by 4.
    l = (32 + 2 * e + 2 * i - h - k) % 7;                       // calculates the number of days since the year was divided by 7.
    EasterMonth = (h + l - 7 * m + 114) / 31;                   // calculates the month of Easter.
    p = (h + l - 7 * m + 114) % 31;                             // calculates the day of Easter.
    EasterDay = p + 1;                                          // calculates the day of Easter.

    if ((EasterMonth == 3) && (EasterDay > 31)) // The if statement is used to check if EasterMonth is equal to 3 and EasterDay is greater than 31.
    {                                           // If both conditions are true, then EasterMonth is set to 4 and EasterDay is set to EasterDay - 31.
        EasterMonth = 4;
        EasterDay = EasterDay - 31;
    }

    cout << "Easter falls on " << EasterDay << "/" << EasterMonth << "/" << year << "." << endl;

    return 0;
}



