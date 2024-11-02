#ifndef HANGMAN_H
#define HANGMAN_H

#include <algorithm>
#include <iostream>
#include <string>

using std::string;

int startHangmanGame();

class Hangman {
public:
    Hangman(const string& word) : word(word), wordCopy(word) {
        emptyWordCopy();
        maxLetters = word.length();
    }

    void emptyWordCopy() {
        std::fill(wordCopy.begin(), wordCopy.end(), '_');
    }

    int guessLetter(string& guess) {
        // Return meanings:
        // -1: Incorrect guess
        // 0: Correct guess
        // -2: Game won

        bool foundLetter = false;

        // Erase all whitespaces
        guess.erase(std::remove_if(guess.begin(), guess.end(), [](char c) {
            return c == ' ' || c == '\t';
        }), guess.end());

        // Convert all characters to lowercase using std::transform
        std::transform(guess.begin(), guess.end(), guess.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        // If the guess is only 1 character
        if (guess.length() == 1) {
            for (size_t i = 0; i < wordCopy.length(); ++i) {
                if (wordCopy[i] == '_' && word[i] == guess[0]) {
                    wordCopy[i] = guess[0];
                    foundLetter = true;
                }
            }
        }

        // If the guess is the same length as the word
        if (guess.length() > 1 && guess == word) {
            wordCopy = word;
            return -2;
        }

        return hasWon() ? -2 : (foundLetter ? 0 : -1);
    }

    bool hasWon() {
        for(int i = 0; i < wordCopy.length(); i++) {
            if(wordCopy[i] == '_') { // If there's still a letter to guess
                return false;
            }
        }
        return true;
    }

    void displayCurrentWord() const { std::cout << wordCopy << std::endl; }
    void displayFullWord() const { std::cout << word << std::endl; }

private:
    int maxLetters;
    string wordCopy;
    const string word;
};

#endif // HANGMAN_H
