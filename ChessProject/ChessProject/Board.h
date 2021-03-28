#pragma once
#ifndef BOARD_H            // Specifies that the minimum required platform is Windows Vista.
#define BOARD_H 

#include "Figure.h"
#include <iostream>
#include <string>

class Figure;

class Board
{
private:
	Figure* _2DBoard[8][8]; // will save the board as 2D array with figure objects
	std::string _stringBoard; // will save the board as simple string (as given in the start)
	bool _turn; // will sign who should do the turn (true - white. false - black) 

	void updateStringBoard(); //will update the string board according to 2dArray board

public:
	Board(const std::string board);
	~Board();
	std::string getBoardAsString() const;
	void setBoard(std::string board);
	void makeMove(std::string move);
	void forceMove(std::string move); // will make the move without checking if the move is legal
	void printBoard();
	bool checkCheck(bool color); // will check if player's king in check (which player will be checked passed in parameters)
	bool getTurn();
	void updateTurn(bool newTurn);
	Figure* getBoardLocation(int x, int y);
	bool checkMate(bool color); // this function will check if current player in mate
	
};
// Change this to the appropriate value to target other versions of Windows.
#endif