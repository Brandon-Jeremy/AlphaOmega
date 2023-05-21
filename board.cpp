#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

#include "board.h"

    
/**
 * Chess board will always be represented with the order a-h with a on the
 * right side of the board.
*/
Board::Board() {
    // Initialize the board to the starting position
    for (int squareIndex = 0; squareIndex < 64; squareIndex++) {
        squares[squareIndex] = Piece::EMPTY;
    }
    Board::sideToMove = 'w'; // White to play initially

    // Casting for white Kingside and Queenside
    // Casting for black kingside and queenside
    Board::castlingAvailability = "KQkq"; 
    Board::enPassantTargetSquare = "-";
    Board::halfMoveClock = 0;
    Board::fullMoveNumber = 1;
    
}   

/**
 * Rank is the values that run horizontal [1-8]
 * File is the letters that run vertical [a-h]
 * 
 * Mailbox representation of the board means a single line
 * is used to represent the board of 64 tiles.
 * 
 * rank 8 & file a: index 0 on the board
 * rank 7 & file a: index 8 on the board
*/
Piece Board::getPiece(int file, int rank){
    int index = rank*8+file;
    return squares[index];
}

void Board::setPiece(int rank, int file, Piece piece){
    int index = rank*8+file;
    squares[index]=piece;
}

Piece Board::getPieceFromFENCharacter(char piece){
    switch(piece){
        case 'P': return PAWN;
        case 'N': return KNIGHT;
        case 'B': return BISHOP;
        case 'R': return ROOK;
        case 'Q': return QUEEN;
        case 'K': return KING;
        case 'p': return BLACK_PAWN;
        case 'n': return BLACK_KNIGHT;
        case 'b': return BLACK_BISHOP;
        case 'r': return BLACK_ROOK;
        case 'q': return BLACK_QUEEN;
        case 'k': return BLACK_KING;
        default: return EMPTY;
    }
}

void Board::setupPositionFromFEN(const std::string& fen){
    // Reset the board to its initial state
    for(int squareIndex =0;squareIndex<64;squareIndex++){
        squares[squareIndex]=EMPTY;
    }
    
    /**
     * Parse the FEN string and set up the board accordingly
     * Example: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
     * Split the FEN string into tokens
     * */ 
    
    char delimiter = '/';
    // Vector to store the tokens extracted from the fen notation
    std::vector<std::string> tokens;

    // Stream for the fen notation
    std::stringstream ss(fen);

    std::string short_fen;
    while(getline(ss,short_fen,' ')){
        tokens.push_back(short_fen);
    }

    /**
     * rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
     * lowercase is for black
     * each / represents a new row
     * numbers = empty squares
    */
    
    // Start with black top left so A7 which is rank 7 file A
    std::string initialPosition = tokens[0];
    int rank = 7;
    int file = 0;
    for(char piece:initialPosition){
        if(piece == '/'){
            rank--;
            file=0;
        }
        else if(std::isdigit(piece)){
            int emptySquares = piece - '0';
            file += emptySquares;
        }
        else{

            Piece p = getPieceFromFENCharacter(piece);
            std::cout<<"Setting up board with piece "<<p<<" using piece "<<piece<<std::endl;
            setPiece(rank, file, p);
            file++;
        }
    }

    sideToMove=tokens[1][0];
    castlingAvailability=tokens[2];
    enPassantTargetSquare=tokens[3];
    halfMoveClock=std::stoi(tokens[4]);
    fullMoveNumber=std::stoi(tokens[5]);

    for(const auto& token:tokens){
        std::cout << token << std::endl;
    }
                
}

void Board::printBoard(){
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int index = rank * 8 + file;
            Piece piece = getPiece(file, rank);

            // Print the piece character
            switch (piece) {
                case EMPTY:
                    std::cout << '.';
                    break;
                case PAWN:
                    std::cout << 'P';
                    break;
                case KNIGHT:
                    std::cout << 'N';
                    break;
                case BISHOP:
                    std::cout << 'B';
                    break;
                case ROOK:
                    std::cout << 'R';
                    break;
                case QUEEN:
                    std::cout << 'Q';
                    break;
                case KING:
                    std::cout << 'K';
                    break;
                case -PAWN:
                    std::cout << 'p';
                    break;
                case -KNIGHT:
                    std::cout << 'n';
                    break;
                case -BISHOP:
                    std::cout << 'b';
                    break;
                case -ROOK:
                    std::cout << 'r';
                    break;
                case -QUEEN:
                    std::cout << 'q';
                    break;
                case -KING:
                    std::cout << 'k';
                    break;
            }
        }
        std::cout << std::endl;
    }
}

