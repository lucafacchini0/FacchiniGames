#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>

class Hangman {
public:
    Hangman();
    void startGameLoop();
private:
    void showChooseDifficultyMenu() const;
    void printCurrentWord(const std::string& word) const;
    void startGame(const std::string& filePath, const std::string& difficultyText, const std::string& color);
};

#endif // HANGMAN_H
