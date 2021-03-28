#pragma once
#ifndef KNIGHT_H            // Specifies that the minimum required platform is Windows Vista.
#define KNIGHT_H 

#include "Figure.h"
#include "Board.h"
#include "ChessExceptions.h"
#include <iostream>
#include <string>

//White: True and big letter
//Black: false and small letter

class Knight : public Figure
{
public:
	Knight(char figureType); //The c'tor
	~Knight() {}; //nothing was allocated dynamically
	bool checkIfMoveLegal(std::string move, Board* board, bool checkForCheck) override; //checks if the move is legal
};

#endif