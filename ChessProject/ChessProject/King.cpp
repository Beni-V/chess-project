#include "King.h"

//The c'tor
King::King(char figureType):
	Figure(figureType)
{
	if (figureType != 'k' && figureType != 'K')
	{
		throw InvalidInitializerStringException();
	}
	this->_hasMoved = false;
}

//Checks if the king was moved from its original position
bool King::hasMoved()
{
	return this->_hasMoved;
}

//update the has moved field
void King::movePiece()
{
	this->_hasMoved = true;
}


//checks if the given move is legal according to the rules of a rook
//only in a one away or castling
bool King::checkIfMoveLegal(std::string move, Board* board, bool checkForCheck)
{
    // will sign the point of moving character on the board
    int x1 = move[0] - 97;
    int y1 = move[1] - 49;

    // will sign the destination point of character on the board
    int x2 = move[2] - 97;
    int y2 = move[3] - 49;


    bool ret = true;
    bool moveRook = false;
    std::string rookMove = "";
    //The three general checks in one function

    generalMoveCheck(board, x1, y1, x2, y2);

    //castling

    //moving right ->
    if (x2 - x1 == 2 && y1 == y2 && !(this->_hasMoved) && !(board->checkCheck(this->getColor())))
    {
        if (board->getBoardLocation(x1 + 1, y1) == nullptr//spots must be empty
            && board->getBoardLocation(x1 + 2, y1) == nullptr
            && board->getBoardLocation(x1 + 3, y1) == nullptr
            && board->getBoardLocation(x1 + 4, y1) != nullptr
            && (board->getBoardLocation(x1 + 4, y1)->getType() == 'r'//a rook must be in original spot
                || board->getBoardLocation(x1 + 4, y1)->getType() == 'R')
            && !(board->getBoardLocation(x1 + 4, y1)->hasMoved())) //rook must nut have moved
        {
            rookMove.push_back(x1 + 4 + 97);
            rookMove.push_back(y1 + 49);
            rookMove.push_back(x1 + 1 + 97);
            rookMove.push_back(y1 + 49);
            moveRook = true;
            
            
        }
    }//left <-
    if (x2 - x1 == -2 && y1 == y2 && !(this->_hasMoved) && !(board->checkCheck(this->getColor())))
    {
        if (board->getBoardLocation(x1 - 1, y1) == nullptr
            && board->getBoardLocation(x1 - 2, y1) == nullptr
            && board->getBoardLocation(x1 - 3, y1) != nullptr
            && (board->getBoardLocation(x1 - 3, y1)->getType() == 'r'
                || board->getBoardLocation(x1 - 3, y1)->getType() == 'R')
            && !(board->getBoardLocation(x1 - 3, y1)->hasMoved()))
        {
            rookMove.push_back(x1 - 3 + 97);
            rookMove.push_back(y1 + 49);
            rookMove.push_back(x1 - 1 + 97);
            rookMove.push_back(y1 + 49);
            moveRook = true;
        }
    }//move normally
    else if ((abs(x1-x2)>1) || (abs(y1 - y2) > 1)) //a king only moves one space
    {
        throw InvalidPieceMovementException();
    }

    //check if a dest has same color
    if (board->getBoardLocation(x2, y2) != nullptr && board->getBoardLocation(x2, y2)->getColor() == this->getColor())
    {
        throw InvalidDestinationColorMovementException();
    }

    if (checkForCheck)
    {
        CheckCopy(board, move);
        this->movePiece();
    }
    if (moveRook)
    {//only after we check that the king is not in check, may we move the rook
        board->forceMove(rookMove);  //e1g1
    }
    

    return true;
}
