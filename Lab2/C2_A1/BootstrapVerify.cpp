/**
 * @author Jonas Van Der Donckt
 * @brief this file contains the main function wich verifies the submission
 */


/* ---------------------------------------------
 *                  LIBRARIES
 * ---------------------------------------------*/
#include <iostream>
#include "Verify.h"
#include "Check.h"
#include "Name.h"



/* ---------------------------------------------
 *                  CONSTANTS
 * ---------------------------------------------*/
#define TOTAL_NUMB_ARGS 3
#define EXECPATHARG     0
#define ZIPFILEARG      1
#define TOKENFILE_ARG   2
#define NAMEFILE_ARG    3
#define ZIP_EXTENSION   ".zip"

using namespace std;



/* ---------------------------------------------
 *                  PROTOTYPES
 * ---------------------------------------------*/
bool CheckMatch(FileInformationArray fileInfArr, string targetSpec);
bool CheckMarker(int &targetIndex, int numMarkerTargets, string MarkerType,
                 string tokenFileName, FileInformationArray arr);
int VerifySubmission(string zipfileName, string tokenfileName, string namefileName);



/* ---------------------------------------------
 *                  PROTOTYPES
 * ---------------------------------------------*/
int main(int argc, char* argv[]) {
    if (argc - 1 == TOTAL_NUMB_ARGS) {
        return VerifySubmission(argv[ZIPFILEARG], argv[TOKENFILE_ARG], argv[NAMEFILE_ARG]);
    }
    cerr << "ERROR: \n\tThe number of arguments (= " << (argc - 1) << "does not correspond "
            "with the required amount (= " << TOTAL_NUMB_ARGS << ") of arguments. \n"
                 "quitting ..." << endl;
    return 1;
}

/**
 * Check the files against the target specification
 * @param fileInfArr a struct that contains all the info of the files
 * @param targetSpec the specification string
 * @return true if the specification string requirements are met, false otherwise
 */
bool CheckMatch(FileInformationArray fileInfArr, string targetSpec) {
    string result = Split(targetSpec, FIELD_SEPARATOR, 0);
    int numbExactMatches = 0, numbCurrentMatches = 0;

    try {
        numbExactMatches = stoi(result);
    }
    catch (...) {
        cerr << "ERROR: \n\tCouldn't convert the number of matches from the target specification"
                "\nplease check if there stands an integer" << endl;
        return false;
    }
    cout << "Target specification:\t" << targetSpec << endl;
    for (int i = 0; i < fileInfArr.length; ++i) {
        if (MatchFileToTarget(fileInfArr.informationArray[i].filename, targetSpec)) {
            cout << "MATCH found:\t" << fileInfArr.informationArray[i].filename << endl;
            numbCurrentMatches++;
        }
    }
    cout << "Total # matches:\t" << numbCurrentMatches << "\n" << endl;
    return numbCurrentMatches == numbExactMatches;
}


/**
 * Checks all the specifications for a certain marker
 * @param targetIndex the index of the current target (passed by reference)
 * @param numMarkerTargets the number of target specifications that need be checked
 * @param MarkerType the type of the specification marker (i.e. required, header, forbidden)
 * @param tokenFileName the name of the token file (where the targets specifications are located)
 * @param arr contains the information of all the files in the zip
 * @return
 */
bool CheckMarker(int &targetIndex, int numMarkerTargets, string MarkerType, string tokenFileName, FileInformationArray arr){
    /* verify the required files */
    cout << "-------------------------------------------------------" << endl;
    cout << "Number of targets specified in the " << MarkerType << " part:\n\t" <<
         numMarkerTargets << "\n" << endl;
    int totalTargets = targetIndex + numMarkerTargets;
    while (targetIndex < totalTargets ) {
        string targetSpec = ReadTarget(tokenFileName, targetIndex);
        targetIndex++;
        if (!CheckMatch(arr, targetSpec)) {
            cerr << "ERROR\n\tThe specification string:\n\t" << targetSpec <<
                 " within the " << MarkerType << " scope doesn't match" << endl;
            return false;
        }
    }
}

/*
 * Combines all the function to validate the name of the zip file and
 * each of the files that are included
 */
int VerifySubmission(string zipfileName, string tokenfileName, string namefileName) {
    FileInformationArray fileInformationArray = ExtractZip(&zipfileName[0]);
    int totalNumbTargets = ReadNumberOfTarget(tokenfileName, HEADER_MARKER);
    int targetIndex = 1;
    cout << "\nNumber of targets specified in the " << HEADER_MARKER << " part: " <<
         totalNumbTargets << endl;

    /* verify the zip name */
    string targetSpec = ReadTarget(tokenfileName, targetIndex);
    if (MatchFileToTarget(zipfileName, targetSpec)) {
        string name = ReadName(namefileName) + ZIP_EXTENSION;
        if(EndsWith(&zipfileName[0], &name[0])){
            cout << "Zip file correctly matched\n" << endl;
        }else {
            cerr << "Error the name: " << name << "doesn't match the zip name: "
                 << zipfileName << endl;
        }
        int numReqTargets = ReadNumberOfTarget(tokenfileName, REQUIRED_MARKER);
        int numbForbiddenTargets = ReadNumberOfTarget(tokenfileName, FORBIDDEN_MARKER);
        if (targetIndex + numReqTargets + numbForbiddenTargets == totalNumbTargets) {
            targetIndex++;

            if (CheckMarker(targetIndex, numReqTargets, REQUIRED_MARKER, tokenfileName,
                            fileInformationArray)){
                if(CheckMarker(targetIndex, numbForbiddenTargets, FORBIDDEN_MARKER, tokenfileName,
                               fileInformationArray)){
                    cout << "-------------------------------------------------------" << endl;
                    cout << "The zip file matches the specifications" << endl;
                    cout << "-------------------------------------------------------" << endl;
                    return 0;
                }
            }
            return 0;
        }
        cerr << "ERROR:\n\tThe number of targets specified after the " <<
             REQUIRED_MARKER << " and the " << FORBIDDEN_MARKER << " do not "
                     "correspond with the the total number of targets after the "
             << HEADER_MARKER << endl;
        return 1;
    }
    cerr << "ERROR:\n\tcouldn't match zip filename to the corresponding target "
            "specification" << endl;
    return 1;
}