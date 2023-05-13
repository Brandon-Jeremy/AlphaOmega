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

enum MoveType {
    NORMAL,        //Normal move
    CASTLING,      //Castling move
    PROMOTION,     //Pawn promotion move
    EN_PASSANT,    //En passant move
    INVALID        //Invalid move
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

        /**
         * Move information
        */
        struct Move{
            int sourceSquare;
            int targetSquare;
            Piece movedPiece;
            Piece capturedPiece;
            MoveType moveType;

            Move(int source, int target, Piece moved, Piece captured, MoveType type){
                sourceSquare = source;
                targetSquare = target;
                movedPiece = moved;
                capturedPiece = captured;
                moveType = type;
            }

        };

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

        // Move related functions
        std::vector<Move> generateLegalMoves();
        bool isMoveLegal(const Move& move);
};

#endif  // BOARD_H
