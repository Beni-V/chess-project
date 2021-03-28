#include "Queen.h"

//The c'tor
Queen::Queen(char figureType):
    Figure(figureType)
{
    if (figureType != 'q' && figureType != 'Q')
    {
        throw InvalidInitializerStringException();
    }
}

//checks if the given move is legal according to the rules of a queen
//only in a straight line or diagonally
bool Queen::checkIfMoveLegal(std::string move, Board* board, bool checkForCheck)
{
    // will sign the point of moving character on the board
    int x1 = move[0] - 97;
    int y1 = move[1] - 49;

    // will sign the destination point of character on the board
    int x2 = move[2] - 97;
    int y2 = move[3] - 49;

    int tempX, tempY, XIncrementor, YIncrementor;
    bool ret = true;
    //The three general checks in one function

    generalMoveCheck(board, x1, y1, x2,y2);
    //a Diagonal movement requires the difference to be the same in the x and y 
    if (!((x1 == x2 || y1 == y2) || (abs(x1-x2) == abs(y1-y2)))) //a queen only moves in a straigt line or diagonally
    {
        throw InvalidPieceMovementException();
    }
    CheckFreeMove(x2, x1, y2, y1, board);

    //    Board boardCopy(board->getBoardAsString());
    //  boardCopy.forceMove(move);
    if (checkForCheck)
    {
        CheckCopy(board, move);
    }
    return true;
}
