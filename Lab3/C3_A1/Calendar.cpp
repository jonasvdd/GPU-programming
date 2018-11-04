#include <iostream>
#include "Lib/Date.h"
#include "Lib/DayOfTheWeek.h"

static const std::string months[] = {"Januari", "Februari", "March", "April", "May", "June", "July", "August", "September", "Oktober", "November", "Decemper"};

void displayCalendar(int m, int y){
	if (m > 0 && m < NUMB_MONTHS){
		Date * datum = new Date(1, m, y);

		// Verbose output
		int dayindex = getDayIndex(datum->getDay(), datum->getMonth(), datum->getYear());
		std::cout << "\t\t" <<  months[m - 1] << ", " << y << std::endl;
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << "MON\t" << "TUE\t" << "WED\t" << "THU\t" << "FRI\t" 
					<< "SAT\t" << "SUN\t" << std::endl;
		std::cout << "---------------------------------------------------" << std::endl;
	
		// adjust the position 
		for(int i = 0; i < dayindex; i++){
			std::cout << "\t";
		}

		// print the days	
		int prevday = 0; 
		while(datum->getDay() > prevday){
			std::cout << datum->getDay() << "\t";
			dayindex++;
			prevday = datum->getDay();
			if(dayindex == NUMB_DAYS){
				std::cout << std::endl;
				dayindex = 0;
			}
			datum->add(1);
		}
		std::cout << std::endl;
		std::cout << "---------------------------------------------------\n\n" << std::endl;
		delete datum;
	}
}


int main() {
	// print calendar to the console
	displayCalendar(1, 1985);
	displayCalendar(2, 2018);
	displayCalendar(5, 1997);
	displayCalendar(2, 2016);
	return 0;
}
