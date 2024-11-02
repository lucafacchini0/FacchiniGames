#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include "../include/misc.h"
#include "../include/hangman.h"
#include "../include/colors.h"

using std::string;
using std::vector;

const string EASY_FILE_PATH = "../assets/hangman/easyWords.txt";
const string MEDIUM_FILE_PATH = "../assets/hangman/mediumWords.txt";
const string HARD_FILE_PATH = "../assets/hangman/hardWords.txt";

const int MAX_TRIES = 10;

// Constructor
Hangman::Hangman() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Hangman::printCurrentWord(const string& word) const {
    std::cout << word << std::endl;
}

void Hangman::showChooseDifficultyMenu() const {
    std::cout << std::endl;
    std::cout << BOLDMAGENTA << centerText("Hangman Game") << RESET << std::endl;
    std::cout << MAGENTA << centerText("Choose the difficulty:") << RESET << std::endl;
    std::cout << std::endl;
    std::cout << GREEN << "EASY [1]" << RESET << std::endl;
    std::cout << YELLOW << "MEDIUM [2]" << RESET << std::endl;
    std::cout << RED << "HARD [3]" << RESET << std::endl;
    std::cout << std::endl;
    std::cout << BLUE << "EXIT [0]" << RESET << std::endl;
    std::cout << std::endl;
}

bool isValidGuess(const string& guess, const string& currentWord, const string& selectedWord, int& triesLeft) {
    // Check if guess is a single letter and alphabetic
    if (guess.length() == 1) {
        if (!std::isalpha(guess[0])) {
            std::cout << std::endl;
            std::cout << BOLDRED << "Invalid guess." << RESET << std::endl;
            std::cout << RED << "You didn't enter a valid character." << RESET << std::endl;
            std::cout << std::endl;

            --triesLeft; // Decrement tries left for invalid character
            return false; // Invalid single letter
        }

        // Check if the letter has already been guessed
        char lowerGuess = std::tolower(guess[0]);
        if (currentWord.find(lowerGuess) != std::string::npos) {
            std::cout << std::endl;
            std::cout << BOLDYELLOW << "Invalid guess." << RESET << std::endl;
            std::cout << YELLOW << "You've already guess that letter!" << RESET << std::endl;
            std::cout << std::endl;

            return false; // Already guessed letter
        }
    } else if (guess.length() > 1) { // Handle word guesses
        // Check for invalid characters in the guess
        for (char c : guess) {
            if (!std::isalpha(c)) {
                std::cout << std::endl;
                std::cout << BOLDRED << "Invalid guess." << RESET << std::endl;
                std::cout << RED << "Your guess contains invalid characters." << RESET << std::endl;
                std::cout << std::endl;

                --triesLeft; // Decrement tries left for invalid character in word guess
                return false; // Invalid character in the guess
            }
        }
        if (guess == selectedWord) {
            return true; // Valid guess, player has guessed the word
        } else {
            std::cout << std::endl;
            std::cout << BOLDRED << "Invalid guess." << RESET << std::endl;
            std::cout << RED << "The word is incorrect." << RESET << std::endl;
            std::cout << std::endl;

            --triesLeft; // Decrement tries left for incorrect word guess
            return false; // Not a valid guess
        }
    }
    return true; // Valid guess for a single letter
}

void Hangman::startGame(const std::string &filePath, const std::string &difficultyText, const std::string &color) {
    std::ifstream wordsFile(filePath);
    if (!wordsFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    vector<string> words;
    string line;
    while (std::getline(wordsFile, line)) {
        words.push_back(line);
    }
    wordsFile.close();

    if (words.empty()) {
        std::cerr << "No words found in the file." << std::endl;
        return;
    }

    int randomWordIndex = rand() % words.size();
    string selectedWord = words[randomWordIndex];

    string currentWord(selectedWord.length(), '_');
    int triesLeft = MAX_TRIES;

    clearScreen();
    std::cout << std::endl;
    std::cout << color << difficultyText << " Game has started!" << RESET << std::endl;
    std::cout << "The word is " << BLUE << selectedWord.length() << RESET << " letters long" << std::endl;
    std::cout << std::endl;

    string currentGuess;

    while (triesLeft > 0 && currentWord != selectedWord) {
        std::cout << YELLOW << "Remaining tries: " << RESET << triesLeft << std::endl;
        printCurrentWord(currentWord);

        std::cout << "Enter your guess: ";
        std::cin >> currentGuess;
        clearScreen();

        // Validate the guess
        bool validGuess = isValidGuess(currentGuess, currentWord, selectedWord, triesLeft);

        if (validGuess) {
            if (currentGuess.length() == 1) { // Process single letter guesses
                char lowerGuess = std::tolower(currentGuess[0]); // Convert to lowercase

                bool found = false; // Reset found for each guess
                for (size_t i = 0; i < selectedWord.length(); i++) {
                    if (std::tolower(selectedWord[i]) == lowerGuess) { // Compare in lowercase
                        currentWord[i] = selectedWord[i];
                        found = true;
                    }
                }

                if (!found) {
                    std::cout << std::endl;
                    std::cout << BOLDRED << "Incorrect guess." << RESET << std::endl;
                    std::cout << RED << "The letter '" << lowerGuess << "' is not in the word." << RESET << std::endl;
                    std::cout << std::endl;
                    --triesLeft;
                } else {
                    std::cout << std::endl;
                    std::cout << BOLDGREEN << "Correct guess!" << RESET << std::endl;
                    std::cout << GREEN << "The letter '" << lowerGuess << "' is in the word." << RESET << std::endl;
                    std::cout << std::endl;
                }
            } else {
                // If guess is valid and is the whole word
                currentWord = selectedWord; // Player guessed the word correctly
            }
        }
    }

    // Game result display
    if (currentWord == selectedWord) {
        std::cout << GREEN << "Congratulations! You've guessed the word: " << selectedWord << RESET << std::endl;
    } else {
        std::cout << RED << "Sorry, you've run out of tries. The word was: " << selectedWord << RESET << std::endl;
    }
}

void Hangman::startGameLoop() {
    bool playAgain = true;

    while (playAgain) {
        int difficulty = -1;
        clearScreen();
        showChooseDifficultyMenu();
        std::cout << GREEN << "Enter your choice: " << RESET;
        std::cin >> difficulty;

        while (difficulty < 0 || difficulty > 3) {
            clearScreen();
            showChooseDifficultyMenu();
            std::cout << RED << "Invalid. Try again." << RESET << std::endl;
            std::cout << GREEN << "Enter your choice: " << RESET;
            std::cin >> difficulty;
        }

        if (difficulty == 0) {
            return;
        }

        if (difficulty == 1) {
            startGame(EASY_FILE_PATH, "EASY", BOLDGREEN);
        } else if (difficulty == 2) {
            startGame(MEDIUM_FILE_PATH, "MEDIUM", BOLDYELLOW);
        } else if (difficulty == 3) {
            startGame(HARD_FILE_PATH, "HARD", BOLDRED);
        }

        std::cout << std::endl;
        std::cout << YELLOW << "Do you want to play again? (Y/N): " << RESET;
        char playAgainChoice;
        std::cin >> playAgainChoice;
        playAgain = (playAgainChoice == 'y' || playAgainChoice == 'Y');
    }
}
