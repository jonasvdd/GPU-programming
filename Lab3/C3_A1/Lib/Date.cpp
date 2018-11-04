#include "Date.h"
#include <iomanip>
#include <iostream>


/* ---------------------------------------------
 *                DATA MEMBERS
 * ---------------------------------------------*/
static const unsigned int dayspermonthData[]  = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const unsigned int * Date::daysPerMonth = dayspermonthData;


/* ---------------------------------------------
 *                  PRIVATE
 * ---------------------------------------------*/
bool Date::checkIfLeapYear(int y) const {
    return (y % 400 == 0) || (y % 100 != 0 && y % 4 == 0);
}

void Date::setDfltDate(){
    this->m_year = DFLT_YEAR;
    this->m_month = DFLT_MONTH;
    this->m_day = DFLT_DAY;
}


/* ---------------------------------------------
 *                 PUBLIC
 * ---------------------------------------------*/
Date::Date() {
    setDfltDate();
}

Date::Date(int d, int m, int y) {
    if (!setDate(d, m, y)) {
        setDfltDate();
    }
}

Date::Date(const Date &d){
    m_year = d.m_year;
    m_month = d.m_month;
    m_day = d.m_day;
}

Date::~Date() {
    /**
     * I only need to delete elements on the heap (and not elements
     * on the stack, nor static members) so I will do nothing! 
     **/
}

Date & Date::operator=(const Date & other){
    if(&other != this){
        setDate(other.getDay(), other.getMonth(), other.getYear());
    }
    return * this;
}


/* ---------------------------------------------
*                  GETTERS
* ---------------------------------------------*/
//this const marks that no class members variables will be changed
int Date::getDay() const { return m_day; }
int Date::getMonth() const { return m_month; }
int Date::getYear() const { return m_year; }


/* ---------------------------------------------
*                  SETTERS
* ---------------------------------------------*/
bool Date::setDay(int d) { return setDate(d, this->m_month, this->m_year);}
bool Date::setMonth(int m) { return setDate(this->m_day, m, this->m_year); }
bool Date::setYear(int y) {return setDate(this->m_day, this->m_month, y);}


bool Date::setDate(int d, int m, int y) {
    if (y >= DFLT_YEAR && 0 < m && m <= NUMB_MONTHS) {
        unsigned int numb_bonus_days = 0;
        if (m == LEAP_MONTH && checkIfLeapYear(y)) { numb_bonus_days++; }
        if (0 < d && d <= daysPerMonth[m - 1] + numb_bonus_days) {
            this->m_day = d;
            this->m_month = m;
            this->m_year = y;
            return true;
        }
        return false;
    }
}


bool Date::equals(Date const &date) const {
    return this->m_year == date.m_year && this->m_month == date.m_month &&
           this->m_day == date.m_day;
}


void Date::displayDate() const {
    std::cout << std::setfill('0') << std::setw(2) << this->m_day << "/" <<
              std::setfill('0') << std::setw(2) << this->m_month << "/" <<
              this->m_year << std::endl;
}


void Date::add(int n) {
    while(n > 0){
        unsigned int numb_bonus_days = 0;
        if (m_month == LEAP_MONTH && checkIfLeapYear(m_year)) { numb_bonus_days++; }
        unsigned int totalDaysInMonth = daysPerMonth[m_month - 1] + numb_bonus_days;

        if (n > totalDaysInMonth - m_day) {
            n -= daysPerMonth[m_month - 1] + numb_bonus_days - m_day + 1;
            this->m_day = 1;
            m_month += 1;
            if (m_month == NUMB_MONTHS + 1) {
                m_year++;
                m_month = 1;
            }
        } 
        else {
            m_day += n;
            n = 0;
        }
    }
}


void Date::sub(int n) {
    // date b4 1/1/1900 --> error message
    while (m_year >= DFLT_YEAR && n > 0) {
        if (n >= m_day) {
            n -= m_day;
            m_month--;
            if (m_month == 0) {
                m_year--;
                m_month = 12;
            }
            unsigned int numb_bonus_days = 0;
            if (m_month == LEAP_MONTH && checkIfLeapYear(m_year)) { numb_bonus_days++; }
            this->m_day = daysPerMonth[m_month - 1] + numb_bonus_days;
        } 
        else {
            this->m_day -= n;
            n = 0;
        }
    }
    if (m_year < DFLT_YEAR){
        std::cerr << "Error: it's not possible to achieve a date earlier "
            "than 01/01/1900" << std::endl;
        setDfltDate();
    }
}