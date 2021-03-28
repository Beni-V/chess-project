/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Board.h"

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));

	
	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	

	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0\0"); // just example...
	//strcpy_s(msgToGraphics, "rnbkqbnr################################################RNBKQBNR0\0"); // just example...

	
	
	Board myBoard(msgToGraphics);


	
	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		
		// YOUR CODE
		try
		{
			if (msgFromGraphics.length() != 4)
			{
				throw InvalidMsg();
			}
			myBoard.makeMove(msgFromGraphics);
			strcpy_s(msgToGraphics, "0");
		}
		catch (InvalidMsg i)
		{
			std::cout << "ERROR: " << i.what() << std::endl;
		}
		catch (std::exception& e)
		{
			strcpy_s(msgToGraphics, e.what());
		}
	

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   


		//
		myBoard.printBoard();

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}