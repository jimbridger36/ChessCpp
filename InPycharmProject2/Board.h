#pragma once
#include "Whtable.h"
#include "ZStuff.h"
#include "Info.h"
#include "Universal.h"
#include "StartUpFunctions.h"
#include <list>
namespace Board {
	// ofcourse a state of 0 just means the game is ongoing

#define ongoing 0
#define drawState 1
#define whiteWins 2
#define blackWins 3



	struct irreversibleState {
		char castleRights;
		char enPassantFile;
		char fiftyMoveCounter;
		char blackToPlay;

		irreversibleState() {
			this->castleRights = 0;
			this->enPassantFile = nullPosition;
			this->fiftyMoveCounter = 0;
			this->blackToPlay = false;
		}
	};;



	class BOARD {
	public:
		int Square[64];
		
		ulong Attacked[2] = {0,0};


		int* getSquarePtr() {
			return (int*)&Square;
		}

		//bool BlackToPlay;

		bool BlackToPlay() {
			return stateStack[this->currentPly].blackToPlay;
		}


		//int fiftyMoveCounter;
		int currentPly;

		Whtable::HT ht;
		int kingPosition[2];
		// PieceLists, possibly with own array;
		// moveStack;
		// irreversibleStateStack(using std);
		bool gameOver;
		int materialBalance;
		ulong ZVal;


		irreversibleState currentState;
		irreversibleState stateStack[maxMoves];
		Move moveStack[maxMoves];


		ulong* getAttackedPtr() {
			return (ulong*) & this->Attacked;
		}

		ulong getAttacked(int index) {
			return Attacked[index];
		}

		void setAttack(int col, ulong value);
		void printAttack0();

		char fileHT[fileCharLength];


		void inline addPiece(int pos, int piece);
		void inline removePiece(int pos);
		void inline transferPiece(int src, int dst);
		//void inline clearCastleRights();
		void inline clearCastleRights(int colour);
		void inline clearCastleRights(int colour, int kingside);
		void inline setEnPFile(int newFile);

		void makeMove(Move move);
		void unmakeMove();


		void genMoves(int col, std::list<Move>* lst);
		void genPosMoves(int pos, std::list<Move> *lst);
		void genBothSidesMoves(std::list<Move> *lst);


		void doIrreversibleZChanges();
		void doIrreversibleZChanges(int oldcurrentPly);
		void doIrreversibleZChanges(irreversibleState OLD, irreversibleState NEW);

		void pushStateToStack();




		BOARD();

		BOARD(const char* fen, char _fileToReadFrom[fileCharLength]);

		BOARD(int _Square[64], irreversibleState _state, char _fileToReadFrom[fileCharLength] = (char*)defaultFile, int currentPly = 0);


		

	};


	void inline BOARD::addPiece(int pos, int piece) {
		assertD(this->Square[pos] == 0);

		this->materialBalance += Info::enumToPieceVal[piece];

		this->ZVal ^= ZStuff::pieceZVals[pos][piece];
		Square[pos] = piece;
	}

	void inline BOARD::removePiece(int pos) {

		this->materialBalance -= Info::enumToPieceVal[Square[pos]];

		this->ZVal ^= ZStuff::pieceZVals[pos][Square[pos]];

		Square[pos] = 0;
	}

	void inline BOARD::transferPiece(int src, int dst) {
		assertD(Square[dst] == 0);

		// putting piece in new position
		this->ZVal ^= ZStuff::pieceZVals[dst][Square[dst]];
		Square[dst] = Square[src];

		// removing piece in old position
		this->ZVal ^= ZStuff::pieceZVals[src][Square[src]];
		Square[src] = 0;
	}

	//void inline BOARD::clearCastleRights() {
	//	this->currentState.castleRights = 0;
	//}

	void inline BOARD::clearCastleRights(int black, int queenside) {
		setBit(currentState.castleRights, black * 2 + queenside);
	}

	void inline BOARD::clearCastleRights(int black) {
		// if black
		// this->currentState.castleRights &= 0b0011;

		// if white
		// this->currentState.castleRights &= 0b1100;

		// this accomplishes the same					white
		this->currentState.castleRights &= 0b11 << (2 * (1 - black));
	}

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
}