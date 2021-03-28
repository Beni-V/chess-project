#include "Rook.h"

//The c'tor for rook
Rook::Rook(char figureType):
    Figure(figureType)
{
    if (figureType != 'r' && figureType != 'R')
    {
        throw InvalidInitializerStringException();
    }
    this->_hasMoved = false;
}


// Checks if the rook was moved from its original position
bool Rook::hasMoved()
{
    return this->_hasMoved;
}

//update the has moved field
void Rook::movePiece()
{
    this->_hasMoved = true;
}


//checks if the given move is legal according to the rules of a rook
//only in a straight line
bool Rook::checkIfMoveLegal(std::string move, Board* board, bool checkForCheck)
{
    // will sign the point of moving character on the board
    int x1 = move[0] - 97;
    int y1 = move[1] - 49;

    // will sign the destination point of character on the board
    int x2 = move[2] - 97;
    int y2 = move[3] - 49;

    //The three general checks in one function
    generalMoveCheck(board, x1, y1, x2, y2);
    // !(x1==x2 || y1==y2)
    // check that movement is according to the rules of a rook
    if (x1 != x2 && y1 != y2) //a rook only moves in a straigt line, so one of the indexes must stay the same
    {
        throw InvalidPieceMovementException();
    }
    CheckFreeMove(x2, x1, y2, y1, board);
    //no we must check that we dont put ourself in check
    //prevent looping
    if (checkForCheck)
    {
        CheckCopy(board, move);
        this->movePiece();
    }
    return true;
}
