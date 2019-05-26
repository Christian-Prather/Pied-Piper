//
// Created by Christian on 5/2/2019.
//

// Utilizing my helper library
#include "HelperFunctions.h"

// Using vectors, my Word class, and standard io with standard namespace
#include <vector>
#include "Word.h"
#include <iostream>
using  namespace std;

// Using strings
#include <string>

// External linkage to variables to allow helper functions to access them instead of
// passing them to ever function by reference, not sure which is better

extern bool precompress;
extern  vector<Word> wordList;
extern string maxWord;
extern int maxCount;
extern int secondMaxCount;
extern string secondMaxWord;
extern int thirdMaxCount;
extern string thirdMaxWord;


// Initalizing all if my fstreams (passed by refernce)
void initalizeFiles(ifstream &loadFile, ofstream &compressedFile, ofstream &mapper,  string folderName, string fileName)
{


    // Open a file for reading passed in by user (source .txt file)
    loadFile.open(fileName);
    // Check is opened alright, if not error out and close programm
    if (loadFile.fail())
    {
        cerr << "File not found... maybe use pipey"<< endl;
        exit(0);
    }

    // Open stream to save compressed verison of file
    // regardless of source this is called compressed.pra in folder passed in by user and contains 1,2,3 and uncompressed
    // words
    compressedFile.open(folderName + "/compressed.pra");
    // Error out if not valid path
    if (compressedFile.fail())
    {
        cerr << "Cant save file"<<endl;
        exit(0);

    }

    // Open stream to save mapping file
    // regardless of source this is called mapper.pra in folder passed in by user and contains 1,2,3 and uncompressed
    // words associated with the respective values, would like to make hidden in future
    mapper.open(folderName + "/mapper.pra");
    if (mapper.fail())
    {
        cerr << "Sad Panda"<<endl;
        exit(0);
    }


}

// Main menu Gui
int mainMenu(ifstream &loadFile, ofstream &compressedFile, ofstream &mapper)
{

    // Display user cmd line interface for selection if they want to compress or decmopress or close programm
    cout << "Welcome to Pied Piper the brand new middle out compression engine"<< endl;
    cout << "Please select what you would like to do..."<< endl;
    cout << "1) Compress File" << endl;
    cout << "2) Decompress File" <<endl;
    cout << "3) Close Program and install virus"<<endl;

    // Take in user input
    int userChoice = 0;
    cin >> userChoice;

    // Check agianst choices
    if (userChoice == 1)
    {
        // Compress File

        // If compressing take in the folder they want the .pra files stored I recommend a folder called Compressed
        cout << "Please enter the folder path to where you would like to save .pra file..." <<endl;
        string folderName;
        cin >> folderName;

        // Ask the user to enter the path to the source file they want to try and compress

        cout << "Please enter directory of file with file name..." <<endl;
        string fileName;
        cin >> fileName;


        // Initialize the fstreams based on the values passed in by the user
        initalizeFiles(loadFile, compressedFile, mapper, folderName, fileName);

        cout << endl; // Display cleanup

        // Inform the user compression is starting
        // TODO: Add progress bar
        cout << "COMPRESSING....."<<endl;

        // Parse through the file once looking for unique words and saving the top three used with corresponding single
        // byte representations
        preCompress(loadFile, compressedFile);

        // Parse through file a second time this time looking for any word matching the top three from preCompression
        // and replacing them with the single byte mapping
        compressor(loadFile, compressedFile, mapper);


    }
    else if (userChoice == 2)
    {
        // Decompress File
        // If Decompressing have user enter folder of .pra files
        cout << "Please enter the path of the folder containing the .pra mapper and compressed file"<<endl;
        string folderName;
        cin >> folderName;

        // Run decopression saving a new decmopressed file in the same folder as the main.cpp file and call it
        // Decmpressed.txt
        // TODO: Change save directory to compressed .pra folder and resave as original source file name

        decompress(folderName);

        // Inform the user its decompressing their file
        cout << endl;

        cout << "DECOMPRESSING..." <<endl;
    }
    else if (userChoice == 3)
    {
        // Close the program

        return 0;

    }
    else
    {
        // User did not select 1-3
        cerr << "Not a valid choice pick again..." <<endl;

    }
}
// Function for parsing through source for top three words
int preCompress(ifstream &sourceFile, ofstream &compressedFile)
{
    // Inform middleOut it is just parsing not saving
    precompress = true;

    // Parse file for top thre words
    middleOut(precompress, sourceFile, compressedFile);

}


