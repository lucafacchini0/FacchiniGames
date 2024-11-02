#ifndef TICTACTOE_H
#define TICTACTOE_H

class TicTacToe {
public:
    TicTacToe(); // Constructor to initialize the game
    void startGameLoop(); // Public method to start the game loop
private:
    char board[3][3];

    void showChooseDifficultyMenu() const;
    void printBoard() const;
    void clearBoard();
    bool validChoice(int row, int col) const;
    char hasWon() const;
    void startGame(int difficulty);
};



#endif // TICTACTOE_H
