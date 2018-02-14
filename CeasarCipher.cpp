/*
 * File: CeasarCipher.cpp
 * 
 * Author: Joe Runser
 * Created: 29 November 2017
 * Updated: 07 December 2017
 * 
 * Purpose: Use a ceasar Ciper to encript and decript text files.
 * 
 * Command structure "MP4.exe -e KEY input.txt output.txt"
 * -e Encript the text file.
 * -d Decript the text file.
 */


#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Function declarations.
void haltProgram();
char encipher(char key, char plain);
char decipher(char key, char cipher);
int charToInt(char c);
char intToChar(int a);

int main(int argc, const char * argv[]) {
    
    const int NUM_ARGS = 5;
    
    ifstream inputFileStream;
    ofstream outputFileStream;
    
    char currentLetter;
    
    string key;
    int count;
    
    // Check for correct number of arguments.
    if(argc != NUM_ARGS) {
        cout << "Error - Invalid arguments." << endl;
        exit(1);
    }
    
    key = argv[2];
    
    // Open the input file.
    inputFileStream.open(argv[3]);
    if(inputFileStream.fail()) {
        cout << "Error - Cannot open " << argv[3] << endl;
        exit(3);
    }
    
    // Create the ouput file.
    outputFileStream.open(argv[4]);
    if(outputFileStream.fail()) {
        cout << "Error - Cannot create " << argv[4] << endl;
        exit(3);
    }
    // Decode.
    if(argv[1][1] == 'd' || argv[1][1] == 'D') {
        count = 0;
        while (inputFileStream.get(currentLetter)) {
            outputFileStream.put(decipher(key[count], currentLetter));
            count = (count + 1) % key.length();
        }
        cout << "Decode" << endl;
    }
    // Encode.
    else if(argv[1][1] == 'e' || argv[1][1] == 'E') {
        count = 0;
        while (inputFileStream.get(currentLetter)) {
            outputFileStream.put(encipher(key[count], currentLetter));
            count = (count + 1) % key.length();
        }
        cout << "Encode" << endl;
    }
    
    // Improper flag.
    else {
        cout << "Error - Please declare weather the file should be decoded or encoded.";
        exit(2);
    }
    
    // Close the streams so there is no accidental access.
    inputFileStream.close();
    outputFileStream.close();
    
    cout << "Input File: " << argv[3] << endl;
    cout << "Ouput File: " << argv[4] << endl;
    cout << "       Key: " << key     << endl;
    return 0;
}

/*
 * haltProgram
 * 
 * Pauses the software and waits for an input before continuing.
*/
void haltProgram() {
    // halt the program
    cout << "Press any key to continue...";
    cin.get();
}

/*
 * enciper
 * 
 * char key: The key letter that is used to encript the plane charecter.
 * char plain: The charecter to be encripted.
 * 
 * Enciper a charecter based on a key using a Ceasar Cipher encription type.
 * 
 * Output: A charecter that has been encipted.
 */
char encipher(char key, char plain) {
    const int NUM_CHAR = 94;
    
    int a = 0;
    
    if(plain == '\n') {
        return plain;
    }
    
    a = ((charToInt(plain)) + charToInt(key)) % NUM_CHAR;
    return intToChar(a);
}

/*
 * decipher
 * 
 * char key: The key letter that is used to decipher the ciphered charecter.
 * char cipher: The charecter to be deciphered.
 * 
 * Decipher a charecter based on a key using a Ceasar Cipher encription type.
 * 
 * Output: A charecter that has been deciphered.
 */
char decipher(char key, char cipher) {
    const int NUM_LETTERS = 94;
    int a = 0;
    
    if(cipher == '\n') {
        return cipher;
    }
    
    a = charToInt(cipher) - charToInt(key);
    if(a < 0) {
        a = NUM_LETTERS + a;
    }
    return intToChar(a);
}

/*
 * charToInt
 * 
 * char c: The charecter that needs to be convereted to an integer.
 * 
 * Converts a charecter to a integer based on readable ASCII charecters. This is
 *     a helper class for encipher and decipher.
 * 
 * Output: A integer representing a readable ASCII charecter.
 */
int charToInt(char c) {
    // Letter value 0 to 25 for key
    // 'a' being 0 and 'z' being 25
    return c - ' ';
}

/*
 * intToChar
 * 
 * int a: The integer that needs to be convereted to a character.
 * 
 * Converts a integer to a charecter based on readable ASCII charecters. This is
 *     a helper class for encipher and decipher.
 * 
 * Output: A charecter representing a readable ASCII charecter.
 */
char intToChar(int a) {
    return a + ' ';
}
