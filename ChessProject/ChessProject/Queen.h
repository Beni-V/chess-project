#pragma once
#ifndef QUEEN_H            // Specifies that the minimum required platform is Windows Vista.
#define QUEEN_H 

#include "Figure.h"
#include "Board.h"
#include "ChessExceptions.h"
#include <iostream>
#include <string>

//White: True and big letter
//Black: false and small letter

class Queen : public Figure
{
public:
	Queen(char figureType); //The c'tor
	~Queen() {}; //nothing was allocated dynamically
	bool checkIfMoveLegal(std::string move, Board* board, bool checkForCheck) override; //checks if the move is legal
};

#endif