class TicTacToe {
public:
    TicTacToe(); // Constructor to initialize the game
    void startGameLoop(); // Public method to start the game loop

private:
    char board[3][3];
    int difficulty; // Difficulty level for the game

    void showChooseDifficultyMenu() const;
    void printBoard() const;
    void clearBoard();
    bool validChoice(int row, int col) const;
    char hasWon() const;
    void startGame(int difficulty);

    // Minimax algorithm methods
    int minimax(int depth, bool isMaximizing);
    void computerMove();
    int evaluateBoard() const;
    bool isMovesLeft() const;
};
