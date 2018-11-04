#include "DayOfTheWeek.h"
#include <iostream>

static const std::string days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
static const int daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


int getDayIndex(int d, int m, int y){
    //https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week?
    //calculate the weekday of the first day of that year 
    int weekday = (int)((int)(2.6*11 - 0.2) + (y - 1)%100 + ((y - 1)%100)/4 + y/400- 2*(y/100))%7;

    for(int i = 1; i < m; i++){                     //calculate the  weekday of the first day of the month
        weekday = (weekday + daysPerMonth[i - 1])%NUMB_DAYS;
    }
    weekday = (weekday + d - 1)%NUMB_DAYS;          // calculate weekday of the given datum  
    return weekday;
}


std::string getDayOfWeek(int d, int m, int y){
    return days[getDayIndex(d, m,y)];
}