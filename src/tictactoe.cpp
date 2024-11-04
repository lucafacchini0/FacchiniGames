#include "../include/tictactoe.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <ctime>
#include <algorithm>
#include "../include/colors.h"
#include "../include/misc.h"




// Constructor for the TicTacToe class
TicTacToe::TicTacToe() {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize the game board to an empty state
    clearBoard();
}




// Method to display the choose difficulty menu
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

// Method to print the current state of the board
void TicTacToe::printBoard() const {
    std::cout << std::endl; // Add some space before the board

    for(int i = 0; i < 3; i++) { // Loop through each row
        for(int j = 0; j < 3; j++) { // Loop through each column
            char current = board[i][j];
            if (current == '0') { // Empty space
                std::cout << WHITE << "  " << current << "  "; // Empty space
            } else if (current == 'X') { // Player X
                std::cout << BLUE << "  " << current << "  "; // Player X
            } else if (current == 'O') { // Player O
                std::cout << RED << "  " << current << "  "; // Player O
            }
        }
        std::cout << RESET << std::endl << std::endl; // Reset color after each row
    }
}

// Method to clear the board
void TicTacToe::clearBoard() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = '0';
        }
    }
}




// Method to validate the player's choice
bool TicTacToe::validChoice(int row, int col) const {
    if(row < 0 || row > 2 || col < 0 || col > 2) { // Check if the row and column are valid
        std::cout << RED << "Invalid choice. Try again." << RESET << std::endl;
        return false;
    }
    if(board[row][col] != '0') { // '0' means the space is empty
        std::cout << RED << "This place is already taken. Try again." << RESET << std::endl;
        return false;
    }
    return true;
}

// Method to check if a player has won the game
char TicTacToe::hasWon() const {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != '0' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
        if (board[0][i] != '0' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }

    // Check diagonals
    if (board[0][0] != '0' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != '0' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    return '0'; // No winner yet
}

// Evaluate the board and return a score
int TicTacToe::evaluateBoard() const {
    switch (hasWon()) {
        case 'X': return -10;
        case 'O': return 10;
        default: return 0;
    }
}

// Check if there are any moves left on the board
bool TicTacToe::isMovesLeft() const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '0') {
                return true;
            }
        }
    }
    return false;
}

// Minimax algorithm
int TicTacToe::minimax(int depth, bool isMaximizing) {
    int score = evaluateBoard();

    // If the game has ended, return the score
    if (score == 10 || score == -10) {
        return score;
    }

    // If no moves left, it's a draw
    if (!isMovesLeft()) {
        return 0; // Return 0 for a tie
    }

    if (isMaximizing) { // Player O (computer)
        int bestScore = INT_MIN; // Initialize best score for maximizing player
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '0') { // If the cell is empty
                    board[i][j] = 'O'; // Make the move
                    bestScore = std::max(bestScore, minimax(depth + 1, false)); // Recur for the next move
                    board[i][j] = '0'; // Undo the move
                }
            }
        }
        return bestScore; // Return the best score
    } else { // Player X (human)
        int bestScore = INT_MAX; // Initialize best score for minimizing player
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '0') { // If the cell is empty
                    board[i][j] = 'X'; // Make the move
                    bestScore = std::min(bestScore, minimax(depth + 1, true)); // Recur for the next move
                    board[i][j] = '0'; // Undo the move
                }
            }
        }
        return bestScore;
    }
}

// Make the best move for the computer
void TicTacToe::computerMove() {
    int bestScore = (difficulty == 1) ? INT_MAX : INT_MIN; // Invert score for EASY
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '0') {
                board[i][j] = 'O';
                int moveScore = minimax(0, false);
                board[i][j] = '0';

                if (difficulty == 1) { // EASY: choose the worst move
                    if (moveScore < bestScore) {
                        bestMoveRow = i;
                        bestMoveCol = j;
                        bestScore = moveScore;
                    }
                } else if (difficulty == 2) { // MEDIUM: 50% best, 50% worst
                    if (rand() % 2 == 0) {
                        if (moveScore > bestScore) {
                            bestMoveRow = i;
                            bestMoveCol = j;
                            bestScore = moveScore;
                        }
                    } else {
                        if (moveScore < bestScore) {
                            bestMoveRow = i;
                            bestMoveCol = j;
                            bestScore = moveScore;
                        }
                    }
                } else { // HARD: choose the best move
                    if (moveScore > bestScore) {
                        bestMoveRow = i;
                        bestMoveCol = j;
                        bestScore = moveScore;
                    }
                }
            }
        }
    }

    if (bestMoveRow != -1 && bestMoveCol != -1) {
        board[bestMoveRow][bestMoveCol] = 'O';
    }
}




// Start the game based on the selected difficulty
void TicTacToe::startGame(int difficulty) {
    this->difficulty = difficulty; // Set the difficulty
    char currentPlayer = 'X'; // Starting player
    bool hasGameEnded = false;

    while (!hasGameEnded) {
        clearScreen(); // Clear the screen after each turn
        printBoard(); // Show current board

        if (currentPlayer == 'X') {
            bool validChoiceFlag = false;
            while (!validChoiceFlag) {
                int row, col;

                std::cout << GREEN << "Enter the row (1-3): " << RESET;
                std::cin >> row;
                std::cout << GREEN << "Enter the column (1-3): " << RESET;
                std::cin >> col;

                validChoiceFlag = validChoice(row - 1, col - 1);
                if (validChoiceFlag) {
                    board[row - 1][col - 1] = currentPlayer; // Place the player's move
                } else {
                    std::cout << RED << "Invalid input. Please try again." << RESET << std::endl;
                    // Clear cin in case of bad input
                    if (std::cin.fail()) {
                        std::cin.clear(); // Clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                    }
                }
            }
        } else {
            computerMove(); // Let the computer make its move
        }

        // Check for a winner
        char winner = hasWon();
        if (winner != '0') {
            clearScreen();
            printBoard();
            std::cout << (winner == 'X' ? BLUE : RED) << "Player " << winner << " wins!" << RESET << std::endl;
            hasGameEnded = true;
        } else if (!isMovesLeft()) {
            clearScreen();
            printBoard();
            std::cout << "It's a tie!" << std::endl;
            hasGameEnded = true;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Switch player
    }

    std::cout << "Game over!" << std::endl;
}

// --- END: Game loop methods --- //


// Main game loop for starting the game and handling replay logic
void TicTacToe::startGameLoop() {
    bool playAgain = true;

    // While the player wants to play again
    while(playAgain) {
        int difficulty = -1;
        clearScreen();
        clearBoard();
        showChooseDifficultyMenu();
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
        switch(difficulty) {
            case 1: startGame(1); break;
            case 2: startGame(2); break;
            case 3: startGame(3); break;
            default: return;
        }

        // Ask if the user wants to play again
        std::cout << std::endl;
        std::cout << YELLOW << "Do you want to play again? (Y/N): " << RESET;
        char choice;
        std::cin >> choice;

        playAgain = (std::tolower(choice) == 'y'); // Continue or exit based on user inputì
    }
}

// --- END: Game loop methods --- //