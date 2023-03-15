#include <random>
#pragma once
#include "Universal.h"
#include "ZStuff.h"

namespace ZStuff {
	ulong pieceZVals[64][16];
	ulong blackToPlayZ, castlingRightsZ[4], enPassantFileZ[8];

	std::mt19937_64 gen;

	ulong HASH(const char* str){

		ulong hash = 5381;
		int c;

		while (c = *str++)
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

		return hash;
	}

	ulong getNextRand() {
		return gen.operator()();
	}

	void seedGenerator(int seed) {
		// seeded
		gen.seed(seed);
		// now to get numbers


	}

	void initialiseZArrays(int seed) {
		for (int i = 0; i < 64; i++)
			for (int j = 0; j < 16; j++)
				pieceZVals[i][j] = getNextRand();;

		// also need to do misc stuff

		// blackToPlay
		blackToPlayZ = getNextRand();

		// castlingRights
		for (int i = 0; i < 4; i++)
			castlingRightsZ[i] = getNextRand();
		
		// enPassant
		for (int i = 0; i < 8; i++)
			enPassantFileZ[i] = getNextRand();


	}
}