//
// Created by Christian on 5/2/2019.
//


// Word class for structuring all words in the source file
#include "Word.h"

// Getter for private word
string Word::getWord()
{
    return _word;
}

// Used to set word after construction (not used in this program due to constructor)
void Word::setWord(string word)
{
    _word = word;
}

// Fucntion for returnign frequency count of individual word
int Word::getFrequency()
{
    return _frequency;
}

// Fucntion for modifying the frequency count of a given word
void Word::setFrequency(int frequency)
{
    _frequency = frequency;
}

// Unused getters and setter fro individual word length wound up not needing it but left in incase it was usful down the
// road

//int Word::getLength()
//{
//    return  _length;
//}
//void Word::setLength(int length)
//{
//    _length = length;
//}

// Default constuctor of word object
Word::Word(string word, int frequency)
{
    _word = word;
    //_length = length;
    _frequency = frequency;
}