Piece* Board::getSquares(){
    return squares;
}

std::string Board::exportFEN() {
    std::string FEN = "";
    int emptyCount = 0;

    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int tile = rank * 8 + file;
            Piece piece = squares[tile];

            if (piece == EMPTY) {
                emptyCount++;
            } else {
                if (emptyCount > 0) {
                    FEN += std::to_string(emptyCount);
                    emptyCount = 0;
                }

                switch (piece) {
                    case PAWN:
                        FEN += 'P';
                        break;
                    case KNIGHT:
                        FEN += 'N';
                        break;
                    case BISHOP:
                        FEN += 'B';
                        break;
                    case ROOK:
                        FEN += 'R';
                        break;
                    case QUEEN:
                        FEN += 'Q';
                        break;
                    case KING:
                        FEN += 'K';
                        break;
                    case BLACK_PAWN:
                        FEN += 'p';
                        break;
                    case BLACK_KNIGHT:
                        FEN += 'n';
                        break;
                    case BLACK_BISHOP:
                        FEN += 'b';
                        break;
                    case BLACK_ROOK:
                        FEN += 'r';
                        break;
                    case BLACK_QUEEN:
                        FEN += 'q';
                        break;
                    case BLACK_KING:
                        FEN += 'k';
                        break;
                }
            }
        }

        if (emptyCount > 0) {
            FEN += std::to_string(emptyCount);
            emptyCount = 0;
        }

        if (rank > 0) {
            FEN += '/';
        }
    }

    // Append additional FEN information
    FEN += " " + std::string(1,sideToMove);// Convert the char to a string
    FEN += " " + castlingAvailability;
    FEN += " " + enPassantTargetSquare; //En passant target square (- or e3)
    FEN += " " + std::to_string(halfMoveClock);
    FEN += " " + std::to_string(fullMoveNumber);

    return FEN;
}

std::string Board::getSideToMove(){
    return std::string(1,sideToMove);
}

std::string Board::getCastlingAvailability(){
    return castlingAvailability;
}

std::string Board::getEnPassantTargetSquare(){
    return enPassantTargetSquare;
}

int Board::getHalfMoveClock(){
    return halfMoveClock;
}

int Board::getFullMoveNumber(){
    return fullMoveNumber;
}

