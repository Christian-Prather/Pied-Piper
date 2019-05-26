//
// Created by Christian on 5/2/2019.
//


// Helper function prototypes

#ifndef FINAL_HELPERFUNCTIONS_H
#define FINAL_HELPERFUNCTIONS_H

// Using the filestream library
#include <fstream>
using namespace std;

// Pre compressor
int preCompress(ifstream &sourceFile, ofstream &compressedFile);

// Meat of programm
void middleOut(bool precompression,  ifstream &sourceFile, ofstream &compressedFile);

// Actual copressor function
int compressor(ifstream &sourceFile, ofstream &compressedFile, ofstream &mapper);

// mapper.pra generator
void mapGenerator(ofstream &mapper);

// Function for decmopression of file
void decompress(string folderName);

// Fucntion for setting up file streams
void initalizeFiles(ifstream &loadFile, ofstream &compressedFile, ofstream &mapper, string folderName, string fileName);

// Main menu GUI
int mainMenu(ifstream &loadFile, ofstream &compressedFile, ofstream &mapper);


#endif //FINAL_HELPERFUNCTIONS_H
