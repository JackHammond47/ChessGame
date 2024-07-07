#include <iostream>
using namespace std;

//ChatGPT was used interactively to assist in editing the code, specifically there were errors with some of the syntax which chatGPT helped correct and also copied 
//some of my longer and clunky sections over and asked the tool to condense some of the code and how to write code all on 1 line using ?. 
//I, Jackson Hammond, have carefully reviewed said text and take ultimate responsibility for the content of this code.

class Piece {
public:
    virtual bool isValidMove(int startX, int startY, int endX, int endY) = 0;
    char symbol;
    bool isWhite;
};

class King : public Piece {
public:
    King(bool isWhite) { this->isWhite = isWhite; symbol = isWhite ? 'K' : 'k'; }
    bool isValidMove(int startX, int startY, int endX, int endY) override {
        return abs(startX - endX) <= 1 && abs(startY - endY) <= 1;
    }
};
class Queen : public Piece {
public:
    Queen(bool isWhite) { this->isWhite = isWhite; symbol = isWhite ? 'Q' : 'q'; }
    bool isValidMove(int startX, int startY, int endX, int endY) override {
        int dx = abs(startX - endX);
        int dy = abs(startY - endY);
        return (dx == dy) || (startX == endX) || (startY == endY);
    }
};
class Rook : public Piece {
public:
    Rook(bool isWhite) { this->isWhite = isWhite; symbol = isWhite ? 'R' : 'r'; }
    bool isValidMove(int startX, int startY, int endX, int endY) override {
        return (startX == endX) || (startY == endY);
    }
};
class Bishop : public Piece {
public:
    Bishop(bool isWhite) { this->isWhite = isWhite; symbol = isWhite ? 'B' : 'b'; }
    bool isValidMove(int startX, int startY, int endX, int endY) override {
        return abs(startX - endX) == abs(startY - endY);
    }
};
class Knight : public Piece {
public:
    Knight(bool isWhite) { this->isWhite = isWhite; symbol = isWhite ? 'N' : 'n'; }
    bool isValidMove(int startX, int startY, int endX, int endY) override {
        return (abs(startX - endX) == 1 && abs(startY - endY) == 2) || (abs(startX - endX) == 2 && abs(startY - endY) == 1);
    }
};
class Pawn : public Piece {
public:
    Pawn(bool isWhite) { this->isWhite = isWhite; symbol = isWhite ? 'P' : 'p'; }
    bool isValidMove(int startX, int startY, int endX, int endY) override {
        int direction = isWhite ? 1 : -1; // White pawns move up, black pawns move down
        int startRow = isWhite ? 1 : 6; // White pawns start at row 1 (index 2), black at row 6 (index 7)
        // Single-step move
        if (startX == endX && endY == startY + direction) {
            return true;
        }

        // Double-step move on initial move
        if (startX == endX && startY == startRow && endY == startY + 2 * direction) {
            return true;
        }

        // Capturing move (diagonal)
        if (abs(startX - endX) == 1 && endY == startY + direction) {
            return true;
        }
        return false;
    }
};

class Board {
private:
    Piece* board[8][8];
public:
    Board() {
        initializeBoard();
    }

    // Initialize the board with pieces in starting positions
    void initializeBoard() {
        // Place pawns
        for (int x = 0; x < 8; ++x) {
            board[x][1] = new Pawn(true);  // White pawns
            board[x][6] = new Pawn(false); // Black pawns
        }

        // Place rooks
        board[0][0] = new Rook(true);  // White rook
        board[7][0] = new Rook(true);  // White rook
        board[0][7] = new Rook(false); // Black rook
        board[7][7] = new Rook(false); // Black rook

        // Place knights
        board[1][0] = new Knight(true);  // White knight
        board[6][0] = new Knight(true);  // White knight
        board[1][7] = new Knight(false); // Black knight
        board[6][7] = new Knight(false); // Black knight

        // Place bishops
        board[2][0] = new Bishop(true);  // White bishop
        board[5][0] = new Bishop(true);  // White bishop
        board[2][7] = new Bishop(false); // Black bishop
        board[5][7] = new Bishop(false); // Black bishop

        // Place queens
        board[3][0] = new Queen(true);   // White queen
        board[3][7] = new Queen(false);  // Black queen

        // Place kings
        board[4][0] = new King(true);    // White king
        board[4][7] = new King(false);   // Black king

        // Fill the rest of the board with nullptr to represent empty squares
        for (int x = 0; x < 8; ++x) {
            for (int y = 2; y < 6; ++y) {
                board[x][y] = nullptr;
            }
        }
    }

    bool movePiece(int startX, int startY, int endX, int endY) {
    Piece* piece = board[startX][startY];
    if (piece && piece->isValidMove(startX, startY, endX, endY)) {
        Piece* targetPiece = board[endX][endY];
        if (targetPiece && targetPiece->isWhite != piece->isWhite) {
            delete board[endX][endY]; // Remove the captured piece from memory
            board[endX][endY] = nullptr;
        }
        board[endX][endY] = piece;
        board[startX][startY] = nullptr;
        return true;
    }
    return false;
}

    void display() {
        for (int y = 0; y < 8; ++y) {
            for (int x = 0; x < 8; ++x) {
                if (board[x][y]) {
                    std::cout << board[x][y]->symbol << ' ';
                } else {
                    std::cout << ". ";
                }
            }
            std::cout << std::endl;
        }
    }

    ~Board() {
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                delete board[x][y];
            }
        }
    }
};

int main() {
    cout << "Welcome to Chess!\n";
    cout << "The board is an 8x8 grid displayed from top left to bottom right with a 0 index.\n";
    cout << "White pieces are in capitals and black pieces are in lowercase.\n";
    cout << "Take turns typing the coordinate of the piece you want to move and the square you want to move to.\n";
    cout << "For example, moving the white leftmost pawn forward 2 squares would be entered as \"0 1 0 3\".\n";
    cout << "Game over when the loser's king is captured.\n";
    cout << "Let's begin!\n\n";

    Board board;
    while (true) {
        board.display();
        int startX, startY, endX, endY;
        std::cout << "Enter move (startX startY endX endY): ";
        std::cin >> startX >> startY >> endX >> endY;
        if (!board.movePiece(startX, startY, endX, endY)) {
            std::cout << "Invalid move, try again." << std::endl;
        }
    }
    return 0;
}