void Board::validPawnmove(std::vector<Move>& legalMoves, int rank, int file, int squareIndex){
    //If the pawn is on the first rank, it has the chance to:
    //move once, move twice, capture if possible
    //This determines if we are moving forward as white or black. Refer to BoardIndex.png for insight
    int forwardDirection = (sideToMove == 'w')?1:-1;
    std::cout<<"Current Rank: "<<rank<<std::endl;
    std::cout<<"Current File: "<<file<<std::endl;

    // ===================================================================

                                /* Move up one tile */
    int targetSquare = squareIndex+forwardDirection*8;
    if(squares[targetSquare]==EMPTY){
        //Target square is empty so it is a legal move.
        //Struct initialization with what kind of move was made
        int targetRank = targetSquare/8;
        if(sideToMove=='w'){
            if(targetRank==7){
                for (Piece promotionPiece : {QUEEN, ROOK, BISHOP, KNIGHT}) {
                    Move promotionMove{squareIndex, targetSquare, PAWN, EMPTY, PROMOTION};
                    promotionMove.promotedPiece = promotionPiece;
                    legalMoves.emplace_back(promotionMove);
                }
            }
            else{
                Move pawn{squareIndex,targetSquare,PAWN,EMPTY,NORMAL};
                legalMoves.emplace_back(pawn);
            }
        }
        else{
            if(targetRank==0){
                for (Piece promotionPiece : {BLACK_QUEEN, BLACK_ROOK, BLACK_BISHOP, BLACK_KNIGHT}) {
                    Move promotionMove{squareIndex, targetSquare, PAWN, EMPTY, PROMOTION};
                    promotionMove.promotedPiece = promotionPiece;
                    legalMoves.emplace_back(promotionMove);
                }
            }
            else{
                Move pawn{squareIndex,targetSquare,BLACK_PAWN,EMPTY,NORMAL};
                legalMoves.emplace_back(pawn);
            }
        }
            std::cout<<"[1] Moving 1 tile up "<<squareIndex<<std::endl;
    }                

    // ===================================================================

                            /* Capture piece */
    if(file==0){ //A file
        //As white, assume tile is 48. Capture can happen on 41
        //As black, assume tile is 8. Capture can happen on 17
        int targetSquare = 0;
        if (sideToMove == 'w')
            //white to capture
            targetSquare = squareIndex + forwardDirection * 9;  // Capture to the right
        else
            //black to capture
            targetSquare = squareIndex + forwardDirection * 7;  // Capture to the left

        if (targetSquare >= 0 && targetSquare <= 63) {
            //target is still on the board
            Piece capturedPiece = squares[targetSquare];
            int targetRank = targetSquare/8;

            // Check if the captured piece is of the opposite color
            if (capturedPiece != EMPTY && capturedPiece * forwardDirection < 0 && targetRank!=rank) {
                if(sideToMove=='w'){
                    if(targetRank==7){
                        for (Piece promotionPiece : {QUEEN, ROOK, BISHOP, KNIGHT}) {
                            Move promotionMove{squareIndex, targetSquare, PAWN, capturedPiece, PROMOTION_CAPTURE};
                            promotionMove.promotedPiece = promotionPiece;
                            legalMoves.emplace_back(promotionMove);
                        }
                    }
                    else{               
                        Move capture{squareIndex,targetSquare,PAWN,capturedPiece,CAPTURE};
                        legalMoves.emplace_back(capture);
                    }
                }
                else{
                    if(targetRank==0){
                        for (Piece promotionPiece : {BLACK_QUEEN, BLACK_ROOK, BLACK_BISHOP, BLACK_KNIGHT}) {
                            Move promotionMove{squareIndex, targetSquare, PAWN, capturedPiece, PROMOTION_CAPTURE};
                            promotionMove.promotedPiece = promotionPiece;
                            legalMoves.emplace_back(promotionMove);
                        }
                    }
                    else{
                        Move capture{squareIndex,targetSquare,BLACK_PAWN,capturedPiece,CAPTURE};
                        legalMoves.emplace_back(capture);
                    }
                }                
                std::cout << "[2] Adding capture: " << squareIndex << " to " << targetSquare << std::endl;
            }
        }

    }
    else if(file==7){ //H file
        //As white, assume tile is 48. Capture can happen on 41
        //As black, assume tile is 8. Capture can happen on 17
        int targetSquare = 0;
        if (sideToMove == 'w')
            //white to capture
            targetSquare = squareIndex + forwardDirection * 7;  // Capture to the left
        else
            //black to capture
            targetSquare = squareIndex + forwardDirection * 9;  // Capture to the right

        if (targetSquare >= 0 && targetSquare <= 63) {
            //target is still on the board
            Piece capturedPiece = squares[targetSquare];
            int targetRank = targetSquare/8;

            // Check if the captured piece is of the opposite color
            if (capturedPiece != EMPTY && capturedPiece * forwardDirection < 0 && targetRank!=rank) {
                if(sideToMove=='w'){
                    if(targetRank==7){
                        for (Piece promotionPiece : {QUEEN, ROOK, BISHOP, KNIGHT}) {
                            Move promotionMove{squareIndex, targetSquare, PAWN, capturedPiece, PROMOTION_CAPTURE};
                            promotionMove.promotedPiece = promotionPiece;
                            legalMoves.emplace_back(promotionMove);
                        }
                    }
                    else{
                        Move capture{squareIndex,targetSquare,PAWN,capturedPiece,CAPTURE};
                        legalMoves.emplace_back(capture);
                    }
                }
                else{
                    if(targetRank==0){
                        for (Piece promotionPiece : {BLACK_QUEEN, BLACK_ROOK, BLACK_BISHOP, BLACK_KNIGHT}) {
                            Move promotionMove{squareIndex, targetSquare, PAWN, capturedPiece, PROMOTION_CAPTURE};
                            promotionMove.promotedPiece = promotionPiece;
                            legalMoves.emplace_back(promotionMove);
                        }
                    }
                    else{
                        Move capture{squareIndex,targetSquare,BLACK_PAWN,capturedPiece,CAPTURE};
                        legalMoves.emplace_back(capture);
                    }
                }                
                std::cout << "[3] Adding capture: " << squareIndex << " to " << targetSquare << std::endl;
            }
        }
    }
    else{
                            /* Capture a piece on the right or left side */
        //Assume tile is 11, capture on the right is 20 as a pawn which is 2 as black
        int targetSquare = squareIndex+forwardDirection*9;

        if (targetSquare >= 0 && targetSquare <= 63) {
            //target is still on the board
            Piece capturedPiece = squares[targetSquare];
            int targetRank = targetSquare/8;


            // Check if the captured piece is of the opposite color
            if (capturedPiece != EMPTY && capturedPiece * forwardDirection < 0 && targetRank!=rank) {
                if(sideToMove=='w'){
                    Move capture{squareIndex,targetSquare,PAWN,capturedPiece,CAPTURE};
                    legalMoves.emplace_back(capture);
                }
                else{
                    Move capture{squareIndex,targetSquare,BLACK_PAWN,capturedPiece,CAPTURE};
                    legalMoves.emplace_back(capture);
                }                
                std::cout << "[5] Adding capture: " << squareIndex << " to " << targetSquare << std::endl;
            }
        }
        //Assume tile is 11, capture on the left is 18 as a pawn which is 4 as black
        targetSquare = squareIndex+forwardDirection*7;
        if (targetSquare >= 0 && targetSquare <= 63) {
            //target is still on the board
            Piece capturedPiece = squares[targetSquare];
            int targetRank = targetSquare/8;

            // Check if the captured piece is of the opposite color
            if (capturedPiece != EMPTY && capturedPiece * forwardDirection < 0 && targetRank!=rank) {
                if(sideToMove=='w'){
                    if(targetRank==7){
                        for (Piece promotionPiece : {QUEEN, ROOK, BISHOP, KNIGHT}) {
                            Move promotionMove{squareIndex, targetSquare, PAWN, capturedPiece, PROMOTION_CAPTURE};
                            promotionMove.promotedPiece = promotionPiece;
                            legalMoves.emplace_back(promotionMove);
                        }
                    }
                    else{
                        Move capture{squareIndex,targetSquare,PAWN,capturedPiece,CAPTURE};
                        legalMoves.emplace_back(capture);
                    }
                }
                else{
                    if(targetRank==0){
                        for (Piece promotionPiece : {BLACK_QUEEN, BLACK_ROOK, BLACK_BISHOP, BLACK_KNIGHT}) {
                            Move promotionMove{squareIndex, targetSquare, PAWN, capturedPiece, PROMOTION_CAPTURE};
                            promotionMove.promotedPiece = promotionPiece;
                            legalMoves.emplace_back(promotionMove);
                        }
                    }
                    else{
                        Move capture{squareIndex,targetSquare,BLACK_PAWN,capturedPiece,CAPTURE};
                        legalMoves.emplace_back(capture);
                    }
                }                
                std::cout << "[6] Adding capture: " << squareIndex << " to " << targetSquare << std::endl;
            }
        }
    }
    if(rank==1 || rank==6){ //This piece is a pawn on its starting square
                            /* Move up two tiles */
        targetSquare = squareIndex+forwardDirection*16;
        int singleSquarePush = squareIndex+forwardDirection*8;
        if(squares[targetSquare]==EMPTY && squares[singleSquarePush]==EMPTY){
            //Target square 2 tiles above starting piece is empty
            if(sideToMove=='w'){
                Move pawn{squareIndex,targetSquare,PAWN,EMPTY,DOUBLE_PAWN_PUSH};
                legalMoves.emplace_back(pawn);
            }
            else{
                Move pawn{squareIndex,targetSquare,BLACK_PAWN,EMPTY,DOUBLE_PAWN_PUSH};
                legalMoves.emplace_back(pawn);
            }
            std::cout<<"[4] Moving 2 tiles up "<<squareIndex<<std::endl;
        }
    }

    //En Passant 
    if(enPassantTargetSquare!="-"){
        if(sideToMove=='w'){
            // std::cout<<"EnPassant for white"<<std::endl;
            //White can only enPassant on the 4th rank.
            int targetSquare = algebraicToNumeric(enPassantTargetSquare);
            int targetRank = targetSquare/8;
            if(rank==targetRank-1){
                Move enPassant{squareIndex,targetSquare,PAWN,BLACK_PAWN,EN_PASSANT};
                std::cout << "[7] Adding capture enPassant: " << squareIndex << " to " << targetSquare << std::endl;
                legalMoves.emplace_back(enPassant);
            }
        }
        else if(sideToMove=='b'){
            //Black can enPassant here
            int targetSquare = algebraicToNumeric(enPassantTargetSquare);
            int targetRank = targetSquare/8;
            if(rank==targetRank+1){
                Move enPassant{squareIndex,targetSquare,BLACK_PAWN,PAWN,EN_PASSANT};
                std::cout << "[8B] Adding capture enPassant: " << squareIndex << " to " << targetSquare << std::endl;
                legalMoves.emplace_back(enPassant);
            }
            
        }
    }
}

