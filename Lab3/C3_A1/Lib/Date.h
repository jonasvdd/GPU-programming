#ifndef DATE_H
#define DATE_H


/* ---------------------------------------------
 *                  CONSTANTS
 * ---------------------------------------------*/
#define DFLT_DAY  		1
#define DFLT_MONTH		1
#define DFLT_YEAR 		1900

#define NUMB_MONTHS     12
#define LEAP_MONTH      2

/* ---------------------------------------------
 *                  CLASSES
 * ---------------------------------------------*/
class Date{

private:
	int m_day;
	int m_month;
	int m_year;
	bool checkIfLeapYear(int y) const;
	void setDfltDate();
	static const unsigned int *daysPerMonth;
public:
	/**
	 * Default constructor, assigns the date to 01/01/1900 (dd/mm/yyyy)
	 */
	Date();

	/**
	 * Assigns the date to d/m/y if the input is valid and after 1/1/1900 
	 * Otherwise, the date will be default date will be assigned 01/01/1900
	 */
	Date(int d, int m, int y);

	/**
	 * Copy constructor
	 */
	Date(const Date &d);	
	
	/**
	 * Destructor
	 */
	~Date();
	
	/**
	 * Assignment operators, copies the date object instances
	 */
	Date &operator = (const Date & other);

	// Getters 
	int getDay() const;
	int getMonth() const; 
	int getYear() const;

	/**
	 * returns true and sets the value if valid, false otherwise and  
	 * the date will be resetted to the default date 01/01/1900
	 */
	bool setDay(int d);
	bool setMonth(int m);
	bool setYear(int y);
	bool setDate(int d, int m, int y);

	/**
	 * Returns true if the current object and the paramter object 
	 * represent the same date, false otherwise
	 */
	bool equals(Date const & date) const;

	void displayDate() const;

	/**
	 * Adds n number of days to the current date
	 */
	void add(int n);

	/**
	 * Subtracts n numbers of days from the current date,
	 * If the new date precedes 01/01/1900, a message will be 
	 * printed and the date will be 01/01/1900
	 */
	void sub(int n);	
};


#endif // DATE_H