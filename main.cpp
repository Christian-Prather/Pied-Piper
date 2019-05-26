/* CSCI 261 Final Project: Pied Piper
 *
 * Author: Christian Prather
 *
 * This program is a low utility file compressor specifically designed for .txt files utilizing a high level of
 * repeating words. The program is controlled through a command line interface and is ment to be a starting point
 * for more advanced file compression in the future.
 *
 * * 4/20/2019
 *
 */



// Using standard input cin and cout as well as file stream for loading and saving files
#include <iostream>
#include <fstream>
// none of that std:; nonsense
using namespace std;

// Using string and vectors
#include <string>
#include <vector>

// Using iomanip for menu and possibly progress bar
#include <iomanip>
// Word class for creating word object of commonly used words
#include "Word.h"
// Header of function prototypes
#include "HelperFunctions.h"


// Global variables for accessing the three most common words in all functions
// TODO: refactor to store these in a struct

int maxCount = 0;
string maxWord;
int secondMaxCount = 0;
string secondMaxWord;
int thirdMaxCount = 0;
string thirdMaxWord;



// Flag for telling middleOut function if its compressing or just getting ready to
bool precompress = true;

// A vector to store Word objects of all unique words seen in the txt file
vector <Word> wordList;

// Global fstream varaibles initiated later
ifstream loadFile; // Source .txt
ofstream compressedFile; // Compressed .pra
ofstream mapper; // mapper .pra



int main()
{

    // Run the main menu at least once and get user input on selection
    do
    {
        // Run main menu function
        mainMenu(loadFile, compressedFile, mapper);
    }while (mainMenu(loadFile, compressedFile, mapper) != 0); // mainMenu retuns 0 if user selects to close


    // Exit message to user
    cout << "Thanks for using Pied Piper tell Gavin Belson we say Hi" <<endl;

    // Clean exit no errors
    return 0;
}

