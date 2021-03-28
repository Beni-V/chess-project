#include "Board.h"
#include "ChessExceptions.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "King.h"
#include "Pawn.h"
#include "Bishop.h"

#define BOARD_ROW_LENGTH 8
#define BOARD_COL_LENGTH 8

/// <summary>
/// the c'tor
/// </summary>
/// <param name="board">the string board containg the build for the board</param>
Board::Board(const std::string board)
{
	this->setBoard(board);
}

// will destruct Board object
Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; i < 8; i++)
		{
			delete this->_2DBoard[i][j];
		}
	} // delete dynamic 2d array
	//might need to loop through
}

// getter for board as simple string 
std::string Board::getBoardAsString() const
{
	return this->_stringBoard;
}

/// <summary>
/// creates the board based on a string
/// </summary>
/// <param name="board">the string of the board</param>
void Board::setBoard(std::string board)
{
	if (board.length() != 65)
	{
		throw InvalidInitializerStringException();
	}
	for (int i = 0; i < board.length() - 1; i++)
	{
		switch (board[i])
		{
		case 'K':
		case 'k':
			this->_2DBoard[i % 8][7-(i / 8)] = new King(board[i]);
			break;
		case 'q':
		case 'Q':
			this->_2DBoard[i % 8][7 - (i / 8)] = new Queen(board[i]);
			break;
		case 'r':
		case 'R':
			this->_2DBoard[i % 8][7 - (i / 8)] = new Rook(board[i]);
			break;
		case 'n':
		case 'N':
			this->_2DBoard[i % 8][7 - (i / 8)] = new Knight(board[i]);
			break;
		case 'b':
		case 'B':
			this->_2DBoard[i % 8][7 - (i / 8)] = new Bishop(board[i]);
			break;
		case 'p':
		case 'P':
			this->_2DBoard[i % 8][7-(i / 8)] = new Pawn(board[i]);
			//this->_2DBoard[i % 8][7 - (i / 8)] = nullptr;
			break;
		case '#':
			this->_2DBoard[i % 8][7 - (i / 8)] = nullptr;
			break;
		default:
			throw TypeException();
		}
	}
	if (board[64] == '0')
	{
		this->_turn = true;
	}
	else
	{
		this->_turn = false;
	}

	this->_stringBoard = board;
}

// will check if move is legal and make him if it is
void Board::makeMove(std::string move)
{
	// will sign the point of moving character on the board
	int x1 = move[0] - 97; //a -> 0
	int y1 = move[1] - 49; //'1' - > 0

	// will sign the destination point of character on the board
	int x2 = move[2] - 97;
	int y2 = move[3] - 49;

	if (this->_2DBoard[x1][y1] == nullptr)
	{
		throw InvalidSourceColorMovementException();
	}

	if ( this->_2DBoard[x1][y1]->checkIfMoveLegal(move, this, true)) // check if the move is legal
	{
		
		this->_2DBoard[x2][y2] = this->_2DBoard[x1][y1]; // set the character from source to destination point
		this->_2DBoard[x1][y1] = nullptr; // set nullptr in source point
		
		updateStringBoard(); // update the stirng board according to changes in 2DBoard
		if (this->checkCheck(!(this->getTurn())))
		{
			this->updateTurn(!(this->getTurn()));
			if (this->checkMate(!(this->getTurn())))
			{
				throw WhiteWonException();
			}
			throw inCheckException();
		}
		this->updateTurn(!(this->getTurn()));
	}

	
	

}

// will make the move without checking if it legal or not
void Board::forceMove(std::string move)
{
	// will sign the point of moving character on the board
	int x1 = move[0] - 97;
	int y1 = move[1] - 49;

	// will sign the destination point of character on the board
	int x2 = move[2] - 97;
	int y2 = move[3] - 49;

	this->_2DBoard[x2][y2] = this->_2DBoard[x1][y1]; // set the character from source to destination point
	this->_2DBoard[x1][y1] = nullptr; // set nullptr in source point

	updateStringBoard(); // update the stirng board according to changes in 2DBoard
}

// will print the board
void Board::printBoard()
{
	std::cout << this->_stringBoard;
}


