#include <iostream>
#include "../include/colors.h"
#include "../include/hangman.h"
#include "../include/misc.h"
#include "../include/tictactoe.h"

const int TOTAL_GAMES = 2;

void displayMenu() {
    std::cout << std::endl;
    std::cout << BOLDYELLOW << centerText("FacchiniGames") << RESET << std::endl;
    std::cout << BLUE << centerText("v1.0") << RESET << std::endl;

    std::cout << std::endl;
    std::cout << GREEN << "Choose an option" << RESET << std::endl;
    std::cout << std::endl;
    std::cout << BLUE << "1. " << RESET << "Hangman Game" << std::endl;
    std::cout << BLUE << "2. " << RESET << "TicTacToe Game" << std::endl;
    std::cout << RED << "0. " << RESET << "Exit" << std::endl;
    std::cout << std::endl;
}

int main() {
    int choice = -1;
    bool playAgain = true;

    while (playAgain) {
        clearScreen(); // Clear the screen for a fresh start.
        displayMenu();
        std::cout << GREEN << "Enter your choice: " << RESET;
        std::cin >> choice;
        std::cout << std::endl;

        // Validate choice
        while (choice < 0 || choice > TOTAL_GAMES) {
            clearScreen();
            displayMenu();
            std::cout << RED << "Invalid choice!" << RESET << std::endl;
            std::cout << GREEN << "Enter your choice: " << RESET;
            std::cin >> choice;
            std::cout << std::endl;
        }

        // Start the selected game
        if (choice == 1) {
            startHangmanGame(); // Start the Hangman games
        } else if (choice == 2) {
            TicTacToe ticTacToeInstance; // Create an instance of the TicTacToe class
            ticTacToeInstance.startGameLoop(); // Start the TicTacToe game
        } else if (choice == 0) {
            std::cout << GREEN << "Goodbye!" << RESET << std::endl;
            break; // Exit the loop if user chooses to quit
        }

        // Ask if the user wants to play again
        std::cout << std::endl;
        std::cout << YELLOW << "Do you want to play another game? (Y/N): " << RESET;
        char playAgainChoice;
        std::cin >> playAgainChoice;
        playAgain = (playAgainChoice == 'y' || playAgainChoice == 'Y'); // Update loop condition
    }

    std::cout << std::endl;
    std::cout << GREEN << "Thanks for playing!" << RESET << std::endl;

    return 0;
}