// Compression primary function

int compressor(ifstream &sourceFile, ofstream &compressedFile, ofstream &mapper)

{
    // Set precompression flag to false to inform middeOut its actually compressing
    precompress = false;

    // Run middleOut function, which is in charge of actually manipulating the files
    middleOut(precompress, sourceFile, compressedFile);
    // Generate a mapper.pra file for the specific source
    mapGenerator(mapper);

    // Count all bytes from start to stop (used for determining file size)
    sourceFile.seekg(0, ios::end);
    // Assuming at end of file which we should be at this point in the code we should be given above line get current position
    float sourceEnd = sourceFile.tellg();
    // Inform user of initial file size in bytes
    cout << "Size of original is " << sourceEnd << " bytes" <<endl;

    // Run same size determination logic as above for the cmopressed file and mapper.pra
    compressedFile.seekp(0, ios::end);
    float compressedEnd = compressedFile.tellp();
    cout << "Size of compressed is " << compressedEnd << " bytes" <<endl;

    mapper.seekp(0, ios::end);
    float mapperEnd = mapper.tellp();
    cout << "Size of mapper is " << mapperEnd <<" bytes" <<endl;

    // Calculate how compressed the result is based on source size vs soze of compressed.pra + mapper.pra
    cout << "Compression percentage: " << 100 - (((compressedEnd + mapperEnd)/ sourceEnd) * 100) << "%" << endl;

    // Close all files for stream cleanup
    sourceFile.close();
    compressedFile.close();
    mapper.close();
}


// Bulk of programm handles all file manipulation
void middleOut(bool precompression,  ifstream &sourceFile, ofstream &compressedFile)
{

    // Ensure the source file is opened properly again
    if(sourceFile.fail())
    {
        cerr << "File not found... maybe use pipey"<< endl;
        exit(0);

    }

    // If just parsing logic is different than compressing
    if (precompression)
    {
        // Read each word in one at a time until at end of file
        string currentWord;

        while (!sourceFile.eof())
        {
            // Boolean for tracking if a word is in list already or not
            bool wordMatch = false;
            // Read current word
            sourceFile >> currentWord;
            // Debugging
            cout << currentWord << endl;

            // Loop through every word in the list of seen words and check if current word is a match
            for (int i = 0; i < wordList.size(); i++)
            {
                // If it matches word in list already set match flag to true and add plus one to frequency count of that
                // specific word frequency

                if (currentWord == wordList[i].getWord())
                {
                    wordMatch = true;
                    wordList[i].setFrequency((wordList[i].getFrequency()) + 1);
                }
            }

            // If matching flag was never set indicating non of the words in the vector are the current word than
            // save a new Word object using the current word as paramater for construction
            if (!wordMatch)
            {
                cout << "Adding word" << endl;
                // New word object with current word name and 1 as starting frequency
                Word newWord(currentWord, 1);

                // Add to back of word vector
                wordList.push_back(newWord);
                //Debugging
                cout << wordList.size() << endl;

            }

        }

        // For all words in the saved wordlist get top three most frequent ones and save to global variables
        for (int i = 0; i < wordList.size()-1; i++)
        {
            // Max word biggest bang for your buck
            if (wordList[i].getFrequency() > maxCount)
            {
                maxCount = wordList[i].getFrequency();
                maxWord = wordList[i].getWord();
            }

            // Second most common
            else if (wordList[i].getFrequency()> secondMaxCount)
            {
                // Store seccond most common
                secondMaxCount = wordList[i].getFrequency();
                secondMaxWord = wordList[i].getWord();

            }
            // Third most common
            else if (wordList[i].getFrequency() > thirdMaxCount)
            {
                thirdMaxCount  = wordList[i].getFrequency();
                thirdMaxWord = wordList[i].getWord();

            }
        }
    }

    // If not precompressing actually compress
    else
    {
        // Compress the file actually

        string currentWord;

        // Reload file and ensure it opens properly
        ifstream loadFile("test.txt");
        if (loadFile.fail())
        {
            cerr << "File not found... maybe use pipey"<< endl;
            exit(0);
        }

        // Read every word in source one at a time and replace if matches top 3
        while (!loadFile.eof())
        {

            loadFile >> currentWord;
            // Check current char to determin when to save a new line in compressed.pra
            if (loadFile.peek() == '\n')
            {
                compressedFile << "\n";
            }

            // Check for top 3 matching words if found replace with mapping byte
            if (currentWord == maxWord)
            {
                compressedFile << " 1";

            }
            else if (currentWord == secondMaxWord)
            {
                compressedFile << " 2";
            }
            else if (currentWord == thirdMaxWord)
            {
                compressedFile << " 3";
            }

            // If the word doesnt match the top 3 simple save it as is to the compressed.pra file
            else
            {
                compressedFile << " " << currentWord;
            }
        }
    }


}

