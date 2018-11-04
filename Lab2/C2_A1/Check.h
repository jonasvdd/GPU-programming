/**
 * @author Jonas Van Der Donckt
 * This library contains functions to retrieve information about the target
 * specifications and match them against file names
 */
#ifndef CHECK_H
#define CHECK_H



/* ---------------------------------------------
 *                  LIBRARIES
 * ---------------------------------------------*/
#include <fstream>
#include <iostream>
#include "ZipInfo.h"
#include "Verify.h"



/* ---------------------------------------------
 *                  STRUCTS
 * ---------------------------------------------*/
/**
 * This struct contains an and array of string and their length.
 */
struct ArrayLengthPair{
    string array[256];
    unsigned int length = 0;
};

/**
 * This struct contains the name and size of a file.
 */
struct FileInformation{
    string filename;
    unsigned int fileSize;
};

/**
 * This struct contains an array of FileInformation structs
 */
struct FileInformationArray{
    FileInformation informationArray[256];
    unsigned int length = 0;
};



/* ---------------------------------------------
 *                  FUNCTIONS
 * ---------------------------------------------*/
/**
 * @param filename the name of the file (most probably check.txt)
 * @param marker The marker where from we want to know the number of specifications
 *  (most likely HEADER, REQUIRED, FORBIDDEN)
 * @return the number of target specifications to check on. If the file was unable
 * to access or the number_of_targets was not specified: information will be shown
 * in the console.
 */
int ReadNumberOfTarget(string filename, string marker);


/**
 * opens the file, reads the information until the n-th target specification
 * is reached. Afterwards
 * @param filename the name of the file (most probably Check_Cx_Ax.txt)
 * @param target the n-th target specifiation
 * @return the n-th target specification string (base 1), if no such specification
 * string is found, an empty string will be returned.
 */
string ReadTarget(string filename, int target);


/**
 * @param text the string that will be separated
 * @param delimeter the pattern which separates the string text
 * @param offsetIndex used if an offset is desired for the the string text
 * @return A struct which contains the separated substrings and number of separated substrings
 */
ArrayLengthPair Separate(string text, string delimeter, int offsetIndex = 0);


/**
 * @param filename filename string
 * @param target_spec target specification string
 * @return true if the filename matches the target specification, false otherwise.
 */
bool MatchFileToTarget(string filename, string target_spec);


/**
 * extracts all the information in the zip file.
 * @param zipFileName the name of the zipfile
 * @return returns a FileInformationArray which contains the file name and file size
 */
FileInformationArray ExtractZip(char * zipFileName);

#endif
