#include "../include/tictactoe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/colors.h"
#include "../include/misc.h"

TicTacToe::TicTacToe() {
    clearBoard(); // Initialize the board to an empty state
}

void TicTacToe::showChooseDifficultyMenu() const {
    std::cout << std::endl;
    std::cout << BOLDMAGENTA << centerText("TicTacToe Game") << RESET << std::endl;
    std::cout << MAGENTA << centerText("Choose the difficulty:") << RESET << std::endl;
    std::cout << std::endl;
    std::cout << GREEN << "EASY [1]" << RESET << std::endl;
    std::cout << YELLOW << "MEDIUM [2]" << RESET << std::endl;
    std::cout << RED << "HARD [3]" << RESET << std::endl;
    std::cout << std::endl;
    std::cout << BLUE << "EXIT [0]" << RESET << std::endl;
    std::cout << std::endl;
}

void TicTacToe::printBoard() const {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            char current = board[i][j];
            if (current == '0') {
                std::cout << WHITE << current << " "; // Empty space
            } else if (current == 'X') {
                std::cout << BLUE << current << " "; // Player X
            } else if (current == 'O') {
                std::cout << RED << current << " "; // Player O
            }
        }
        std::cout << RESET << std::endl; // Reset color after each row
    }
}

void TicTacToe::clearBoard() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = '0';
        }
    }
}

bool TicTacToe::validChoice(int row, int col) const {
    if(row < 0 || row > 2 || col < 0 || col > 2) {
        std::cout << RED << "Invalid choice. Try again." << RESET << std::endl;
        return false;
    }

    if(board[row][col] != '0') {
        std::cout << RED << "This place is already taken. Try again." << RESET << std::endl;
        return false;
    }

    return true;
}

char TicTacToe::hasWon() const {
    // Check rows
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '0') {
            return board[i][0];
        }
    }

    // Check columns
    for(int i = 0; i < 3; i++) {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '0') {
            return board[0][i];
        }
    }

    // Check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '0') {
        return board[0][0];
    }

    // Check inverse diagonal
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '0') {
        return board[0][2];
    }

    return '0'; // No winner yet
}

void TicTacToe::startGame(int difficulty) {
    char currentPlayer = 'X'; // Starting player
    bool hasGameEnded = false;

    while(!hasGameEnded) {
        clearScreen(); // Clear the screen after each turn
        printBoard(); // Show current board
        // Player's turn
        if (currentPlayer == 'X') {
            bool validChoiceFlag = false;
            while(!validChoiceFlag) {
                int row, col;

                // Insert first the row, then the column and then validate
                std::cout << GREEN << "Enter the row (1-3): " << RESET;
                std::cin >> row;
                std::cout << GREEN << "Enter the column (1-3): " << RESET;
                std::cin >> col;

                // Convert to 0-indexed for internal representation
                validChoiceFlag = validChoice(row - 1, col - 1);
                if (validChoiceFlag) {
                    board[row - 1][col - 1] = currentPlayer; // Place move
                }
            }
        } else {
            // Computer's turn (random move for now)
            bool validChoiceFlag = false;
            while(!validChoiceFlag) {
                int row = rand() % 3;
                int col = rand() % 3;

                validChoiceFlag = validChoice(row, col);
                if (validChoiceFlag) {
                    board[row][col] = currentPlayer; // Place move
                }
            }
        }

        // Check for a winner after each turn
        char winner = hasWon();
        if (winner != '0') {
            clearScreen(); // Clear screen before showing final board
            printBoard();
            if (winner == 'X') {
                std::cout << GREEN << "Player X wins!" << RESET << std::endl;
            } else {
                std::cout << RED << "Computer O wins!" << RESET << std::endl;
            }
            hasGameEnded = true;
        } else {
            // Switch players
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

void TicTacToe::startGameLoop() {
    srand(static_cast<unsigned int>(time(nullptr)));

    bool playAgain = true;

    while(playAgain) {
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
            clearBoard(); // Clear board before starting
            startGame(1);
        }

        std::cout << std::endl;
        std::cout << YELLOW << "Do you want to play again? (Y/N): " << RESET;
        char playAgainChoice;
        std::cin >> playAgainChoice;
        playAgain = (playAgainChoice == 'y' || playAgainChoice == 'Y');
    }
}
