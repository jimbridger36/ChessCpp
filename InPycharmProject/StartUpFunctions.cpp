#include "Universal.h"
#include "ZStuff.h"
#include "StartUpFunctions.h"
#include "Info.h"

namespace StartUpFunctions {


	void InitAll(int ZSeed) {
		setUpColourEnPassantRank();
		setUpDirectionInfoFlat();

		ZStuff::initialiseZArrays(ZSeed);
		std::cout << "initialised" << std::endl;
	}

	static int vecToInt(int dX, int dY) {
		return (dY * 8) + dX;
	};

	static int min(int a, int b) {
		if (a < b) return a;
		else {
			return b;
		}
	}



	void setUpDistanceInfoFlat() {

		for (int rank = 0; rank < 8; rank++) {
			for (int file = 0; file < 8; file++) {
				Info::distanceInfoFlat[rank*8 + file][(0 + 2)*8 + 1 + 2] = 7 - file;
				Info::distanceInfoFlat[rank*8 + file][(1 + 2) * 8 + 1 + 2] = min(7 - rank, 7 - file);
				Info::distanceInfoFlat[rank*8 + file][(1 + 2)*8 + 0 + 2] = 7 - rank;
				Info::distanceInfoFlat[rank*8 + file][(1 + 2)*8 + -1 + 2] = min(file, 7 - rank);
				Info::distanceInfoFlat[rank*8 + file][(0 + 2)*8 + -1 + 2] = file;
				Info::distanceInfoFlat[rank*8 + file][(-1 + 2)*8 + -1 + 2] = min(file, rank);
				Info::distanceInfoFlat[rank*8 + file][(-1 + 2)*8 + 0 + 2] = rank;
				Info::distanceInfoFlat[rank*8 + file][(-1 + 2)*8 + 1 + 2] = min(7 - file, rank);

				//moving in same spot
				Info::distanceInfoFlat[rank*8 + file][0 + 2, 0 + 2] = 0;


				// horse movement (copied and converted from python code in the big comment below
			
				Info::distanceInfoFlat[rank * 8 + file][0 * 8 + 1 + DistanceInfoDirectionOffset]   = file <= 5 and rank <= 6 ? 1 : 0;
				Info::distanceInfoFlat[rank * 8 + file][1 * 8 + 1 + DistanceInfoDirectionOffset]   = file <= 6 and rank <= 5 ? 1 : 0;
				Info::distanceInfoFlat[rank * 8 + file][1 * 8 + 0 + DistanceInfoDirectionOffset]   = file >= 1 and rank <= 5 ? 1 : 0;
				Info::distanceInfoFlat[rank * 8 + file][1 * 8 + -1 + DistanceInfoDirectionOffset]  = file >= 2 and rank <= 6 ? 1 : 0;
				Info::distanceInfoFlat[rank * 8 + file][0 * 8 + -1 + DistanceInfoDirectionOffset]  = file >= 2 and rank >= 1 ? 1 : 0;
				Info::distanceInfoFlat[rank * 8 + file][-1 * 8 + -1 + DistanceInfoDirectionOffset] = file >= 1 and rank >= 2 ? 1 : 0;
				Info::distanceInfoFlat[rank * 8 + file][-1 * 8 + 0 + DistanceInfoDirectionOffset]  = file <= 6 and rank >= 2 ? 1 : 0;
				Info::distanceInfoFlat[rank * 8 + file][-1 * 8 + 1 + DistanceInfoDirectionOffset]  = file <= 5 and rank >= 1 ? 1 : 0;


				/*
				// bloody horse movement
				Info::distanceInfoFlat[rank, file][1 + 2, 2 + 2] = 1 if file <= 5 and rank <= 6 else 0
				Info::distanceInfoFlat[rank, file][2 + 2, 1 + 2] = 1 if file <= 6 and rank <= 5 else 0
				Info::distanceInfoFlat[rank, file][2 + 2, -1 + 2] = 1 if file >= 1 and rank <= 5 else 0
				Info::distanceInfoFlat[rank, file][1 + 2, -2 + 2] = 1 if file >= 2 and rank <= 6 else 0
				Info::distanceInfoFlat[rank, file][-1 + 2, -2 + 2] = 1 if file >= 2 and rank >= 1 else 0
				Info::distanceInfoFlat[rank, file][-2 + 2, -1 + 2] = 1 if file >= 1 and rank >= 2 else 0
				Info::distanceInfoFlat[rank, file][-2 + 2, 1 + 2] = 1 if file <= 6 and rank >= 2 else 0
				Info::distanceInfoFlat[rank, file][-1 + 2, 2 + 2] = 1 if file <= 5 and rank >= 1 else 0
				*/
			}
		}


	}

