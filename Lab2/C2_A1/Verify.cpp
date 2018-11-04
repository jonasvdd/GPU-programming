/**
 * @author Jonas Van Der Donckt
 */
/* ---------------------------------------------
 *                  LIBRARIES
 * ---------------------------------------------*/
#include "Verify.h"

using namespace std;


/* ---------------------------------------------
 *                  FUNCTIONS
 * ---------------------------------------------*/
bool StartsWith(char in[], char start[]) {
    int i = 0;
    while (start[i] != NULL_TERMINATION) {
        if (in[i] != start[i]) {
            return false;
        }
        i++;
    }
    return true;
}


bool EndsWith(char in[], char end[]) {
    int in_length = strlen(in) - 1, end_length = strlen(end) - 1;

    while (in_length >= 0 && end_length >= 0) {
        if (in[in_length] != end[end_length]) {
            return false;
        }
        in_length--;
        end_length--;
    }
    return in_length >= 0;
}


string Split(string in, string delim, int splitindex) {
    unsigned int in_Index = 0, delimOccurence = 0;
    string result;

    while (delimOccurence <= splitindex && in_Index + delim.length() < in.length()) {
        if (delimOccurence == splitindex) {
            for (int i = in_Index; i < in.length(); i++) {
                if (in.compare(in_Index, delim.length() ,delim) == 0) {
                    return result;
                }
                result += in[i];
                in_Index++;
            }
        }
        if (in.compare(in_Index, delim.length() ,delim) == 0) {
            delimOccurence++;
            in_Index += delim.length();
        } else {
            in_Index++;
        }
    }
    return result;
}


string Split(char *in, char *delim, int splitindex) {
    int in_Index = 0, delimOccurence = 0;
    char *localPointer = in;    // used to change the reference through the array.
    string result;

    while (delimOccurence <= splitindex && in_Index + strlen(delim) < strlen(in)) {
        if (delimOccurence == splitindex) {
            for (int i = in_Index; i < strlen(in); i++) {
                if (strncmp(localPointer, delim, strlen(delim)) == 0) {
                    return result;
                }
                result += in[i];
                localPointer++;
                in_Index++;
            }
        }
        if (strncmp(localPointer, delim, strlen(delim)) == 0) {
            delimOccurence++;
            localPointer += strlen(delim);
            in_Index += strlen(delim);
        } else {
            in_Index++;
            localPointer++;
        }
    }
    return result;
}


bool Compare(string str1, string str2) { return str1 == str2; }


bool CompareNoCase(string str1, string str2) {
    for (char &c: str1) { c = toupper(c); }
    for (char &c: str2) { c = toupper(c); }
    return str1 == str2;
}
