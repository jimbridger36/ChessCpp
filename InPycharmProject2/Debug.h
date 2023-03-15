#pragma once
#include "Board.h"
#include "Info.h"
#include "StartUpFunctions.h"
#include "Universal.h"
#include "Whtable.h"
#include "ZStuff.h"

namespace Debug {
	void printDirectionInfoFlat();

	void saveDistanceInfoFlatToFile(const char* fileName = "DebugOutput.txt");

	void genAllMovesDB(Board::BOARD board);

	int* getDirInfoPointer();

	int* getDistInfoFlat();
}
