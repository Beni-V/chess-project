#include "Pawn.h"

//the ctor
Pawn::Pawn(char figureType):
Figure(figureType)
{
    if (figureType != 'p' && figureType != 'P')
    {
        throw InvalidInitializerStringException();
    }
    this->_hasMoved = false;
}

bool Pawn::hasMoved()
{
    return this->_hasMoved;
}

void Pawn::movePiece()
{
    this->_hasMoved = true;
}

bool Pawn::checkIfMoveLegal(std::string move, Board* board, bool checkForCheck)
{
    // will sign the point of moving character on the board
    int x1 = move[0] - 97;
    int y1 = move[1] - 49;

    // will sign the destination point of character on the board
    int x2 = move[2] - 97;
    int y2 = move[3] - 49;

    
    bool ret = true;
    //The three general checks in one function
    generalMoveCheck(board, x1, y1, x2, y2);
    // one forwards
    //2 forwards and hasmoved==false
    //one diagonal
    if ( !((this->getType() == 'p' && y2 - y1 == -1 && x1 == x2) //one forwards black -> down
        || (this->getType() == 'P' && y2 - y1 == 1 && x1 == x2) //one forwards white -> up
        || (this->getType() == 'p' && y2 - y1 == -2 && x1 == x2 && this->_hasMoved == false) //2 forwards , black, down only from start
        || (this->getType() == 'P' && y2 - y1 == 2 && x1 == x2 && this->_hasMoved == false)  //2 forwards , white, up, only from start
        || (this->getType() == 'p' && y2 - y1 == -1 && abs(x1 - x2) == 1 && board->getBoardLocation(x2,y2)!= nullptr) //eating -> diagonal, must be someone there- wont check if other color- already done in the move check
        || (this->getType() == 'P' && y2 - y1 == 1 && abs(x1 - x2) == 1 && board->getBoardLocation(x2, y2) != nullptr)))
    {
        throw InvalidPieceMovementException();
    }
    //makes sure the way is clear
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
