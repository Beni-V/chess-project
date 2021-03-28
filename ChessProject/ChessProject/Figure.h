#pragma once
#ifndef FIGURE_H            // Specifies that the minimum required platform is Windows Vista.
#define FIGURE_H 

#include "Board.h"
#include "ChessExceptions.h"
#include <iostream>
#include <string>

//White: True and big letter
//Black: false and small letter

class Board;
class Figure
{
private:
	char _figureType;
	bool _color;

public:
	Figure(char figureType);
	~Figure(){}; //nothing was allocated dynamically
	bool getColor();
	char getType();
	void setFigureType(char figureType); //also sets the color
	virtual bool checkIfMoveLegal(std::string move, Board* board, bool checkForCheck) =0;
	virtual bool hasMoved() { return true; }
	void CheckCopy(Board* board, std::string& move);
	void CheckFreeMove(int x2, int x1, int y2, int y1, Board* board);
	void generalMoveCheck(Board* board, int x1, int y1, int x2, int y2);
};

#endif