/**
 * @author Jonas Van Der Donckt
 */

#include "Check.h"

using namespace std;


/* ---------------------------------------------
 *                  FUNCTIONS
 * ---------------------------------------------*/
int ReadNumberOfTarget(string filename, string marker) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if(Compare(line, marker)){
                // the next line should contain the total number of target specifications withing this file
                if (getline(file, line)){
                    int numbTargets = 0;
                    try{
                        numbTargets = stoi(line); }
                    catch(...){
                        cerr << "ERROR: \n\tCouldn't successfully convert the line after: " <<
                             marker << " please check if there stands an integer \n" << endl;}
                    return numbTargets;
                }
                cerr << "ERROR: \n\tCouldn't access the line after " << marker << endl;
                return 0;
            }
        }
        cerr << "ERROR: \n\tCouldn't find the "  << marker << " string in " <<
                filename << endl;
        return 0;
    }
    cerr << "ERROR: \n\tCouldn't open the file: "  << filename << " please check that"
            "that the file's path is given relative to this .exe file" << endl;
    return 0;
}


string ReadTarget(string filename, int target) {
    //FORMAT: %[xyz]%[ext]%[delim]%[pattern1]%[pattern2]%[pattern3]%...%[EOL]
    ifstream file(filename);
    int current_target = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.length() > XYZ_length + strlen(FIELD_SEPARATOR) &&
                    line.compare(XYZ_length,strlen(FIELD_SEPARATOR), FIELD_SEPARATOR) == 0){
                current_target++;
                if (current_target == target){
                    return line;
                }
            }
        }
        cerr << "Error the defined number of specified targets in the header file "
                    "is greater than the real amount of specifications, please check:"
                        "\n\t" << filename << endl;
        return "";
    }
    cerr << "Error couldn't open file: " << filename << endl;
    return "";
}

ArrayLengthPair Separate(string text, string delimeter, int offsetIndex /* = 0 */){
    int index = 0 + offsetIndex, currentLength = 0;
    ArrayLengthPair splitTextPair;

    //special case: if the array is only contains the separation char
    if(text == delimeter){
        splitTextPair.length = 1;
        splitTextPair.array[0] = "";
        return splitTextPair;
    }

    splitTextPair.array[index - offsetIndex] = Split(text, delimeter, index);
    while(splitTextPair.array[index - offsetIndex] != ""){
        index++;
        splitTextPair.array[index - offsetIndex] = Split(text, delimeter, index);
    }
    splitTextPair.length = index - offsetIndex;
    return splitTextPair;
}


bool MatchFileToTarget(string filename, string target_spec) {
    //FORMAT: [xyz]%[ext]%[delim]%[pattern1]%[pattern2]%[pattern3]%...%[EOL]
    /** listing of all priorities (HIGH TO LOW)
     *  1. ALTERNATIVE_SEPARATOR ( |  has a greater priority than %)
     *  2. FIELD SEPARATOR (%)
     *  3. MULTIPLE_CHAR_PLACEHOLDER (*)
     *  4. SINGLE_CHAR_PLACEHOLDER (?)
     */
    ArrayLengthPair alternativesArray = Separate(target_spec, ALTERNATIVE_SEPARATOR);
    if(alternativesArray.length > 0){
        string ext = Split(alternativesArray.array[0], FIELD_SEPARATOR, EXT_SUBSTRING_INDEX);
        // we assume that extensions do not contain wildcards or alternative markers
        string delim = Split(alternativesArray.array[0], FIELD_SEPARATOR, DELIM_SUBSTRING_INDEX);
        if(EndsWith(&filename[0], &ext[0])){
            for(int separatorIndex =0; separatorIndex < alternativesArray.length; separatorIndex++){
                ArrayLengthPair patterns;
                if(separatorIndex == 0){
                    // special case since we have the ext and delim clutter in this string
                    // therefore we need an offset to remove this.
                    patterns = Separate(alternativesArray.array[separatorIndex], FIELD_SEPARATOR, FIRST_PATTERN_INDEX);
                }
                else{
                    patterns = Separate(alternativesArray.array[separatorIndex], FIELD_SEPARATOR);
                }

                // make 1 big string with the patterns by concatenating the delimeter string
                string patternString;
                for(int patternIndex =0; patternIndex < patterns.length; patternIndex++){
                    patternString += patterns.array[patternIndex] + delim;
                }  // remove the last delimeter
                patternString = patternString.substr(0, patternString.length() - delim.length());

                // split the pattern string up in multiple char placeholders.
                ArrayLengthPair multipleCharArray = Separate(patternString, MULTIPLE_CHAR_PLACEHOLDER);
                string rawFileName = filename.substr(0, filename.length() - ext.length());
                unsigned int rawFileNameIndex = 0;

                // iterate over the multiple char array
                for(int multipleCharIndex =0; multipleCharIndex < multipleCharArray.length; multipleCharIndex++){
                    ArrayLengthPair singleCharArray = Separate(multipleCharArray.array[multipleCharIndex], SINGLE_CHAR_PLACEHOLDER);

                    for(int singleCharInd = 0; singleCharInd < singleCharArray.length; singleCharInd++){
                        string pattern = singleCharArray.array[singleCharInd];
                        // the pattern string is now splitted by the multiple char delimiter and the single char delimiter afterwards.
                        if(Compare(pattern, filename.substr(rawFileNameIndex, pattern.length()))){
                            rawFileNameIndex = pattern.length() + 1; // +1 because splitted on SINGLE_CHAR_PLACEHOLDER
                        } else{
                            if(separatorIndex == alternativesArray.length - 1){
                                return false;
                            }
                        }
                    }
                    if(rawFileNameIndex <= rawFileName.length()){
                        string firstPattern = Split(rawFileName.substr(rawFileNameIndex), SINGLE_CHAR_PLACEHOLDER, 0);
                        //now we have to match the first pattern to the rest of the pattern
                        for(unsigned int rawindex = rawFileNameIndex; rawindex <= rawFileName.length() - firstPattern.length(); rawindex++){
                            if(rawindex > rawFileName.length() - firstPattern.length()){
                                return  false;
                            }
                            if(Compare(firstPattern, rawFileName.substr(rawindex, firstPattern.length()))){
                                rawFileNameIndex = rawindex;
                                break;
                            }
                        }
                    } else{
                        return true;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

FileInformationArray ExtractZip(char *zipFileName) {
    unsigned int numberOfFiles = GetNumberOfFiles(zipFileName);
    FileInformationArray fileInfArr;
    fileInfArr.length = numberOfFiles;
    for (unsigned int index = 0; index < numberOfFiles; index++) {

        // split te directories so you just get the file names
        string filename = GetFilenameFrom(zipFileName, index);
        ArrayLengthPair fileDirSplittedArr = Separate(filename, DIRECTORY_SEPARATOR);

        FileInformation fileinfo;
        fileinfo.filename = fileDirSplittedArr.array[fileDirSplittedArr.length - 1];
        fileinfo.fileSize = GetFilesizeFrom(zipFileName, index);
        fileInfArr.informationArray[index] = fileinfo;
    }
    return fileInfArr;
}