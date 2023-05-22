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
    DOUBLE_PAWN_PUSH, //Pawn moving 2 tiles upward
    CASTLING,      //Castling move
    PROMOTION,     //Pawn promotion move
    EN_PASSANT,    //En passant move
    CAPTURE,       //Capturing move
    PROMOTION_CAPTURE,  //Capture and promote
    INVALID        //Invalid move
};

/**
 * Move information
*/
struct Move{
    int sourceSquare;
    int targetSquare;
    Piece movedPiece;
    Piece capturedPiece;
    MoveType moveType;
    Piece promotedPiece;

    Move(int source, int target, Piece moved, Piece captured, MoveType type){
        sourceSquare = source;
        targetSquare = target;
        movedPiece = moved;
        capturedPiece = captured;
        moveType = type;
        promotedPiece = EMPTY;
    }

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
        Piece* getSquares();
        int parseFEN(Board board);

        // FEN-related functions
        std::string exportFEN();
        std::string getSideToMove();
        std::string getCastlingAvailability();
        std::string getEnPassantTargetSquare();
        int getHalfMoveClock();
        int getFullMoveNumber();

        //Move related functions
        std::vector<Move> generateLegalMoves(char sideToMove);
        bool isMoveLegal(const Move& move);
        //Helper function for if a piece corresponds to the right color
        bool isColoredMove(char sideToMove, const Piece&piece);
        void validPawnmove(std::vector<Move>& legalMoves, int rank, int file, int squareIndex);
        void validBishopMove(std::vector<Move>& legalMoves, int rank, int file, int squareIndex);
        void validKnightMove(std::vector<Move>& legalMoves, int rank, int file, int squareIndex);
        void validRookMove(std::vector<Move>& legalMoves, int rank, int file, int squareIndex);
        void validQueenMove(std::vector<Move>& legalMoves, int rank, int file, int squareIndex);
        int algebraicToNumeric(std::string algebraic);
        std::string numericToAlgebraic(int squareIndex);

        bool isValidSquare(int squareIndex);
        bool isOpponentPiece(int squareIndex);
        bool isEdgeFile_Bishop(int squareIndex, int direction);
        bool isValidKnightTarget(int squareIndex, int direction);
};  


#endif  // BOARD_H