/// <summary>
/// checks if a cetrain color is in check
/// </summary>
/// <param name="color">the color to check if is in check</param>
/// <returns>true if in check</returns>
bool Board::checkCheck(bool color)
{
	bool tempTurn = this->getTurn();
	this->updateTurn(!(color));

	char kingInCheckChar;
	std::string kingPlace = "";
	std::string moveString = "";
	bool inCheck = false; //the return value
	bool tempb;
	if (color) //finding the specific char of king based on color in order to find the king in check
	{
		kingInCheckChar = 'K';
	}
	else
	{
		kingInCheckChar = 'k';
	}
	//first we need to find the king in check
	for (int i = 0; i < BOARD_COL_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_COL_LENGTH; j++)
		{
			if (this->_2DBoard[i][j] != nullptr && this->_2DBoard[i][j]->getType() == kingInCheckChar)
			{
				kingPlace.push_back(char(i + 97)); //we are creating a move string based the kings location
				kingPlace.push_back(char(j + 49)); //like d7
				i = BOARD_COL_LENGTH;//double break
				j = BOARD_COL_LENGTH;
			}
		}
	}
	//now we go through all of the players and check if the move to king is legal- he's in check
	for (int i = 0; i < BOARD_COL_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_COL_LENGTH; j++)
		{
			//need to check piece is of opposite color
			if (this->_2DBoard[i][j] == nullptr || this->_2DBoard[i][j]->getColor() == color)
			{
				continue;
			}
			moveString.clear(); //create move string //movestring conains a1d8
			moveString.push_back(char(i + 97)); //src part of string
			moveString.push_back(char(j + 49));
			moveString.append(kingPlace); //dest part of string
			try
			{
				tempb = this->_2DBoard[i][j]->checkIfMoveLegal(moveString, this, false);//we go through every piece, and check if the move to the king is legal- he is in check
			}
			catch (std::exception e)
			{
				continue;
			}
			if (tempb) 
			{
				inCheck = true;
				i = BOARD_COL_LENGTH;//double break
				j = BOARD_COL_LENGTH;
			}
		}
	}
	this->updateTurn(tempTurn);//retrun to start position
	return inCheck;
}

bool Board::getTurn()
{
	return this->_turn;
}

void Board::updateTurn(bool newTurn)
{
	this->_turn = newTurn;
	if (newTurn)
	{
		this->_stringBoard[64] == '0';
	}
	else
	{
		this->_stringBoard[64] == '1';
	}
}

Figure* Board::getBoardLocation(int x, int y)
{
	//return this->_2DBoard[y][x];
	return this->_2DBoard[x][y];
	
}

/*
input: color of side that will be checked for mate
output: true (player in mate) or false (player not in mate)
function will check if player in mate or nor
*/
bool Board::checkMate(bool color)
{
	bool tempTurn = this->getTurn();
	this->updateTurn(!(color));
	std::string tempMove = "";

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				for (int l = 0; l < 8; l++)
				{
					tempMove.clear();
					tempMove.push_back(char(i + 97));
					tempMove.push_back(char(j + 49));
					tempMove.push_back(char(k + 97));
					tempMove.push_back(char(l + 49));
					//check if all the moves in the board are legal
					//the move is only legal if after the turn, the king is no longer in check
					//if no such move exists, 
					//the king is in mate- a check that no matter what exists
					try
					{
						if (this->_2DBoard[i][j] != nullptr && this->_2DBoard[i][j]->checkIfMoveLegal(tempMove, this, true))
						{
							return false;
						}
					}
					catch (std::exception e)
					{
						continue;
					}
					
				}
			}
		}
	}
	this->updateTurn(tempTurn);
	return true;
}

/*
this function will update the stringBoard according to data in 2DArray
*/
void Board::updateStringBoard()
{
	int i = 0;
	int j = 0;
	int tempIndex = 0;
	for (int i = BOARD_ROW_LENGTH - 1; i >= 0; i--)
	{
		for (j =  0; j < BOARD_COL_LENGTH ; j++)
		{
			//tempIndex = i * 8 + i;
			if (this->_2DBoard[j][i] == nullptr)
			{
				this->_stringBoard[tempIndex] = '#';
			}
			else
			{
				this->_stringBoard[tempIndex] = this->_2DBoard[j][i]->getType();
			}
			tempIndex++;
		}
	}
}

//hello