	void setUpDirectionInfoFlat() {

		// array already initialised to 0 so only need to deal with the non zero cases
/*
#define EMPTY 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define KING 5
#define QUEEN 6
*/
		
		// will do white first then figure out how to spread this to black later
		// to do black will just loop through the black and just set every entry
		// to the entry of the white one
		// this works for everything but pawns which can be done manually

		Info::directionInfoFlat[PAWN][0] = 9; // up and right
		Info::directionInfoFlat[PAWN][1] = 7; // up and left
		
		


		Info::directionInfoFlat[KNIGHT][0] = vecToInt(2,1);
		Info::directionInfoFlat[KNIGHT][1] = vecToInt(1,2);
		Info::directionInfoFlat[KNIGHT][2] = vecToInt(-1,2);
		Info::directionInfoFlat[KNIGHT][3] = vecToInt(-2,1);
		Info::directionInfoFlat[KNIGHT][4] = vecToInt(-2,-1);
		Info::directionInfoFlat[KNIGHT][5] = vecToInt(-1,-2);
		Info::directionInfoFlat[KNIGHT][6] = vecToInt(1,-2);
		Info::directionInfoFlat[KNIGHT][7] = vecToInt(2,-1);





		Info::directionInfoFlat[BISHOP][0] = vecToInt(1,1);
		Info::directionInfoFlat[BISHOP][1] = vecToInt(-1,1);
		Info::directionInfoFlat[BISHOP][2] = vecToInt(-1,-1);
		Info::directionInfoFlat[BISHOP][3] = vecToInt(1,-1);


		Info::directionInfoFlat[ROOK][0] = vecToInt(1,0);
		Info::directionInfoFlat[ROOK][1] = vecToInt(0,1);
		Info::directionInfoFlat[ROOK][2] = vecToInt(-1,0);
		Info::directionInfoFlat[ROOK][3] = vecToInt(0,-1);
		
		
		
		for (int angle = 0; angle < 8; angle++) {

			int index = angle / 2;
			// if it is done by a rook
			int rookOrNot = angle % 2 == 0;


			int pieceToGetInfoFrom;
			if (rookOrNot) {
				pieceToGetInfoFrom = ROOK;
			}
			else {
				pieceToGetInfoFrom = BISHOP;
			}


			Info::directionInfoFlat[KING][angle] = Info::directionInfoFlat[pieceToGetInfoFrom][index];
			Info::directionInfoFlat[QUEEN][angle] = Info::directionInfoFlat[pieceToGetInfoFrom][index];
		}

		// now all the white ones are set

		for (int pieceType = 0; pieceType < 8; pieceType++) {
			for (int entry = 0; entry < 9; entry++) {
				Info::directionInfoFlat[BLACK | pieceType][entry] = Info::directionInfoFlat[pieceType][entry];
			}
		}

		Info::directionInfoFlat[BLACK | PAWN][0] = -9; // down and left
		Info::directionInfoFlat[BLACK | PAWN][1] = -7; // down and right

		// now all the black ones too


	}

	void setUpColourEnPassantRank() {
		// if the enPassant rank is the rank at which the piece being eaten sits on
		Info::colourEnPassantRank[0] = 3;
		Info::colourEnPassantRank[0] = 4;
	}


}
