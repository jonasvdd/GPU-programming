#include <iostream>
#include "../Lib/Date.h"
#include <assert.h>
#include <memory>


using namespace std;

/* ---------------------------------------------
 *                  PROTOTYPES
 * ---------------------------------------------*/
void testAddandSub();
void testSetters();
void testConstructors();


int main(){
    testAddandSub();
    testSetters();
    testConstructors();
    return 0;
}

void testAddandSub(){
    std::cout << "-------------------\nTesting Add and Sub\n"
        "--------------------"<< std::endl;

    Date * testDate1 = new Date();
    assert(testDate1->getDay() ==1);
    assert(testDate1->getMonth() == 1);
    assert(testDate1->getYear() == 1900);
    testDate1->displayDate();
    std::cout << std::endl;

    testDate1->setDate(12, 5, 1997);
    testDate1->displayDate();
    testDate1->add(7600);    // 3/3/2018
    testDate1->displayDate();
    assert(testDate1->getDay() == 3);
    assert(testDate1->getMonth() == 3);
    assert(testDate1->getYear() == 2018);
    testDate1->sub(7600);
    assert(testDate1->getDay() == 12);
    assert(testDate1->getMonth() == 5);
    assert(testDate1->getYear() == 1997);
    testDate1->displayDate();
    std::cout << std::endl;

    testDate1->setDate(12, 5, 1997);
    testDate1->add(137);     // 26/9/1997
    assert(testDate1->getDay() == 26);
    assert(testDate1->getMonth() == 9);
    assert(testDate1->getYear() == 1997);
    testDate1->displayDate();
    testDate1->sub(137);
    assert(testDate1->getDay() == 12);
    assert(testDate1->getMonth() == 5);
    assert(testDate1->getYear() == 1997);
    testDate1->displayDate();
    std::cout << std::endl;

    
    testDate1->setDate(12, 5, 1997);
    testDate1->displayDate();
    testDate1->add(31);
    assert(testDate1->getDay() == 12);
    assert(testDate1->getMonth() == 6);
    assert(testDate1->getYear() == 1997);
    testDate1->displayDate();
    testDate1->sub(31);
    assert(testDate1->getDay() == 12);
    assert(testDate1->getMonth() == 5);
    assert(testDate1->getYear() == 1997);
    testDate1->displayDate();
    std::cout << std::endl;
    
    delete testDate1;
}

    

void testSetters(){
    std::cout << "-------------------\nTesting Setters\n"
     "--------------------"<< std::endl;
    Date * testDate1 = new Date(12, 5, 1997);
    assert(testDate1->setDay(32)==false);
    assert(testDate1->setDay(0) == false);
    assert(testDate1->setDay(30) == true);
    assert(testDate1->setYear(1889) == false);
    assert(testDate1->setYear(2016) == true);
    assert(testDate1->setMonth(0) == false);
    assert(testDate1->setMonth(13) == false);
    assert(testDate1->setMonth(12) == true);
    assert(testDate1->setMonth(2) == false);    // leap year (only 29 days in that month, while current day-member = 30) 
    assert(testDate1->setDay(29) == true);      // still in december 
    assert(testDate1->setMonth(2) == true);     // now we can set the date frebrauri. 
    delete testDate1;
}

void testConstructors(){
    std::cout << "-------------------\nTesting Constructors\n"
     "--------------------"<< std::endl;
    Date * testDate1 = new Date(0, 5, 1997);
    testDate1->displayDate();
    assert(testDate1->getDay() ==1);
    assert(testDate1->getMonth() == 1);
    assert(testDate1->getYear() == 1900);
    delete testDate1;

    Date * testDate2 = new Date(12, 13, 1997);
    testDate2->displayDate();
    assert(testDate2->getDay() ==1);
    assert(testDate2->getMonth() == 1);
    assert(testDate2->getYear() == 1900);
    delete testDate2;

    Date * testDate3 = new Date(12, 5, 1899);
    testDate3->displayDate();
    assert(testDate3->getDay() ==1);
    assert(testDate3->getMonth() == 1);
    assert(testDate3->getYear() == 1900);
    delete testDate3;


    Date * testDate4 = new Date(12, -1, 1899);
    testDate4->displayDate();
    assert(testDate4->getDay() ==1);
    assert(testDate4->getMonth() == 1);
    assert(testDate4->getYear() == 1900);
    delete testDate4;
    
    Date * testDate5 = new Date(32, 5, 1899);
    testDate5->displayDate();
    assert(testDate5->getDay() ==1);
    assert(testDate5->getMonth() == 1);
    assert(testDate5->getYear() == 1900);
    delete testDate5;

    Date * testDate6 = new Date(29, 2, 2020);
    testDate6->displayDate();
    assert(testDate6->getDay() ==29);
    assert(testDate6->getMonth() == 2);
    assert(testDate6->getYear() == 2020);
    delete testDate6;

    Date * testDate7 = new Date(29, 2, 2000);
    testDate7->displayDate();
    assert(testDate7->getDay() ==29);
    assert(testDate7->getMonth() == 2);
    assert(testDate7->getYear() == 2000);
    delete testDate7;

    Date * testDate8 = new Date(29, 2, 2100);
    testDate8->displayDate();
    assert(testDate8->getDay() ==1);
    assert(testDate8->getMonth() == 1);
    assert(testDate8->getYear() == 1900);
    delete testDate8;
}