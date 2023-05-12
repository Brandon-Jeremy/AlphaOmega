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

        Piece getPieceFromFENCharacter(char piece){
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

        void setupPositionFromFEN(const std::string& fen){
            // Reset the board to its initial state
            for(int i =0;i<64;i++){
                squares[i]=EMPTY;
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
            
            // for(const auto& token:tokens){
            //     std::cout << token << std::endl;
            // }
                        
        }

        void printBoard(){
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


};

int main()
{
    Board board;
    board.setupPositionFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    board.printBoard();
    return 0;
}
