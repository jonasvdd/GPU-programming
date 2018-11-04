/**
 * @author Jonas Van Der Donckt
 * @brief This library contains functions whom help can do operations on 
 *  zip files.
 */
#ifndef ZIP_INFO_H
#define ZIP_INFO_H



/* ---------------------------------------------
 *                  LIBRARIES
 * ---------------------------------------------*/
#include <string>
#include <vector>
#include <stdio.h>
#include <cstring>


#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#define strncpy_s(dest, destsize, src, size) ((strncpy(dest, src, size)))
#endif

// won't explain these since I haven't implemented them
extern unsigned int GetNumberOfFiles(const char* zipfilename);
extern char* GetFilenameFrom(const char* zipfilename, unsigned int index);
extern unsigned int GetFilesizeFrom(const char* zipfilename, unsigned int index);

#endif // ZIP_INFO_H