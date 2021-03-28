#pragma once
#ifndef PAWN_H           // Specifies that the minimum required platform is Windows Vista.
#define PAWN_H

#include "Figure.h"
#include "Board.h"
#include "ChessExceptions.h"
#include <iostream>
#include <string>

class Pawn : public Figure
{
private:
	bool _hasMoved;

public:
	Pawn(char figureType); //The c'tor
	~Pawn(){}; //nothing was allocated dynamically

	bool hasMoved(); //checks if the piece has moved yet

	void movePiece(); //updates the hasmoved field

	bool checkIfMoveLegal(std::string move, Board* board, bool checkForCheck) override; //checks if the move is legal

};













#endif
