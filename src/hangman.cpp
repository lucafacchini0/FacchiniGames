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




// Constructor to initialize the game
Hangman::Hangman() {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed random number generator
}



// Method to display the choose difficulty menu
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

// Print the error message to the console
void Hangman::printError(const string& message) {
    std::cout << std::endl;
    std::cout << BOLDRED << "Invalid guess " << RESET << std::endl;
    std::cout << RED << message << RESET << std::endl;
    std::cout << std::endl;
}

// Print the warning message to the console
void Hangman::printWarning(const string& message) {
    std::cout << std::endl;
    std::cout << BOLDYELLOW << "Invalid " << RESET << std::endl;
    std::cout << YELLOW << message << RESET << std::endl;
    std::cout << std::endl;
}

// Print the success message to the console
void Hangman::printSuccess(const string& message) {
    std::cout << std::endl;
    std::cout << BOLDGREEN << "Valid guess " << RESET << std::endl;
    std::cout << GREEN << message << RESET << std::endl;
    std::cout << std::endl;
}

// Print the current guessed word status to the console
void Hangman::printCurrentWord(const string& word) const {
    std::cout << word << std::endl;
}




// Method to validate the user's guess
Hangman::GuessResult Hangman::validateGuess(const std::string& guess, std::string& currentWord, const std::string& selectedWord) {

    // Check if the guess is a single letter
    if (guess.length() == 1) {
        char lowerGuess = std::tolower(guess[0]);

        if (!std::isalpha(lowerGuess)) { return INVALID_SINGLE_CHAR; } // If the character is not a letter
        if (currentWord.find(lowerGuess) != std::string::npos) { return ALREADY_GUESSED_CHAR; } // If the character has already been guessed

        return VALID_SINGLE_CHAR;
    }

    // Validate a full word guess
    for(int i = 0; i < guess.length(); i++) {
        if (!std::isalpha(guess[i])) { return INVALID_CHAR_WORD; } // Return invalid character
    }

    // Check if the full word guess is correct
    if (guess == selectedWord) {
        currentWord = selectedWord;
        return CORRECT_WORD;
    }

    return INCORRECT_WORD;
}

// Search for a single character in the selected word
bool Hangman::searchSingleChar(char guess, const string& selectedWord, string& currentWord) {
    bool found = false;

    for (int i = 0; i < selectedWord.length(); i++) {
        if (std::tolower(selectedWord[i]) == guess) {
            currentWord[i] = selectedWord[i];
            found = true;
        }
    }
    return found;
}




// Start the Hangman game with the selected difficulty
void Hangman::startGame(const string &filePath, const string &difficultyText, const string &color) {
    // Open the selected file
    std::ifstream wordsFile(filePath);
    if (!wordsFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    vector<string> words; // Vector to store words from the file
    string line; // Line to read from the file

    // Read words from the selected file into a vector
    while (std::getline(wordsFile, line)) {
        words.push_back(line);
    }

    // Close the file after reading
    wordsFile.close();

    // Check if the file is empty
    if (words.empty()) {
        std::cerr << "No words found in the file." << std::endl;
        return; // Exit if no words are found
    }

    // Select a random word from the list
    int randomWordIndex = rand() % words.size();
    string selectedWord = words[randomWordIndex];

    // Initialize the game variables
    string currentWord(selectedWord.length(), '_'); // Current state of the word
    int triesLeft = MAX_TRIES;

    clearScreen();

    // Display that the game has started
    std::cout << std::endl;
    std::cout << color << difficultyText << " Game has started!" << RESET << std::endl;
    std::cout << "The word is " << BLUE << selectedWord.length() << RESET << " letters long" << std::endl;
    std::cout << std::endl;

    string currentGuess; // User's current guess

    // Main game loop
    while (triesLeft > 0 && currentWord != selectedWord) {
        std::cout << YELLOW << "Remaining tries: " << RESET << triesLeft << std::endl;
        printCurrentWord(currentWord); // Display current guessed word

        std::cout << "Enter your guess: ";
        std::cin >> currentGuess; // Get user guess
        clearScreen();

        switch(validateGuess(currentGuess, currentWord, selectedWord)) {
            case VALID_SINGLE_CHAR:
                if (!searchSingleChar(std::tolower(currentGuess[0]), selectedWord, currentWord)) {
                    printError("The character '" + currentGuess + "' is not in the word.");
                    triesLeft--;
                } else {
                    printSuccess("The character '" + currentGuess + "' is in the word.");
                }
                break;
            case INVALID_SINGLE_CHAR:
                printError("The character is invalid. Please enter a valid character.");
                triesLeft--;
                break;
            case INVALID_CHAR_WORD:
                printError("The word is invalid. Please enter a valid word.");
                triesLeft--;
                break;
            case ALREADY_GUESSED_CHAR:
                printWarning("The character is already in the word.");
                break;
            case INCORRECT_WORD:
                printError("The word is incorrect. Please try again.");
                triesLeft--;
                break;
            case CORRECT_WORD:
                printSuccess("Correct word!");
                break;
        }
    }

    // Display game result
    if (currentWord == selectedWord) {
        std::cout << GREEN << "Congratulations! You've guessed the word: " << selectedWord << RESET << std::endl;
    } else {
        std::cout << RED << "Sorry, you've run out of tries. The word was: " << selectedWord << RESET << std::endl;
    }
}

// Main game loop for starting the game and handling replay logic
void Hangman::startGameLoop() {
    bool playAgain = true;

    // While the player wants to play again
    while (playAgain) {
        int difficulty = -1;
        clearScreen();
        showChooseDifficultyMenu(); // Show difficulty selection menu
        std::cout << GREEN << "Enter your choice: " << RESET;
        std::cin >> difficulty;

        // Validate difficulty input
        while (difficulty < 0 || difficulty > 3) {
            clearScreen();
            showChooseDifficultyMenu();
            std::cout << RED << "Invalid. Try again." << RESET << std::endl;
            std::cout << GREEN << "Enter your choice: " << RESET;
            std::cin >> difficulty;
        }

        // Start the game based on selected difficulty
        switch (difficulty) {
            case 1: startGame(EASY_FILE_PATH, "EASY", BOLDGREEN); break;
            case 2: startGame(MEDIUM_FILE_PATH, "MEDIUM", BOLDYELLOW); break;
            case 3: startGame(HARD_FILE_PATH, "HARD", BOLDRED); break;
            default: break;
        }

        // Ask if the user wants to play again
        std::cout << std::endl;
        std::cout << YELLOW << "Do you want to play again? (Y/N): " << RESET;
        char choice;
        std::cin >> choice;

        playAgain = (std::tolower(choice) == 'y'); // Continue or exit based on user input
    }
}