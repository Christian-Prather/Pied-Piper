//
// Created by Christian on 5/2/2019.
//

// Word header for word class

#ifndef FINAL_WORD_H
#define FINAL_WORD_H

// Using strings
#include <string>
using  namespace std;

// Class named Word
class Word
{

// Declaration of my private variable fr each object
private:
    // Word name as strign, frequency count, and unused length of word
    string _word;
    int _frequency;
  //  int _length;

// Getters and setters
public:

    // Default Constructor
    Word(string word, int frequency);

    // Functions for manipulation the word name
    string getWord();
    void setWord(string word);

    // Funcions for manipulting the word frequency
    int getFrequency();
    void setFrequency(int frequency);

  //  ing getLength();
  //  void setLength(int length);


};


#endif //FINAL_WORD_H
