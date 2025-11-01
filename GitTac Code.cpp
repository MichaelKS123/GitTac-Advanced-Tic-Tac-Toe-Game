// GitTac - Advanced Tic Tac Toe Game
// Created by Michael Semera
// Features: Single/Multiplayer, AI with 4 difficulty levels, 3D board support

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// ANSI color codes for beautiful output
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string BOLD = "\033[1m";

// Game modes
enum GameMode { SINGLE_PLAYER, MULTIPLAYER };
enum Difficulty { EASY, MEDIUM, HARD, IMPOSSIBLE };
enum BoardType { CLASSIC_2D, ADVANCED_3D };

class GitTacGame {
private:
    vector<vector<char>> board2D;
    vector<vector<vector<char>>> board3D;
    char currentPlayer;
    char humanPlayer;
    char aiPlayer;
    GameMode mode;
    Difficulty difficulty;
    BoardType boardType;
    int boardSize;
    int moveCount;
    bool gameOver;
    string player1Name;
    string player2Name;

public:
    GitTacGame() {
        srand(time(0));
        currentPlayer = 'X';
        humanPlayer = 'X';
        aiPlayer = 'O';
        moveCount = 0;
        gameOver = false;
        boardSize = 3;
    }

    void displayBanner() {
        cout << CYAN << BOLD << "\n";
        cout << "  ╔═══════════════════════════════════════╗\n";
        cout << "  ║           🎮 GITTAC 🎮               ║\n";
        cout << "  ║     Advanced Tic Tac Toe Game       ║\n";
        cout << "  ║      Created by Michael Semera       ║\n";
        cout << "  ╚═══════════════════════════════════════╝\n";
        cout << RESET << "\n";
    }

    void setupGame() {
        displayBanner();
        
        // Choose board type
        cout << YELLOW << "Choose Board Type:\n" << RESET;
        cout << "1. Classic 2D (3x3)\n";
        cout << "2. Advanced 3D (3x3x3)\n";
        cout << "Enter choice (1-2): ";
        
        int boardChoice;
        cin >> boardChoice;
        boardType = (boardChoice == 2) ? ADVANCED_3D : CLASSIC_2D;

        // Choose game mode
        cout << "\n" << YELLOW << "Choose Game Mode:\n" << RESET;
        cout << "1. Single Player (vs AI)\n";
        cout << "2. Multiplayer (vs Human)\n";
        cout << "Enter choice (1-2): ";
        
        int modeChoice;
        cin >> modeChoice;
        mode = (modeChoice == 1) ? SINGLE_PLAYER : MULTIPLAYER;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (mode == SINGLE_PLAYER) {
            cout << "\n" << GREEN << "Enter your name: " << RESET;
            getline(cin, player1Name);
            
            cout << "\n" << YELLOW << "Choose Difficulty:\n" << RESET;
            cout << "1. Easy (Random moves)\n";
            cout << "2. Medium (Basic strategy)\n";
            cout << "3. Hard (Advanced strategy)\n";
            cout << "4. Impossible (Minimax algorithm)\n";
            cout << "Enter choice (1-4): ";
            
            int diffChoice;
            cin >> diffChoice;
            
            switch(diffChoice) {
                case 1: difficulty = EASY; break;
                case 2: difficulty = MEDIUM; break;
                case 3: difficulty = HARD; break;
                case 4: difficulty = IMPOSSIBLE; break;
                default: difficulty = MEDIUM;
            }
        } else {
            cout << "\n" << GREEN << "Enter Player 1 name (X): " << RESET;
            getline(cin, player1Name);
            cout << GREEN << "Enter Player 2 name (O): " << RESET;
            getline(cin, player2Name);
        }

        initializeBoard();
    }

    void initializeBoard() {
        if (boardType == CLASSIC_2D) {
            board2D = vector<vector<char>>(boardSize, vector<char>(boardSize, ' '));
        } else {
            board3D = vector<vector<vector<char>>>(
                boardSize, 
                vector<vector<char>>(boardSize, vector<char>(boardSize, ' '))
            );
        }
    }

    void displayBoard2D() {
        cout << "\n";
        cout << "     1   2   3\n";
        cout << "   ╔═══╦═══╦═══╗\n";
        
        for (int i = 0; i < boardSize; i++) {
            cout << " " << (i + 1) << " ║";
            for (int j = 0; j < boardSize; j++) {
                char cell = board2D[i][j];
                string color = (cell == 'X') ? RED : (cell == 'O') ? BLUE : "";
                cout << " " << color << cell << RESET << " ";
                if (j < boardSize - 1) cout << "║";
            }
            cout << "║\n";
            if (i < boardSize - 1) {
                cout << "   ╠═══╬═══╬═══╣\n";
            }
        }
        cout << "   ╚═══╩═══╩═══╝\n\n";
    }