// Function for generating the mapping file used to conver between .pra file and .txt file
void mapGenerator(ofstream &mapper)
{
    const string MAX_VAL = "1";
    const string SECOND_MAX_VAL = "2";
    const string THIRD_MAX_VAL = "3";

    // Save max frequency word with 1 and so on for top 3
    mapper << maxWord << " " << MAX_VAL <<endl; // add endl when doing multiple words and dont add it for last one
    mapper << secondMaxWord << " " << SECOND_MAX_VAL <<endl;
    mapper << thirdMaxWord << " "  << THIRD_MAX_VAL;

}


// Function for handling decompression of .pra file
void decompress(string folderName)
{

    // Struct for storing the top three words and mapped bytes from the mapper.pra file
    struct topWords
    {
        string mostCommonWord = "";
        string mostCommonInt = "";

        string secondMostCommonWord = "";
        string secondMostCommonInt = "";

        string thirdMostCommonWord = "";
        string thirdMostCommonInt = "";

    };



    // Ensure mapper.pra opens and read each line at a time into two variables, this okay because I decided how mapper.pra
    // would be structured
    string currentWordMap;

    ifstream loadFile(folderName + "/mapper.pra");
    if (loadFile.fail())
    {
        cerr << "File not found... maybe use pipie"<< endl;
        exit(0);

    }

    // Build a topWords struct called wordMap
    topWords wordMap;

    // Parse mapper.pra into the struct
    while (!loadFile.eof())
    {
        loadFile >> wordMap.mostCommonWord  >> wordMap.mostCommonInt;
        cout << "End: " << wordMap.mostCommonWord << " / " << wordMap.mostCommonInt;

        loadFile >> wordMap.secondMostCommonWord  >> wordMap.secondMostCommonInt;
        cout << "End: " << wordMap.secondMostCommonWord << " / " << wordMap.secondMostCommonInt;

        loadFile >> wordMap.thirdMostCommonWord  >> wordMap.thirdMostCommonInt;
        cout << "End: " << wordMap.thirdMostCommonWord << " / " << wordMap.thirdMostCommonInt;

    }

    // File stream cleanup
    loadFile.close();

    // Open ompressed.pra file from user defined folder
    ifstream compressedFile (folderName+ "/compressed.pra");
    if (compressedFile.fail())
    {
        cerr << "Could not find compressed file, is directory correct?"<< endl;
        exit(0);

    }

    // Initiate an output filestream for the decompressed file
    ofstream decompressedFile("Decompressed.txt");
    if (decompressedFile.fail())
    {
        cerr << "Could not decompress..."<<endl;
        exit(0);

    }

    // For every word in compressed.pra see if it maps to the saved words, if so save out mapped word to decompressed file
    while (!compressedFile.eof())
    {
        compressedFile >> currentWordMap;

        // Again look for new lines in compressed.pra file
        if (compressedFile.peek() == '\n')
        {
            decompressedFile << "\n";
        }
        // If 1
        if (currentWordMap == wordMap.mostCommonInt)
        {
            cout << "Found Match";

            decompressedFile << " " << wordMap.mostCommonWord << " ";

        }

        // If 2
        else if (currentWordMap == wordMap.secondMostCommonInt)
        {
            cout << "Found second match";

            decompressedFile <<  " " << wordMap.secondMostCommonWord << " ";
        }

        // If 3
        else if (currentWordMap == wordMap.thirdMostCommonInt)
        {
            cout << "Found third";
            decompressedFile <<  " " << wordMap.thirdMostCommonWord << " ";
        }
        // Otherwise treat the read in word as an uncompressed word
        else
        {
            cout << "Not compressed word";
            decompressedFile  << currentWordMap << " ";
        }

    }

    // File stream clean up
    compressedFile.close();
    decompressedFile.close();


}


