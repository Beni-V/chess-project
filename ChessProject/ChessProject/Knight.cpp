#include "Knight.h"

Knight::Knight(char figureType) :
    Figure(figureType)
{
    if (figureType != 'n' && figureType != 'N')
    {
        throw InvalidInitializerStringException();
    }
}

//checks if the given move is legal according to the rules of a queen
//only +3 +1
bool Knight::checkIfMoveLegal(std::string move, Board* board, bool checkForCheck)
{
    // will sign the point of moving character on the board
    int x1 = move[0] - 97;
    int y1 = move[1] - 49;

    // will sign the destination point of character on the board
    int x2 = move[2] - 97;
    int y2 = move[3] - 49;

    //The three general checks in one function

    generalMoveCheck(board, x1, y1, x2, y2);
    //night must move +3 +1, x and y must be 1 and 3
    if (!((abs(x1 - x2) == 1 && abs(y1 - y2) == 2) || (abs(x1 - x2) == 2 && abs(y1 - y2) == 1)))
    {
        throw InvalidPieceMovementException();
    }

    if (board->getBoardLocation(x2, y2) != nullptr && board->getBoardLocation(x2, y2)->getColor() == this->getColor())
    {
        throw InvalidDestinationColorMovementException();
    }
    if (checkForCheck)
    {
        CheckCopy(board, move);
    }
    
    return true;
}