void Board::validBishopMove(std::vector<Move>& legalMoves, int rank, int file, int squareIndex){
    int directions[4] = {9, 7, -9, -7};
    //up-right, up-left, down-right, down-left

    for(int direction:directions){
        int currentSquare = squareIndex;
        int targetSquare = currentSquare+direction;

        while (isValidSquare(targetSquare) && !isEdgeFile_Bishop(currentSquare, direction)){
            if (squares[targetSquare] == EMPTY){
                Move normalMove{squareIndex, targetSquare, squares[squareIndex], EMPTY, NORMAL};
                std::cout<<"Bishop moved from "<<squareIndex<<" to "<<targetSquare<<std::endl;
                legalMoves.emplace_back(normalMove);
            }
            else if (isOpponentPiece(targetSquare)){
                Piece capturedPiece = squares[targetSquare];
                Move captureMove{squareIndex, targetSquare, squares[squareIndex], capturedPiece, CAPTURE};
                std::cout<<"[Capture] Bishop moved from "<<squareIndex<<" to "<<targetSquare<<std::endl;
                legalMoves.emplace_back(captureMove);
                break;  //Cannot move further in this direction
            }
            else{
                break;  //Encountered own piece
            }

            currentSquare = targetSquare;
            targetSquare += direction;
        }
    }
}

