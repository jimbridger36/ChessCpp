#include <random>
#pragma once
#include "Universal.h"
#include "ZStuff.h"

namespace ZStuff {
	ulong pieceZVals[64][16];
	ulong blackToPlayZ, castlingRightsZ[16], enPassantFileZ[9];

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
		for (int primitiveBit = 0; primitiveBit < 4; primitiveBit++) {
			castlingRightsZ[1 << primitiveBit] = getNextRand();
		}
		uchar tmp = 0;

		for (int b0 = 0; b0 <= 1; b0++)
			for (int b1 = 0; b1 <= 1; b1++)
				for (int b2 = 0; b2 <= 1; b2++)
					for (int b3 = 0; b3 <= 1; b3++) {
						tmp = 0;
						if (b0)
							tmp ^= castlingRightsZ[1 << 0];
						if (b1)
							tmp ^= castlingRightsZ[1 << 1];
						if (b2)
							tmp ^= castlingRightsZ[1 << 2];
						if (b3)
							tmp ^= castlingRightsZ[1 << 3];

						castlingRightsZ[(b3 << 3) + (b2 << 2) + (b1 << 1) + (b0 << 0)] = tmp;

					};;;;

		castlingRightsZ[0] = 0;

		
		// enPassant
		enPassantFileZ[0] = 0;
		for (int i = 1; i < 9; i++)
			enPassantFileZ[i] = getNextRand();


	}
}