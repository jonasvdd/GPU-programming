#include <iostream>

#define len(arr) (sizeof(arr)/sizeof(arr[0]))
#define MOST_COMMON_CHAR  'E'

//Jonas Van Der Donckt

using namespace std;

char max_frequency (const char str[]);
void rotate (char str[], int rotDist);

int main() {
    string line, fullText = "";
    while (getline(cin, line)) {
        fullText.append(line + "\n", 0, line.length() + 1);
    }
    char* cipher = (char*) fullText.c_str();
    char freqChar = max_frequency(cipher);
    rotate(cipher, MOST_COMMON_CHAR - freqChar);
    return 0;
}

/**
 * Returns the alphabetic uppercase char that occurs the most. 
 */
char max_frequency (const char str[]) {
    string alphabeticUpperString = "";      // $ str | grep "[a-zA-z]" | tr '[:lower:]' '[:upper:]'
    int i = 0;
    while(str[i] != 0){
        char c = str[i];
        if(isalpha(str[i])){
            alphabeticUpperString += toupper(c);
        }
        i++;
    }

    int freq_arr['Z' - 'A' + 1] = {}; 
    for (int i = 0; i < alphabeticUpperString.length(); i++){
        char c = alphabeticUpperString[i] - 'A';
        freq_arr[c]+= 1;
    }

    // determine maximum frequency
    int max = 0;
    char max_freq_char = 0;
    for (char j = 0; j < len(freq_arr); j++){
        if (freq_arr[j] > max){
            max = freq_arr[j];
            max_freq_char = j;
        }
    }
    max_freq_char += 'A';
    cout << "max freq is: " << max_freq_char << endl;
    return max_freq_char;
}


void rotate (char str[], int rotDist) {
    // makes sure that the rotation distance is positive
    if (rotDist < 0){ rotDist += 'Z' - 'A' + 1; }
    cout << "\n----------- \nrotDist: " << rotDist  << "\n----------- \n"<< endl;

    // rotates and prints to the console
    int i = 0;
    while(str[i] != 0){
        if(isalpha(str[i]) && islower(str[i])){
            str[i] = 'a' + (str[i] - 'a' + rotDist)%('z'-'a' + 1);
        }
        else if(isalpha(str[i]) && isupper(str[i])){
            str[i] = 'A' + (str[i] - 'A' + rotDist)%('Z'-'A' + 1);
        }
        cout << str[i];
        i++;
    }
}
