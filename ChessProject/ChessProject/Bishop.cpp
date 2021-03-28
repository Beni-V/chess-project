#include "Bishop.h"

Bishop::Bishop(char charType) : Figure(charType)
{

}

bool Bishop::checkIfMoveLegal(std::string move, Board* board, bool checkForCheck)
{
	// will sign the point of moving character on the board
	int x1 = move[0] - 97;
	int y1 = move[1] - 49;

	// will sign the destination point of character on the board
	int x2 = move[2] - 97;
	int y2 = move[3] - 49;

	// will be the temp location for checking if the move is legal
	int tempX = move[0] - 97;
	int tempY = move[1] - 49;
	//The three general checks in one function
	generalMoveCheck(board, x1, y1, x2, y2);
	if (abs(x1 - x2) != abs(y1 - y2)) // will check if figure move is in the right form
	{
		throw InvalidIndexException();
	}
	CheckFreeMove(x2, x1, y2, y1, board);

	if (checkForCheck)
	{
		CheckCopy(board, move);
	}

	return true; // if move passed all conditions, return true
}