void Board::validKnightMove(std::vector<Move>& legalMoves, int rank, int file, int squareIndex) {
    int knightOffset[8] = {-17, -15, -10, -6, 6, 10, 15, 17};

    for (int offset:knightOffset){
        int currentSquare = squareIndex;
        int targetSquare = currentSquare + offset;

        // Check if the target square is within the valid range of the board
        if (isValidSquare(targetSquare) && isValidKnightTarget(currentSquare, targetSquare)){
            //Target square is empty and we can occupy it
            if (squares[targetSquare] == EMPTY){
                Move normalMove{squareIndex, targetSquare, squares[squareIndex], EMPTY, NORMAL};
                legalMoves.emplace_back(normalMove);
                std::cout << "Moving knight from " << currentSquare << " to " << targetSquare << std::endl;
            }
            //Target square is occupied by opponent's piece
            else if (isOpponentPiece(targetSquare)){
                Piece capturedPiece = squares[targetSquare];
                Move captureMove{squareIndex, targetSquare, squares[squareIndex], capturedPiece, CAPTURE};
                legalMoves.emplace_back(captureMove);
                std::cout << "[Capture] Knight moved from " << squareIndex << " to " << targetSquare << std::endl;
            }
        }
    }
}


bool Board::isValidSquare(int squareIndex){
    return squareIndex >= 0 && squareIndex < 64;
}

bool Board::isOpponentPiece(int squareIndex){
    Piece piece = squares[squareIndex];
    return (sideToMove == 'w' && piece < 0) || (sideToMove == 'b' && piece > 0);
}

bool Board::isEdgeFile_Bishop(int squareIndex, int direction){
    int currentFile = squareIndex % 8;
    int targetFile = (squareIndex + direction) % 8;
    return (currentFile == 0 && targetFile == 7) || (currentFile == 7 && targetFile == 0);
}

bool Board::isValidKnightTarget(int sourceSquare, int targetSquare){
    int sourceRank = sourceSquare/8;
    int sourceFile = sourceSquare%8;
    int targetRank = targetSquare/8;
    int targetFile = targetSquare%8;

    //Knight moves can only occur within a range of two ranks and one file in any direction
    int rankDiff = std::abs(sourceRank - targetRank);
    int fileDiff = std::abs(sourceFile - targetFile);

    return rankDiff <= 2 && fileDiff <= 2 && rankDiff + fileDiff == 3;
}

