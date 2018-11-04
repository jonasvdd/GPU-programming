/**
 * @author Jonas Van Der Donckt
 * @brief this library contains functions whom operate on the .txt file
 * which contains the name of the applicant.
 */
#ifndef NAME_H
#define NAME_H

/* ---------------------------------------------
 *                  LIBRARIES
 * ---------------------------------------------*/
#include <fstream>
#include <iostream>

using namespace std;

/* ---------------------------------------------
 *                  FUNCTIONS
 * ---------------------------------------------*/
/**
 * Opens the file filename, reads the first line and returns it
 * @param filename the name of the file that will be opened
 * @return the first line if the file exists/ if the file doesn't
 * exist/ is empty returns empty string
 */
string ReadName(string filename);

#endif
