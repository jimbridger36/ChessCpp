#include "Board.h"
#include "Universal.h"


namespace Board {


	void BOARD::genAllMoves(std::list<Move> **lst) {

		int black = this->currentState.blackToPlay;

		for (int pos = 0; pos < 64; pos++) {

			if (pos != 0 and sameColour(black, Square[pos])) {
				genMoves(pos, lst);
			}
		}




		// first gen all moves, updating Attacked as you go

		// then might be able to use this for checking if in check



		// then see if can castle at the end
		// attack only matters for castling and check


	}


	void BOARD::genMoves(int pos, std::list<Move>** lst) {
		
		int piece = this->Square[pos];
		int black = isblack(piece);
		int white = 1 - black;
		int pieceType = bleach(piece);



		assertD(bleach(piece) != 0);

		// dont know how to deal with these yet
		if (bleach(piece) == PAWN) {

			int rank = pos / 8;
			int file = pos % 8;
			int whitepm = 2 * white - 1;
			int targetPos;


			// generating enPassants
			if (this->currentState.enPassantFile == file + 1) {
				(*lst)->push_back(
					Move(piece | ((piece^0b1000) << 4) | (flagEnP << 8), pos, (rank + whitepm) * 8 + (file + 1))
				);
			}
			else if (this->currentState.enPassantFile == file - 1) {
				(*lst)->push_back(
					Move(piece | ((piece ^ 0b1000) << 4) | (flagEnP << 8), pos, (rank + whitepm) * 8 + (file - 1))
				);
			}

			


			// if in non promotion vertical ranges
			if (rank <= 6 - white and rank >= 2 - black) {

				int target = 0;
				// captures
				{
					// if it is even possible for it to move on the LHS
					if (file != 0) {
						// if can capture on the LHS
						targetPos = pos + 8 * whitepm - 1;
						target = Square[targetPos];
						setAttacked(black, targetPos);


						if (target != 0 and (not sameColour(piece, target))) 
							(*lst)->push_back(Move(piece | target << 4, pos, pos + 8 * whitepm - 1));
						
					}
					// if it is even possible for it to move on the RHS
					if (file != 7) {
						targetPos = pos + 8 * whitepm + 1;
						target = Square[targetPos];
						setAttacked(black, target);

						// if can capture on the RHS
						if (target != 0 and (not sameColour(piece, target))) 
							(*lst)->push_back(Move(piece | target << 4, pos, pos + 8 * whitepm + 1));
						
					}
				}

				// normal pushes
				{
					if (Square[pos + 8 * whitepm] == 0)
						(*lst)->push_back( Move(piece, pos, pos + 8 * whitepm));
				}

			}



				// if at second to back rank (i.e. will promote)
			if (rank == (1 + 6 * white)) {
							//			knight, bishop, rook, queen
				int promoPieceTypes[4] = { 2, 3, 4, 6 };
				int target = 0;
				int targetPos = 0;


				for (int promoType : promoPieceTypes) {

					int flagsAndPiece = (flagProm << 8) | ((promoType | (black << 3)) << 12);

					// captures
					{
						// if it is even possible for it to move on the LHS
						if (file != 0) {
							// if can capture on the LHS
							targetPos = pos + 8 * whitepm - 1;
							target = Square[targetPos];
							setAttacked(black, targetPos);

							if (target != 0 and (not sameColour(piece, target))) 
								(*lst)->push_back(Move(piece | target << 4 | flagsAndPiece, pos, pos + 8 * whitepm - 1));
							
						}
						// if it is even possible for it to move on the RHS
						if (file != 7) {
							targetPos = pos + 8 * whitepm + 1;
							target = Square[targetPos];
							setAttacked(black, targetPos);
							// if can capture on the RHS
							if (target != 0 and (not sameColour(piece, targetPos)))
								(*lst)->push_back( Move(piece | target << 4 | flagsAndPiece, pos, pos + 8 * whitepm + 1));
						}
					}

					// normal pushes
					{
						if (Square[pos + 8 * whitepm] == 0)
							(*lst)->push_back( Move(piece | flagsAndPiece, pos, pos + 8 * whitepm));
					}
	




				}







			}




			// if it is on its starting square (and can double pawn push)
			if (rank == (1 + black * 5)) {
				if (Square[pos + whitepm * 8] == 0 and Square[pos + whitepm * 2 * 8] == 0)
					(*lst)->push_back( Move(piece, pos, pos + whitepm * 2 * 8));
				
			}




		}



		if (bleach(piece) == KING) {
			int rank = pos / 8;
			int file = pos % 8;

			int dir, targetPos;
			int *dirs;
			dirs =  (int*) & Info::directionInfoFlat[KING];
			int* dists = (int*)&Info::distanceInfoFlat[pos];

			// for all the directions it can go
			for (int iDir = 0; dirs[iDir] != 0; iDir++) {
				dir = dirs[iDir];

				if (dists[dir] != 0) {
					targetPos = pos + dir;
					setAttacked(black, targetPos);

					// if not same colour (i.e. can move into or capture it)
					if (Square[targetPos] == 0 or (not sameColour(piece, Square[targetPos]))) {
						(*lst)->push_back(
							Move(piece | (Square[targetPos] << 4), pos, targetPos)
						);

					}
				}

				
			}
			



		}

		int maxDist;


		int targetPos, dir, dist;
		Move move;

		for (int iDir = 0; iDir++; Info::directionInfoFlat[pieceType][iDir] != 0) {
			dist = 1;
			dir = Info::directionInfoFlat[pieceType][iDir];
			maxDist = Info::distanceInfoFlat[pieceType][dir + 18];

			targetPos = pos + dir;


			// while going through empty space
			while (dist <= maxDist and Square[targetPos] == 0) {
				move = Move(piece, pos, targetPos);
				(*lst)->push_back(move);

				dist++;
				targetPos += dir;
			}


			// if it didnt stop because it ran out of room and if it can capture
			if (dist <= maxDist && !sameColour(piece, Square[targetPos])){
				
				move = Move(piece | (Square[targetPos] << 4), pos, targetPos);

				(*lst)->push_back(move);
			}




		}







	}









}