/**
 * Board:: since we are accessing a private array called squares 
 * If squares were public we wouldn't need Board::
*/
std::vector<Move> Board::generateLegalMoves(char sideToMove){
    std::vector<Move> legalMoves;

    std::cout<<"Side to move is "<<sideToMove<<std::endl;

    //Loop done from 0-64 to take advantage of 1D array and parallelize
    for(int squareIndex=0;squareIndex<64;squareIndex++){
        Piece piece = squares[squareIndex];
        if(sideToMove=='w'){
            //If the tile we are currently on corresponds to the correct color piece to move
            int rank = squareIndex/8;
            int file = squareIndex % 8;
            if(piece == PAWN){
                std::cout<<"White Pawn found on "<<rank<<" "<<file<<std::endl;
                validPawnmove(legalMoves,rank,file,squareIndex);
            }
            else if(piece == BISHOP){
                std::cout<<"White Bishop found on "<<rank<<" "<<file<<std::endl;
                validBishopMove(legalMoves,rank,file,squareIndex);
            }
            else if(piece == KNIGHT){
                std::cout<<"White Knight found on "<<rank<<" "<<file<<std::endl;
                validKnightMove(legalMoves,rank,file,squareIndex);

            }
        }
        else{
            int rank = squareIndex/8;
            int file = squareIndex % 8;
            if(piece == BLACK_PAWN){
                std::cout<<"Black Pawn found on "<<rank<<" "<<file<<std::endl;
                validPawnmove(legalMoves,rank,file,squareIndex);          
            }
            else if(piece == BLACK_BISHOP){
                std::cout<<"Black Bishop found on "<<rank<<" "<<file<<std::endl;
                validBishopMove(legalMoves,rank,file,squareIndex);
            }
            else if(piece == BLACK_KNIGHT){
                std::cout<<"Black Knight found on "<<rank<<" "<<file<<std::endl;
                validKnightMove(legalMoves,rank,file,squareIndex);

            }
        }
    }

    return legalMoves;

}

bool Board::isColoredMove(char sideToMove, const Piece&piece){
    if(piece == 0)
        return false;
    if(sideToMove == 'w' && piece>=PAWN)
        return true;
    if(sideToMove == 'b' && piece<=BLACK_PAWN)
        return true;
    return false;

}

/**
 * string notation of square and returns its value between 0-63
*/
int Board::algebraicToNumeric(std::string algebraic){
    //Validate the input before parsing
    if(algebraic.length()==2){
        //Example of an algebraic representation of a square is e2
        char file=algebraic[0];
        char rank=algebraic[1];

        //Validate rank and file numbers and letters
        if((file>='a' && file<='h')&&(rank>='1' && rank<='8')){
            int numericFile = file-'a';
            int numericRank = rank-'1';

            int squareIndex = numericRank*8+numericFile;
            return squareIndex;
        }
        return -1;
    }
    return -1;
}

std::string Board::numericToAlgebraic(int squareIndex){
    /**
     * Given a number to represent an index on the chess board, convert to human readable 
     * notation
     */
    //Ensure the square index is within the valid range
    if (squareIndex<0|| squareIndex>63) {
        return "";
    }

    //Map the square index to algebraic notation
    int rank = 8-(squareIndex/8);
    int file = squareIndex%8;
    std::string algebraic = "";
    algebraic += ('a'+file);
    algebraic += ('1'+rank);

    return algebraic;
}

int Board::parseFEN(Board board){
    std::ifstream file("testFEN.txt"); // Replace "filename.txt" with the actual name and path of your file
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return 1; // Exit the program if the file cannot be opened
    }

    std::string line;
    bool proceed = true;
    while (std::getline(file, line) && proceed) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); // Remove the carriage return character '\r' if present
        }
        if (!line.empty() && line.back() == '\n') {
            line.pop_back(); // Remove the newline character '\n' if present
        }
        
        // Process each line here
        std::cout << line << std::endl;

        // Store the line in a string variable
        std::string storedLine = line;

        board.setupPositionFromFEN(storedLine);
        board.printBoard();

        std::vector<Move> legalMoves;

        legalMoves = board.generateLegalMoves(board.sideToMove);

        for (const auto& move : legalMoves) {
            std::cout << move.sourceSquare<< " ";
        }


        std::cout << "\nContinue?";
        std::cin >> proceed;
        if(!proceed){
            break;
        }
        // Clear the line variable for the next iteration
        line.clear();
        legalMoves.clear();
    }

    file.close();
    return 0;
}

int main()
{
    Board board;
    // board.setupPositionFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    // board.printBoard();

    board.parseFEN(board);
    // std::cout<<board.exportFEN()<<std::endl;

    // std::vector<Move> legalMoves;

    // legalMoves = board.generateLegalMoves('w');

    // for (const auto& move : legalMoves) {
    //     std::cout << move.sourceSquare<< " ";
    // }
    // int num = board.algebraicToNumeric("e5");
    // std::string alg = board.numericToAlgebraic(num);
    // std::cout<<"\n"<<num<<" "<<alg<<std::endl;

    // std::cout<<"\n"<<board.getEnPassantTargetSquare()<<std::endl;

    return 0;
}
