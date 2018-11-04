/* ---------------------------------------------
 *                  LIBRARIES
 * ---------------------------------------------*/
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

/* Jonas Van Der Donckt */


/* ---------------------------------------------
 *                  CONSTANTS
 * ---------------------------------------------*/
#define ALIVE           "*"
#define DEAD            "."
#define SEPARATOR       " "
#define CARRIAGE_RETURN '\r'

#define ROW_INDEX   0
#define COL_INDEX   1
#define MIN_X       0
#define MIN_Y       0

#define AUTOTESTGAME    true //Change to false if you want to give manual input
#define TESTFILE        "Oscill.in"
#define TEST_NUMB_GEN   15
//  https://upload.wikimedia.org/wikipedia/commons/f/fb/I-Column.gif?1519683964799


/* ---------------------------------------------
 *                  PROTOYPES
 * ---------------------------------------------*/
void printLife1(const bool *board, int nRows, int nCols);
void printLife2(bool **board, int nRows, int nCols);
void playLife1(const bool *board, int nRows, int nCols, bool *board2);
bool **playLife2(bool **board, int nRows, int nCols);
string Split(string in, string delim, int splitIndex);



/* ---------------------------------------------
 *                  MAIN METHOD
 * ---------------------------------------------*/
int main() {
    //life board dimensions
    int numRows = 0, numCols = 0;
    string myFile;

    int numbGenerations = 0;
    if (AUTOTESTGAME) {
        myFile = TESTFILE;
        numbGenerations = TEST_NUMB_GEN;
    } else {
        cout << "Please enter your file name: ";
        getline(cin, myFile);  // such as "../../file.txt"

        // retrieve the amount of generations
        string strGenerations;
        cout << "Please enter the number of generations: ";
        getline(cin, strGenerations);
        try {
            numbGenerations = stoi(strGenerations);
        } catch (...) {
            cerr << "Error:\t\nCouldn't convert the input to an integer! Quitting ..." << endl;
            exit(1);
        }
    }

    // check if the file exists
    ifstream inputFile(myFile.c_str(), ios::in);
    if (!inputFile) {
        cerr << "File could not be opened, make sure that you've given"
                " the data path relative to the executable or the "
                "absolute path" << endl;
        exit(1);
    }

    // retrieve the dimensions from the file
    string line;
    if (getline(inputFile, line)) {
        try {
            numRows = stoi(Split(line, SEPARATOR, ROW_INDEX));
            numCols = stoi(Split(line, SEPARATOR, COL_INDEX));
        } catch (...) {
            cerr << "Couldn't convert the first line of the input "
                    "file  into the # of rows/columns" << endl;
            exit(1);
        }
    }

    // case 1: 1D array
    bool *board1D = new bool[numCols * numRows];

    // case 2: Dynamic array
    bool **board2D;
    board2D = new bool *[numRows];
    for (int row = 0; row < numRows; row++) {
        board2D[row] = new bool[numCols];
    }

    // read the input and put in both boards
    for (unsigned int row = 0; row < numRows; row++) {
        if (getline(inputFile, line)) {
            for (unsigned int col = 0; col < numCols; col++) {
                string status = Split(line, SEPARATOR, col);
                if (status == ALIVE) {
                    board1D[row * numCols + col] = true;
                    board2D[row][col] = true;

                } else if (status == DEAD) {
                    board1D[row * numCols + col] = false;
                    board2D[row][col] = false;
                } else {
                    cerr << "ERROR:\n\tThe status of (" << row << ", " << col <<
                         ") = " << status << " doesn't match the input" << endl;
                }
            }
        } else {
            cerr << "ERROR\n\t: the number of specified rows is greater than"
                    " the amount of lines in the file" << endl;
            exit(1);
        }
    }

    /*****************************************************************
    *                       PLAY LIFE 1
    ****************************************************************/
    std::cout << "Original situation:" << std::endl;
    printLife1(board1D, numRows, numCols);
    auto *board1New = new bool[numCols * numRows];  //todo clean this up
    for (int generation = 0; generation < numbGenerations; ++generation) {
        cout << "generation " << generation + 1 << " :" << endl;
        playLife1(board1D, numRows, numCols, board1New);
        printLife1(board1New, numRows, numCols);
        delete[](board1D);  //todo check if this is correct
        board1D = new bool[numRows * numCols];
        std::copy(board1New, board1New + numRows * numCols, board1D);
    }

    cout << "\n==========================\n\tChanging to part 2\n"
            "==========================\n" << endl;

    /*****************************************************************
    *                       PLAY LIFE 2
    ****************************************************************/
    std::cout << "Original situation:" << std::endl;
    printLife2(board2D, numRows, numCols);
    for (int generation = 0; generation < numbGenerations; ++generation) {
        cout << "generation " << generation + 1 << " :" << endl;
        board2D = playLife2(board2D, numRows, numCols);
        printLife2(board2D, numRows, numCols);
    }
    return 0;
}