    void displayBoard3D() {
        cout << "\n" << CYAN << "3D Board (Layer by Layer):\n" << RESET;
        
        for (int layer = 0; layer < boardSize; layer++) {
            cout << YELLOW << "\nLayer " << (layer + 1) << ":\n" << RESET;
            cout << "     1   2   3\n";
            cout << "   ╔═══╦═══╦═══╗\n";
            
            for (int i = 0; i < boardSize; i++) {
                cout << " " << (i + 1) << " ║";
                for (int j = 0; j < boardSize; j++) {
                    char cell = board3D[layer][i][j];
                    string color = (cell == 'X') ? RED : (cell == 'O') ? BLUE : "";
                    cout << " " << color << cell << RESET << " ";
                    if (j < boardSize - 1) cout << "║";
                }
                cout << "║\n";
                if (i < boardSize - 1) {
                    cout << "   ╠═══╬═══╬═══╣\n";
                }
            }
            cout << "   ╚═══╩═══╩═══╝\n";
        }
    }

    void displayBoard() {
        if (boardType == CLASSIC_2D) {
            displayBoard2D();
        } else {
            displayBoard3D();
        }
    }

    bool isValidMove(int row, int col, int layer = 0) {
        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
            return false;
        }
        
        if (boardType == CLASSIC_2D) {
            return board2D[row][col] == ' ';
        } else {
            if (layer < 0 || layer >= boardSize) return false;
            return board3D[layer][row][col] == ' ';
        }
    }

    void makeMove(int row, int col, int layer = 0) {
        if (boardType == CLASSIC_2D) {
            board2D[row][col] = currentPlayer;
        } else {
            board3D[layer][row][col] = currentPlayer;
        }
        moveCount++;
    }

    bool checkWin2D() {
        // Check rows
        for (int i = 0; i < boardSize; i++) {
            if (board2D[i][0] != ' ' && 
                board2D[i][0] == board2D[i][1] && 
                board2D[i][1] == board2D[i][2]) {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < boardSize; j++) {
            if (board2D[0][j] != ' ' && 
                board2D[0][j] == board2D[1][j] && 
                board2D[1][j] == board2D[2][j]) {
                return true;
            }
        }

        // Check diagonals
        if (board2D[0][0] != ' ' && 
            board2D[0][0] == board2D[1][1] && 
            board2D[1][1] == board2D[2][2]) {
            return true;
        }

        if (board2D[0][2] != ' ' && 
            board2D[0][2] == board2D[1][1] && 
            board2D[1][1] == board2D[2][0]) {
            return true;
        }

        return false;
    }

    bool checkWin3D() {
        // Check each layer
        for (int layer = 0; layer < boardSize; layer++) {
            // Rows
            for (int i = 0; i < boardSize; i++) {
                if (board3D[layer][i][0] != ' ' &&
                    board3D[layer][i][0] == board3D[layer][i][1] &&
                    board3D[layer][i][1] == board3D[layer][i][2]) {
                    return true;
                }
            }
            
            // Columns
            for (int j = 0; j < boardSize; j++) {
                if (board3D[layer][0][j] != ' ' &&
                    board3D[layer][0][j] == board3D[layer][1][j] &&
                    board3D[layer][1][j] == board3D[layer][2][j]) {
                    return true;
                }
            }
            
            // Diagonals in layer
            if (board3D[layer][0][0] != ' ' &&
                board3D[layer][0][0] == board3D[layer][1][1] &&
                board3D[layer][1][1] == board3D[layer][2][2]) {
                return true;
            }
            
            if (board3D[layer][0][2] != ' ' &&
                board3D[layer][0][2] == board3D[layer][1][1] &&
                board3D[layer][1][1] == board3D[layer][2][0]) {
                return true;
            }
        }

        // Check vertical columns through layers
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board3D[0][i][j] != ' ' &&
                    board3D[0][i][j] == board3D[1][i][j] &&
                    board3D[1][i][j] == board3D[2][i][j]) {
                    return true;
                }
            }
        }

        // Check 3D diagonals
        // Main 3D diagonal
        if (board3D[0][0][0] != ' ' &&
            board3D[0][0][0] == board3D[1][1][1] &&
            board3D[1][1][1] == board3D[2][2][2]) {
            return true;
        }

        // Other 3D diagonals
        if (board3D[0][0][2] != ' ' &&
            board3D[0][0][2] == board3D[1][1][1] &&
            board3D[1][1][1] == board3D[2][2][0]) {
            return true;
        }

        if (board3D[0][2][0] != ' ' &&
            board3D[0][2][0] == board3D[1][1][1] &&
            board3D[1][1][1] == board3D[2][0][2]) {
            return true;
        }

        if (board3D[0][2][2] != ' ' &&
            board3D[0][2][2] == board3D[1][1][1] &&
            board3D[1][1][1] == board3D[2][0][0]) {
            return true;
        }

        return false;
    }

    bool checkWin() {
        return (boardType == CLASSIC_2D) ? checkWin2D() : checkWin3D();
    }

    bool checkDraw() {
        int maxMoves = (boardType == CLASSIC_2D) ? 9 : 27;
        return moveCount >= maxMoves && !checkWin();
    }

    void getHumanMove() {
        int row, col, layer = 0;
        bool validInput = false;

        while (!validInput) {
            if (boardType == CLASSIC_2D) {
                cout << CYAN << currentPlayer << "'s turn. ";
                if (mode == MULTIPLAYER) {
                    string playerName = (currentPlayer == 'X') ? player1Name : player2Name;
                    cout << "(" << playerName << ") ";
                }
                cout << "Enter row (1-3): " << RESET;
                cin >> row;
                cout << CYAN << "Enter column (1-3): " << RESET;
                cin >> col;
                row--; col--;
            } else {
                cout << CYAN << currentPlayer << "'s turn. ";
                if (mode == MULTIPLAYER) {
                    string playerName = (currentPlayer == 'X') ? player1Name : player2Name;
                    cout << "(" << playerName << ") ";
                }
                cout << "Enter layer (1-3): " << RESET;
                cin >> layer;
                cout << CYAN << "Enter row (1-3): " << RESET;
                cin >> row;
                cout << CYAN << "Enter column (1-3): " << RESET;
                cin >> col;
                layer--; row--; col--;
            }

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << "Invalid input! Please enter numbers only.\n" << RESET;
                continue;
            }

            if (isValidMove(row, col, layer)) {
                makeMove(row, col, layer);
                validInput = true;
            } else {
                cout << RED << "Invalid move! Try again.\n" << RESET;
            }
        }
    }

    void getAIMoveEasy() {
        vector<tuple<int, int, int>> availableMoves;
        
        if (boardType == CLASSIC_2D) {
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (board2D[i][j] == ' ') {
                        availableMoves.push_back(make_tuple(0, i, j));
                    }
                }
            }
        } else {
            for (int layer = 0; layer < boardSize; layer++) {
                for (int i = 0; i < boardSize; i++) {
                    for (int j = 0; j < boardSize; j++) {
                        if (board3D[layer][i][j] == ' ') {
                            availableMoves.push_back(make_tuple(layer, i, j));
                        }
                    }
                }
            }
        }

        if (!availableMoves.empty()) {
            int randomIndex = rand() % availableMoves.size();
            auto move = availableMoves[randomIndex];
            makeMove(get<1>(move), get<2>(move), get<0>(move));
            cout << GREEN << "AI played at position.\n" << RESET;
        }
    }

    void getAIMoveMedium() {
        // Try to win first, then block, then random
        if (!tryWinningMove() && !tryBlockingMove()) {
            getAIMoveEasy();
        }
    }

    bool tryWinningMove() {
        return tryStrategicMove(aiPlayer);
    }

    bool tryBlockingMove() {
        return tryStrategicMove(humanPlayer);
    }

    bool tryStrategicMove(char player) {
        if (boardType == CLASSIC_2D) {
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (board2D[i][j] == ' ') {
                        board2D[i][j] = player;
                        bool wins = checkWin2D();
                        board2D[i][j] = ' ';
                        
                        if (wins) {
                            makeMove(i, j);
                            return true;
                        }
                    }
                }
            }
        } else {
            for (int layer = 0; layer < boardSize; layer++) {
                for (int i = 0; i < boardSize; i++) {
                    for (int j = 0; j < boardSize; j++) {
                        if (board3D[layer][i][j] == ' ') {
                            board3D[layer][i][j] = player;
                            bool wins = checkWin3D();
                            board3D[layer][i][j] = ' ';
                            
                            if (wins) {
                                makeMove(i, j, layer);
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    void getAIMoveHard() {
        if (!tryWinningMove()) {
            if (!tryBlockingMove()) {
                if (!tryCornerOrCenter()) {
                    getAIMoveEasy();
                }
            }
        }
    }

    bool tryCornerOrCenter() {
        if (boardType == CLASSIC_2D) {
            // Try center
            if (board2D[1][1] == ' ') {
                makeMove(1, 1);
                return true;
            }
            
            // Try corners
            vector<pair<int, int>> corners = {{0,0}, {0,2}, {2,0}, {2,2}};
            for (auto corner : corners) {
                if (board2D[corner.first][corner.second] == ' ') {
                    makeMove(corner.first, corner.second);
                    return true;
                }
            }
        }
        return false;
    }

    int minimax(int depth, bool isMaximizing) {
        if (checkWin()) {
            return isMaximizing ? -10 + depth : 10 - depth;
        }
        if (checkDraw()) return 0;

        if (isMaximizing) {
            int bestScore = -1000;
            if (boardType == CLASSIC_2D) {
                for (int i = 0; i < boardSize; i++) {
                    for (int j = 0; j < boardSize; j++) {
                        if (board2D[i][j] == ' ') {
                            board2D[i][j] = aiPlayer;
                            moveCount++;
                            int score = minimax(depth + 1, false);
                            board2D[i][j] = ' ';
                            moveCount--;
                            bestScore = max(score, bestScore);
                        }
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = 1000;
            if (boardType == CLASSIC_2D) {
                for (int i = 0; i < boardSize; i++) {
                    for (int j = 0; j < boardSize; j++) {
                        if (board2D[i][j] == ' ') {
                            board2D[i][j] = humanPlayer;
                            moveCount++;
                            int score = minimax(depth + 1, true);
                            board2D[i][j] = ' ';
                            moveCount--;
                            bestScore = min(score, bestScore);
                        }
                    }
                }
            }
            return bestScore;
        }
    }

    void getAIMoveImpossible() {
        if (boardType == ADVANCED_3D) {
            getAIMoveHard();
            return;
        }

        int bestScore = -1000;
        int bestRow = -1, bestCol = -1;

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board2D[i][j] == ' ') {
                    board2D[i][j] = aiPlayer;
                    moveCount++;
                    int score = minimax(0, false);
                    board2D[i][j] = ' ';
                    moveCount--;

                    if (score > bestScore) {
                        bestScore = score;
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
        }

        if (bestRow != -1 && bestCol != -1) {
            makeMove(bestRow, bestCol);
            cout << GREEN << "AI played at position.\n" << RESET;
        }
    }

    void getAIMove() {
        cout << YELLOW << "AI is thinking...\n" << RESET;
        
        switch(difficulty) {
            case EASY:
                getAIMoveEasy();
                break;
            case MEDIUM:
                getAIMoveMedium();
                break;
            case HARD:
                getAIMoveHard();
                break;
            case IMPOSSIBLE:
                getAIMoveImpossible();
                break;
        }
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void displayResult() {
        displayBoard();
        
        if (checkWin()) {
            cout << GREEN << BOLD << "\n🎉 ";
            if (mode == SINGLE_PLAYER) {
                if (currentPlayer == humanPlayer) {
                    cout << player1Name << " WINS! 🎉\n";
                } else {
                    cout << "AI WINS! Better luck next time!\n";
                }
            } else {
                string winner = (currentPlayer == 'X') ? player1Name : player2Name;
                cout << winner << " WINS! 🎉\n";
            }
            cout << RESET;
        } else if (checkDraw()) {
            cout << YELLOW << BOLD << "\n🤝 It's a DRAW! 🤝\n" << RESET;
        }
    }

    void play() {
        setupGame();
        
        while (!gameOver) {
            displayBoard();
            
            if (mode == SINGLE_PLAYER && currentPlayer == aiPlayer) {
                getAIMove();
            } else {
                getHumanMove();
            }

            if (checkWin() || checkDraw()) {
                gameOver = true;
                displayResult();
            } else {
                switchPlayer();
            }
        }
    }

    void playAgain() {
        cout << "\n" << CYAN << "Play again? (y/n): " << RESET;
        char choice;
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            moveCount = 0;
            gameOver = false;
            currentPlayer = 'X';
            initializeBoard();
            play();
        } else {
            cout << MAGENTA << BOLD << "\nThanks for playing GitTac!\n";
            cout << "Created by Michael Semera\n" << RESET;
        }
    }
};

int main() {
    GitTacGame game;
    game.play();
    game.playAgain();
    
    return 0;
}