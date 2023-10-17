#include <random>
#include <iostream>
#pragma once
#include "Universal.h"
namespace ZStuff {
	extern ulong pieceZVals[64][16];
	extern ulong blackToPlayZ, castlingRightsZ[16], enPassantFileZ[9];

	extern std::mt19937_64 gen;

	ulong HASH(const char* str);

	ulong getNextRand();

	void seedGenerator(int seed);

	void initialiseZArrays(int seed);

}