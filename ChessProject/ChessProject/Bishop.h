#pragma once
#ifndef BISHOP_H
#endif BISHOP_H

#include "Figure.h"

class Bishop : public Figure
{
public:
	Bishop(char charType);
	bool checkIfMoveLegal(std::string move, Board* board, bool checkForCheck) override;
};
