#include "Universal.h"
#include "ZStuff.h"
#include "StartUpFunctions.h"
#include "Info.h"
#include <fstream>



//#define distanceInfoFile fileLibPath + "distanceInfoFile.dat"

#ifdef FROMCYTHON
#define distanceInfoFile "InPycharmProject2/distanceInfoFile.dat"
#else
#define distanceInfoFile "distanceInfoFile.dat"
#endif



namespace StartUpFunctions {


	void InitAll(int ZSeed) {
		setUpColourEnPassantRank();
		setUpDirectionInfoFlat();
		loadDistanceInfoFlat();
		setCharToPieceArray();

		ZStuff::initialiseZArrays(ZSeed);
		std::cout << "initialised" << std::endl;

		std::cout << arr1[0] << std::endl;
		std::cout << abc << std::endl;

	}

	static int vecToInt(int dX, int dY) {
		return (dY * 8) + dX;
	};

	static int min(int a, int b) {
		if (a < b) {
			return a; 
		}
		else {
			return b;
		}
	}

	
	
	void loadDistanceInfoFlat() {
	
		std::ifstream rf(distanceInfoFile, std::ios::in | std::ios::binary);

		char buffer[64 * 37 * 4];


		int numBytes = 0;
		struct stat results;
		if (stat(distanceInfoFile, &results) == 0) {
			numBytes = results.st_size;
		}
		else {
			printf("failed to read file with name: ");
			printf(distanceInfoFile);
			printf("\n");
			return;
		}
		int number = numBytes;

		rf.read(buffer, 64 * 37 * 4);

		int arr[64 * 37];


		for (int i = 0; i < (64 * 37); i++)
		{
			arr[0] = 0;
			for (int j = 0; j < 4; j++) {
				Info::distanceInfoFlat[i / 64][i % 37] += (int)buffer[4 * i + j] << 8 * j; // because its little endian
			}



		}



		for (int pos = 0; pos < 64; pos++) {
			for (int dir = 0; dir < 37; dir++) {


																// make this 4 (size of int)
				//rf.read((char*)&Info::distanceInfoFlat[pos][dir], sizeof(int));
			}
		}
		printf("]. ");
		printf(("read: " + std::to_string(number) + " bytes from  " + distanceInfoFile + "\n").c_str());

		rf.close();



	}

	void setCharToPieceArray() {

		Info::charToPiece['k'] = KING;
		Info::charToPiece['r'] = ROOK;
		Info::charToPiece['n'] = KNIGHT;
		Info::charToPiece['b'] = BISHOP;
		Info::charToPiece['q'] = QUEEN;
		Info::charToPiece['p'] = PAWN;

		Info::charToPiece['K'] = BLACK | KING;
		Info::charToPiece['R'] = BLACK | ROOK;
		Info::charToPiece['N'] = BLACK | KNIGHT;
		Info::charToPiece['B'] = BLACK | BISHOP;
		Info::charToPiece['Q'] = BLACK | QUEEN;
		Info::charToPiece['P'] = BLACK | PAWN;

	}


	
	void setUpDistanceInfoFlat() {

		std::cout << "min of 2,3: " << min(2, 3) << std::endl;

		for (int rank = 0; rank < 8; rank++) {
			for (int file = 0; file < 8; file++) {
				Info::distanceInfoFlat[rank*8 + file][0*8 + 1 + DistanceInfoDirectionOffset] = 7 - file;
				assert(Info::distanceInfoFlat[rank * 8 + file][0 * 8 + 1 + DistanceInfoDirectionOffset] == 0 or Info::distanceInfoFlat[rank * 8 + file][0 * 8 + 1 + DistanceInfoDirectionOffset] == 1);
				Info::distanceInfoFlat[rank*8 + file][1*8 + 1 + DistanceInfoDirectionOffset] = min(7 - rank, 7 - file);
				Info::distanceInfoFlat[rank*8 + file][1*8 + 0 + DistanceInfoDirectionOffset] = 7 - rank;
				Info::distanceInfoFlat[rank*8 + file][1*8 + -1 + DistanceInfoDirectionOffset] = min(file, 7 - rank);
				Info::distanceInfoFlat[rank*8 + file][0*8 + -1 + DistanceInfoDirectionOffset] = file;
				Info::distanceInfoFlat[rank*8 + file][-1*8 + -1 + DistanceInfoDirectionOffset] = min(file, rank);
				Info::distanceInfoFlat[rank*8 + file][-1*8 + 0 + DistanceInfoDirectionOffset] = rank;
				Info::distanceInfoFlat[rank*8 + file][-1*8 + 1 + DistanceInfoDirectionOffset] = min(7 - file, rank);

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
