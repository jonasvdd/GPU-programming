/**
 * @author Jonas Van Der Donckt
 */

/* ---------------------------------------------
 *                  LIBRARIES
 * ---------------------------------------------*/
#include "Name.h"

/* ---------------------------------------------
 *                  FUNCTIONS
 * ---------------------------------------------*/
string ReadName(string filename){
    ifstream file(filename);
    string line;
    if (file.is_open()){
        getline(file, line);
        return line;
    }
    cerr << "Error: couldn't open the file: " << filename << "\n\t" <<
               "please check that the file exists";
    return line;
}

