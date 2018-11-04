/**
 * @author Jonas Van Der Donckt
 * @brief this library contains functions whom help the verification
 * process of the target specifications
 */
#ifndef VERIFY_H
#define VERIFY_H



/* ---------------------------------------------
 *                  LIBRARIES
 * ---------------------------------------------*/
#include <cstring>
#include <string>

using namespace std;



/* ---------------------------------------------
 *                  CONSTANTS
 * ---------------------------------------------*/
#define SINGLE_CHAR_PLACEHOLDER     "?"
#define MULTIPLE_CHAR_PLACEHOLDER   "*"
#define FIELD_SEPARATOR             "%" 
#define ALTERNATIVE_SEPARATOR       "|"
#define NULL_TERMINATION            '\0'
#define DIRECTORY_SEPARATOR         "/"
#define EOL                         '\n'

#define XYZ_SUBSTRING_INDEX         0
#define EXT_SUBSTRING_INDEX         1   // EXT = EXTENSION
#define DELIM_SUBSTRING_INDEX       2
#define FIRST_PATTERN_INDEX         3
#define XYZ_length                  3

#define HEADER_MARKER               "HEADER"
#define REQUIRED_MARKER             "REQUIRED"
#define FORBIDDEN_MARKER            "FORBIDDEN"



/* ---------------------------------------------
 *                  FUNCTIONS
 * ---------------------------------------------*/
/**
 * Compares the beginning of in[] with the pattern start[]
 * @param in null terminated string
 * @param start the starting pattern, a null terminated string
 * @return true if the beginning of in[] equals start[], false otherwise
 */
bool StartsWith(char in[], char start[]);


/**
 * compares the last chars of in[] with the pattern end[]
 * @param in: a null terminated string
 * @param end the starting pattern, a null terminated string
 * @return true if the ending of in[] equals end[], false otherwise
 */
bool EndsWith(char in[], char end[]);


/**
 * Splits the string in into multiple substrings based on the delim pattern.
 * The split index argument represents the substring that will be returned.
 * @param in the input char* that will be split
 * @param delim  the delimeter pattern
 * @param splitindex the splitted substring that will be returned (starts at 0)
 * @return the substring. if the split index > total number of substrings;
 * an empty string will be returned.
 */
string Split(string in, string delim, int splitindex);


/**
 * Splits the char *in into multiple substrings based on the *delim pattern.
 * The splitindex argument represents the substring that will be returned.
 * @param in the input char* that will be split
 * @param delim  the delimeter pattern
 * @param splitindex the splitted substring that will be returned (starts at 0)
 * @return the substring. if the splitindex > total number of substrings;
 * an empty string will be returned.
 */
string Split(char *in, char *delim, int splitindex);


/**
 * compares 2 case sensitive strings
 * @param str1 string2
 * @param str2 string1
 * @return true if both strings are equal, false otherwise
 */
bool Compare(string str1, string str2);


/**
 * compares 2 case insensitive strings
 * @param str1 string2
 * @param str2 string1
 * @return true if both strings are equal, false otherwise
 */
bool CompareNoCase(string str1, string str2);

#endif
