#ifndef DAY_OF_THE_WEEK
#define DAY_OF_THE_WEEK

#include <math.h>
#include <string>
#include <cstring>


/* ---------------------------------------------
 *                  CONSTANTS
 * ---------------------------------------------*/
#define NUMB_DAYS 7


/* ---------------------------------------------
 *                  FUNCTIONS
 * ---------------------------------------------*/
std::string getDayOfWeek(int d, int m, int y);
int getDayIndex(int d, int m, int y);

#endif