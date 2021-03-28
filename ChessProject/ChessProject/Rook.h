#pragma once
#ifndef ROOK_H            // Specifies that the minimum required platform is Windows Vista.
#define ROOK_H 

#include "Figure.h"
#include "Board.h"
#include "ChessExceptions.h"
#include <iostream>
#include <string>

//White: True and big letter
//Black: false and small letter

class Rook : public Figure 
{
private:
	bool _hasMoved;

public:
	Rook(char figureType); //The c'tor
	~Rook() {}; //nothing was allocated dynamically

	bool hasMoved(); //checks if the piece has moved yet

	void movePiece(); //updates the hasmoved field

	bool checkIfMoveLegal(std::string move, Board* board, bool checkForCheck) override; //checks if the move is legal
	
};

#endif