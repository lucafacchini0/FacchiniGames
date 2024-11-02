#ifndef HANGMAN_H
#define HANGMAN_H

#include <algorithm>
#include <iostream>
#include <string>

using std::string;

void startHangmanGame();

class Hangman {
public:
    Hangman(const string& word) : word(word), wordCopy(word) {
        emptyWordCopy();
        maxLetters = word.length();
    }

    void emptyWordCopy();
    int guessLetter(string& guess);
    bool hasWon();
    void displayCurrentWord() const;
    void displayFullWord() const;

private:
    int maxLetters;
    string wordCopy;
    const string word;
};

#endif // HANGMAN_H
