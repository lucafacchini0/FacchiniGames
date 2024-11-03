#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include "colors.h"

using std::string;

class Hangman {
public:
    Hangman();
    void startGameLoop();
private:
    enum GuessResult {
        VALID_SINGLE_CHAR,
        INVALID_SINGLE_CHAR,
        INVALID_CHAR_WORD,
        ALREADY_GUESSED_CHAR,
        INCORRECT_WORD,
        CORRECT_WORD,

    };

    static void printError(const string& message);
    static void printWarning(const string& message);
    static void printSuccess(const string& message);
    static bool searchSingleChar(char guess, const string& selectedWord, string& currentWord); void showChooseDifficultyMenu() const;
    void printCurrentWord(const string& word) const;
    void startGame(const string& filePath, const string& difficultyText, const string& color);
    GuessResult validateGuess(const string& guess, string& currentWord, const string& selectedWord); // Update return type

};

#endif // HANGMAN_H
