#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Board{
    private:
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
        Piece squares[64];
    
    public:
        /**
         * Chess board will always be represented with the order a-h with a on the
         * right side of the board.
        */
        Board(){
            for (int i = 0;i<64;i++){
                squares[i]=EMPTY;
            }
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
        Piece getPiece(int file, int rank){
            int index = rank*8+file;
            return squares[index];
        }

        void setPiece(int rank, int file, Piece piece){
            int index = rank*8+file;
            squares[index]=piece;
        }

};