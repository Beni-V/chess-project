#pragma once
#ifndef KING_H            // Specifies that the minimum required platform is Windows Vista.
#define KING_H 

#include "Figure.h"
#include "Board.h"
#include "ChessExceptions.h"
#include <iostream>
#include <string>

//White: True and big letter
//Black: false and small letter

class King : public Figure
{
private:
	bool _hasMoved;

public:
	King(char figureType); //The c'tor
	~King() {}; //nothing was allocated dynamically

	bool hasMoved() override; //checks if the piece has moved yet

	void movePiece(); //updates the hasmoved field

	bool checkIfMoveLegal(std::string move, Board* board, bool checkForCheck) override; //checks if the move is legal
};

#endif