#include "Figure.h"

/// <summary>
/// The c'tor
/// </summary>
/// <param name="figureType">The figure's type</param>
Figure::Figure(char figureType)
{
	this->setFigureType(figureType);
}

/// <summary>
/// Gets the figure's color
/// </summary>
/// <returns>The figure's color</returns>
bool Figure::getColor()
{
	return this->_color;
}

/// <summary>
/// Gets the figure's type
/// </summary>
/// <returns>The figure's type</returns>
char Figure::getType()
{
	return this->_figureType;
}

/// <summary>
/// sets the figure's type and color
/// </summary>
/// <param name="figureType">the new figure type</param>
void Figure::setFigureType(char figureType)
{
	if (figureType == 'k'
		|| figureType == 'q'
		||figureType == 'r'
		|| figureType == 'n'
		|| figureType == 'b'
		|| figureType == 'p')
	{
		this->_figureType = figureType;
		this->_color = false;
	}
	else if(figureType == 'K'
		|| figureType == 'Q'
		|| figureType == 'R'
		|| figureType == 'N'
		|| figureType == 'B'
		|| figureType == 'P')
	{
		this->_figureType = figureType;
		this->_color = true;
	}
	else
	{
		throw TypeException();
	}
}


//Creates a copy of the board and checks for check
void Figure::CheckCopy(Board* board, std::string& move)
{
    Board boardCopy(board->getBoardAsString());
    boardCopy.forceMove(move);
    boardCopy.updateTurn(!(board->getTurn()));
    if (boardCopy.checkCheck(this->getColor())) //if in check -> move not legal -> false
    {
        throw PutSelfInCheckException();
    }
}

//checks if the way to the dest if free
//no one is ion the way
//and also that the piece at the end is not of same color
void Figure::CheckFreeMove(int x2, int x1, int y2, int y1, Board* board)
{
    int tempX, tempY, XIncrementor, YIncrementor;
    //we will now find the how the loop must change
    //if we go directly right- the x incrementor will be plus one and the y zero
    //left xi = -1, yi =0 
    //up xi = 0, yi = 1
    //down xi = 0, yi = -1
    if ((x2 - x1) > 0)
    {
        XIncrementor = 1;
    }
    else if ((x2 - x1) < 0)
    {
        XIncrementor = -1;
    }
    else
    {
        XIncrementor = 0;
    }
    if ((y2 - y1) > 0)
    {
        YIncrementor = 1;
    }
    else if ((y2 - y1) < 0)
    {
        YIncrementor = -1;
    }
    else
    {
        YIncrementor = 0;
    }

    //must start from next one
    tempX = x1 + XIncrementor; //the is obviously a tile in the original location
    tempY = y1 + YIncrementor;
    while (!(tempX == x2 && tempY == y2)) //while we haven't reached the dest location
    {
        if (board->getBoardLocation(tempX, tempY) != nullptr)
        {
            throw FigureInTheWayException();
        }
        tempX += XIncrementor; //almost like ++, but might be --, or just stay the same
        tempY += YIncrementor;
    }
    //check that at dest there isnt a piece of same color
    if (board->getBoardLocation(x2, y2) != nullptr && board->getBoardLocation(x2, y2)->getColor() == this->getColor())
    {
        throw InvalidDestinationColorMovementException();
    }
}

//the general movement checks
void Figure::generalMoveCheck(Board* board, int x1, int y1, int x2, int y2)
{
    //check that color is of the turn
    if (board->getTurn() != this->getColor())
    {
        throw InvalidSourceColorMovementException();
    }//movement is on the board
    if (x1 > 7 || x1 < 0 || y1 > 7 || y1 < 0 || x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0)
    {
        throw InvalidIndexException();
    }//the piece must move - cannot stay on same place
    if (x1 == x2 && y1 == y2)
    {
        throw SourceIsDestException();
    }
}
