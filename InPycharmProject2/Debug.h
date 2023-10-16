#pragma once
#include "Board.h"
#include "Info.h"
#include "StartUpFunctions.h"
#include "Universal.h"
#include "Whtable.h"
#include "ZStuff.h"

namespace Debug {
	void printDirectionInfoFlat();

	void savedistanceInfoAdd18ToFile(const char* fileName = "DebugOutput.txt");

	Move* genAllMovesDB(Board::BOARD &board, int& num);

	int* getDirInfoPointer();

	int* getDistInfoFlat(int* ptr);

	void checkDistance(bool printTrue);

	void printAttack0D(Board::BOARD &board);

	ulong printZVal(Board::BOARD &board);

}
