#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include "../include/misc.h"
#include "../include/hangman.h"
#include "../include/colors.h"

using std::string;
using std::vector;

const string EASY_FILE_PATH = "../assets/hangman/easyWords.txt";
const string MEDIUM_FILE_PATH = "../assets/hangman/mediumWords.txt";
const string HARD_FILE_PATH = "../assets/hangman/hardWords.txt";

constexpr int MAX_TRIES = 10;

void showChooseDifficultyMenu() {
    std::cout << std::endl;
    std::cout << MAGENTA << centerText("Choose the difficulty:") << RESET << std::endl;
    std::cout << std::endl;
    std::cout << GREEN << "EASY [1]" << RESET << std::endl;
    std::cout << YELLOW << "MEDIUM [2]" << RESET << std::endl;
    std::cout << RED << "HARD [3]" << RESET << std::endl;
    std::cout << std::endl;
    std::cout << BLUE << "EXIT [0]" << RESET << std::endl;
    std::cout << std::endl;
}

bool isValidGuess(const string& guess, const string& currentWord) {
    for (char c : guess) {
        if (!(isalpha(c))) {
            clearScreen();
            std::cout << std::endl;
            std::cout << RED << "Invalid guess (Only letters are allowed). Try again." << RESET << std::endl;
            return false;
        }
    }

    if (guess.length() > currentWord.length()) {
        clearScreen();
        std::cout << std::endl;
        std::cout << RED << "Invalid guess (Word is too long). Try again." << RESET << std::endl;
        return false;
    }

    return true;
}

void startGame(const string& filePath, const string& difficultyText, const string& color) {
    // File stream
    std::ifstream wordsFile(filePath);
    if (!wordsFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    // Read the words from the file
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

    // Get a random word
    int randomWordIndex = rand() % words.size();
    Hangman game(words[randomWordIndex]);

    bool hasWon = false;

    clearScreen();
    std::cout << std::endl;
    std::cout << color << difficultyText << " Game has started!" << RESET << std::endl;
    std::cout << "The word is " << BLUE << words[randomWordIndex].length() << RESET << " letters long" << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < MAX_TRIES && !hasWon;) {
        string guess;
        std::cout << YELLOW << "Remaining tries: " << RESET << MAX_TRIES - i << std::endl;
        std::cout << std::endl;
        game.displayCurrentWord();
        std::cout << std::endl;
        std::cout << BLUE << "Your guess: " << RESET;
        std::cin >> guess;

        // Check if it's a valid guess
        if (!isValidGuess(guess, words[randomWordIndex])) {
            i++;
            continue;
        }

        // Check the guess
        int result = game.guessLetter(guess);

        if (result == -1) {
            clearScreen();
            std::cout << std::endl;
            std::cout << RED << "Incorrect guess." << RESET << std::endl;
            i++;
        } else if (result == -2) {
            clearScreen();
            std::cout << std::endl;
            hasWon = true;
        } else {
            clearScreen();
            std::cout << std::endl;
            std::cout << GREEN << "Correct guess." << RESET << std::endl;
        }
    }
    clearScreen();
    if(hasWon) {
        std::cout << GREEN << centerText("Congratulations! You won!") << RESET << std::endl;
    } else {
        std::cout << RED << centerText("Aaaah, you lost! Better luck next time!") << RESET << std::endl;
    }
    std::cout << centerText("The word was: ") << std::endl;
    std::cout << BLUE << centerText(words[randomWordIndex]) << RESET << std::endl;
}

int startHangmanGame() {
    srand(static_cast<unsigned int>(time(nullptr)));

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
        return -1;
    }

    if (difficulty == 1) {
        startGame(EASY_FILE_PATH, "EASY", BOLDGREEN);
    } else if (difficulty == 2) {
        startGame(MEDIUM_FILE_PATH, "MEDIUM", BOLDYELLOW);
    } else if (difficulty == 3) {
        startGame(HARD_FILE_PATH, "HARD", BOLDRED);
    }

    return 0;
}
