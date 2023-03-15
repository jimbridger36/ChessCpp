#include "Whtable.h"
#include "ZStuff.h"
#include "Info.h"
#include "Universal.h"
#include "StartUpFunctions.h"
#include "Board.h"
using namespace Whtable;

namespace Board {
// ofcourse a state of 0 just means the game is ongoing


	
	


	// BOARD class attributes
	/*
		bool BlackToPlay;
		int fiftyMoveCounter;
		int currentPly;
		Whtable::HT ht;
		int Square[64];
		int kingPosition[2];
		// PieceLists, possibly with own array;
		// moveStack;
		// irreversibleStateStack(using std);
		bool gameOver;
		int materialBalance;

		char fileHT[fileCharLength];
	*/


	

	void BOARD::pushStateToStack() {
		this->stateStack[currentPly + 1] = currentState;
	}


	BOARD::BOARD(){
		char fileToRead[fileCharLength] = {0};

			
		std::string str = defaultFile;

		for (std::string::size_type i = 0; i < str.size(); i++)
			fileToRead[i] = str[i];


		ht = HT(fileToRead);
			
		
	};

	BOARD::BOARD(const char* fen, char _fileToReadFrom[fileCharLength]) {
		
		int rank = 0, file = 0;


		for (int i = 0; fen[i] != 0; i++) {
			// if they are blank spaces
			if ((fen[i] <= '9') && (fen[i] >= '0'))
				file += fen[i] - '0';
			else if (fen[i] == '/') {
				file = 0; rank++;
			}


		}






	}


	BOARD::BOARD(int _Square[64], irreversibleState _state, char _fileToReadFrom[fileCharLength], int _currentPly) {

			ht = HT(_fileToReadFrom);

			this->currentPly = _currentPly;
			this->currentState = _state;

			this->kingPosition[0] = nullPosition;
			this->kingPosition[1] = nullPosition;

			// set Square
			for (int pos = 0; pos < 64; pos++) {
				
				if (_Square[pos] != 0)
					addPiece(pos, _Square[pos]);
				else
					Square[pos] = 0;

				if (decolour(_Square[pos]) == KING)
					this->kingPosition[isblack(_Square[pos])] = pos;
			}

			// checking kings are there
			if (kingPosition[0] == nullPosition)
				std::cout << "white king is not on the board" << std::endl;
			if (kingPosition[1] == nullPosition)
				std::cout << "black king is not on the board" << std::endl;
			assert(kingPosition[0] != nullPosition and kingPosition[1] != nullPosition);
			

			// doing irreversible state
			{
				irreversibleState blank = irreversibleState(); 
				this->doIrreversibleZChanges(blank, _state);
			}









		}


	};





	/*

	attributes:
		BlackToPlay
		fiftyMoveCounter
		currentPly
		ht
		Square
		kingPosition[2]
		PieceLists, possibly with own array
		moveStack
		irreversibleStateStack (using std)
		gameOver
		drawFlag
		winner
		materialBalance



	Cython get/setters:
		getSquare




	*/
