#pragma once
#ifndef CHESSEXCEPTIONS_H
#define CHESSEXCEPTIONS_H

#include <exception>

class TypeException : public std::exception
{
public:
	virtual const char* what() const
	{
		return "Invalid type";
	}
};

class InvalidMsg : public std::exception
{
public:
	virtual const char* what() const
	{
		return "Invalid message";
	}
};

class inCheckException : public std::exception //1
{
public:
	virtual const char* what() const
	{
		return "1";
		//return "Invalid type";
	}
};

class InvalidInitializerStringException : public std::exception
{
public:
	virtual const char* what() const
	{
		return "Invalid initializer string";
	}
};

class InvalidSourceColorMovementException : public std::exception //exception number 2
{
public:
	virtual const char* what() const
	{
		return "2";
		//return "Invalid source color movement. Not the right turn.";
	}
};

class InvalidDestinationColorMovementException : public std::exception //exception number 3
{
public:
	virtual const char* what() const
	{
		return "3";
		//return "There is a piece of the same color at the destination";
	}
};

class PutSelfInCheckException : public std::exception //exception number 4
{
public:
	virtual const char* what() const
	{
		return "4";
		//return "The move will put the player in self-check";
	}
};

class InvalidIndexException : public std::exception //exception number 5
{
public:
	virtual const char* what() const
	{
		return "5";
		//return "The index is out of the board";
	}
};

class InvalidPieceMovementException : public std::exception //exception number 6
{
public:
	virtual const char* what() const
	{
		return "6";
		//return "The piece cannot move that way";
	}
};

class FigureInTheWayException : public std::exception //exception number 6
{
public:
	virtual const char* what() const
	{
		return "6";
		//return "There is a figure in the way";
	}
};

class SourceIsDestException : public std::exception //exception number 7
{
public:
	virtual const char* what() const
	{
		return "7";
		//return "The source and destination are the same";
	}
};

class WhiteWonException : public std::exception //exception number 8.1
{
public:
	virtual const char* what() const
	{
		return "8";
		//return "Game over. White won";
	}
};

class BlackWonException : public std::exception //exception number 8.2
{
public:
	virtual const char* what() const
	{
		return "8";
		//return "Game over. Black won";
	}
};
#endif