/* ---------------------------------------------
 *                  FUNCTIONS
 * ---------------------------------------------*/
/**
 * Prints the 1D array using pointer arithmetic
 * @param board the 1D array that contains the current situation of
 * the game (which cells are alive and which aren't)
 * @param nRows the number of rows
 * @param nCols the number of columns
 */
void printLife1(const bool *board, int nRows, int nCols) {
    const bool *localPointer = board;
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            if (*localPointer) {
                std::cout << ALIVE << " ";
            } else {
                std::cout << DEAD << " ";
            }
            localPointer++;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


/**
 * Calculates the next generation using the current *board generation
 * @param board the current generation
 * @param nRows the number of rows
 * @param nCols the number of columns
 * @param board2 this 1D array is used to store the new generation in.
 */
void playLife1(const bool *board, int nRows, int nCols, bool *board2) {
    const bool *board1Pointer = board;
    bool *board2Pointer = board2;

    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            // calculate the number of alive cells.
            int min_x = (col == MIN_X) ? MIN_X : col - 1;
            int min_y = (row == MIN_Y) ? MIN_Y : row - 1;
            int max_x = (col == nCols - 1) ? col : col + 1;
            int max_y = (row == nRows - 1) ? row : row + 1;

            int numb_alive = 0;
            bool prevAlive = false;
            for (int y = min_y; y <= max_y; ++y) {
                for (int x = min_x; x <= max_x; ++x) {
                    bool isAlive = *(board1Pointer + y * nCols + x);
                    if (col == x && row == y) {
                        prevAlive = isAlive;
                    } else if (isAlive) {
                        numb_alive++;
                    }
                }
            }

            bool alive = false;
            if (numb_alive == 3 || numb_alive == 2 && prevAlive) {
                alive = true;
            }
            board2Pointer[0] = alive;
            board2Pointer++;
        }
    }
}


/**
 * Prints the life based on a dynamically allocated 2D array
 * @param board the dynamic 2D array
 * @param nRows the number of rows
 * @param nCols the number of columns
 */
void printLife2(bool **board, int nRows, int nCols) {
    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            if (board[row][col]) {
                std::cout << ALIVE << " ";
            } else {
                std::cout << DEAD << " ";
            }
        }
        std::cout << std::endl;
    }
}


/**
 * Calculates a new generation, base on the current generation (= board)
 * @param board the current generation, stored in a 2D dynamically allocated array
 * @param nRows the number of rows
 * @param nCols the number of columns
 * @return a (new) dynamic 2D array that contains the the new generation information.
 */
bool **playLife2(bool **board, int nRows, int nCols) {
    bool **newBoard;
    newBoard = new bool *[nRows];
    for (int row = 0; row < nRows; row++) {
        newBoard[row] = new bool[nCols];
    }

    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            // calculate the number of alive cells.
            int min_x = (col == MIN_X) ? MIN_X : col - 1;
            int min_y = (row == MIN_Y) ? MIN_Y : row - 1;
            int max_x = (col == nCols - 1) ? col : col + 1;
            int max_y = (row == nRows - 1) ? row : row + 1;

            int numb_alive = 0;
            bool prevAlive = false;
            for (int y = min_y; y <= max_y; ++y) {
                for (int x = min_x; x <= max_x; ++x) {
                    if (col == x && row == y) {
                        prevAlive = board[y][x];
                    }
                    if (board[y][x] && (y != row || x != col)) {
                        numb_alive++;
                    }
                }

                // the game of life conditions.
                if (numb_alive == 3 || numb_alive == 2 && prevAlive) {
                    newBoard[row][col] = true;
                } else {
                    newBoard[row][col] = false;
                }
            }
        }
    }
    // deleting the prev board situation
    for (int row = 0; row < nRows; ++row) {
        delete board[row];
    }
    delete[] board;
    return newBoard;
}


/**
 * Splits the string in into parts based on the delimiter string. the n-th (= splitindex)
 * substring will be returned.
 * @param in The input string that will be splitted.
 * @param delim the splitting pattern delimiter
 * @param splitIndex the index of the substring that will be returned
 * @return the corresponding substring
 */
string Split(string in, string delim, int splitIndex) {
    unsigned int in_Index = 0, delimOccurence = 0;
    string result;

    while (delimOccurence <= splitIndex && in_Index + delim.length() <= in.length()) {
        if (delimOccurence == splitIndex) {
            for (int i = in_Index; i < in.length(); i++) {
                if (in.compare(in_Index, delim.length(), delim) == 0) {
                    return result;
                }
                result += in[i];
                in_Index++;
            }
        }
        if (in.compare(in_Index, delim.length(), delim) == 0) {
            delimOccurence++;
            in_Index += delim.length();
        } else {
            in_Index++;
        }
    }
    if (!result.empty() && result.back() == CARRIAGE_RETURN) {
        result = result.substr(0, result.length() - 1);
    }
    return result;
}
