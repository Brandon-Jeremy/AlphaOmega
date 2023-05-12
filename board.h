#ifndef BOARD_H
#define BOARD_H

enum Piece {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    BLACK_PAWN = -PAWN,
    BLACK_KNIGHT = -KNIGHT,
    BLACK_BISHOP = -BISHOP,
    BLACK_ROOK = -ROOK,
    BLACK_QUEEN = -QUEEN,
    BLACK_KING = -KING
    };

class Board {
    private:
        Piece squares[64];

        //Fen information
        char sideToMove;
        std::string castlingAvailability;
        std::string enPassantTargetSquare;
        int halfMoveClock;
        int fullMoveNumber;

    public:
        Board(); 

        //Piece methods
        Piece getPiece(int file, int rank);
        void setPiece(int rank, int file, Piece piece);
        Piece getPieceFromFENCharacter(char piece);
        void setupPositionFromFEN(const std::string& fen);
        void printBoard();

        // FEN-related functions
        std::string exportFEN();
        std::string getSideToMove();
        std::string getCastlingAvailability();
        std::string getEnPassantTargetSquare();
        int getHalfMoveClock();
        int getFullMoveNumber();
};

#endif  // BOARD_H
