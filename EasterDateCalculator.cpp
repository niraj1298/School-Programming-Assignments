/**
 Developer: Niraj Nepal
 Date: 2022-08-28
 Program Name: When's Easter Day!
 Summary: This program will calculate the date of Easter Day for a given year.
 Credits: Notes from Program Description
 **/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int goldenNumber,y,c,x,d,e,n,z;
    cout << "Please Enter the year > ";
    cin >> y;
    goldenNumber = (y % 19) + 1;
    //
    c = floor((y / 100) + 1);
    x = floor(((3 * c) / 4) - 12);
    z = floor(((8*c+ 5) / 25)-5);
    d = floor(((5*y)/4)-x-10);
    e = ((11*goldenNumber)+20+z-x)%30;
    if(e == 25 && goldenNumber > 11 || e == 24){ e++; }


    n = 44 - e;
    if (n < 21){ n = n + 30;} else{n = n;}
    n = n+7-((d+n)%7);
    if(n > 31){n = n-31; cout << "Easter Day is on April " << n <<"/" <<  y <<  endl;} else{cout << "Easter Day is on March " << n <<"/" << y << endl;}


    return 0;
}
