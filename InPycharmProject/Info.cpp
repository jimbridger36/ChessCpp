#include "Universal.h"
#include "Info.h"

namespace Info {
	int enumToPieceVal[16] = {
	0,
	1,
	3,
	3,
	5,
	50,
	8,
	0,
	0,
	-1,
	-3,
	-3,
	-5,
	-50,
	-8,
	0
	};

	// data set by cython (now startUpFunctions)
	int distanceInfoFlat[64][37];


	// set by startUpF...
	// first index is the piece type, second is the direction (0 is null, the loop to check should look for this as the end)
	int directionInfoFlat[16][9] = {};

	




	// [1] is black, [0] is white (if EnP rank is the rank the piece being eaten sits on)
	int colourEnPassantRank[2];
}
