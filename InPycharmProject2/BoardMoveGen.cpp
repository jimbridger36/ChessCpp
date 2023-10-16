#include "Board.h"
#include "Universal.h"
#include "Debug.h"


namespace Board {


	void BOARD::genBothSidesMoves(std::list<Move> *lst) {


		for (int pos = 0; pos < 64; pos++) {

			if (Square[pos] != 0 ) {
				genPosMoves(pos, lst);
			}
		}




		// first gen all moves, updating Attacked as you go

		// then might be able to use this for checking if in check



		// then see if can castle at the end
		// attack only matters for castling and check
	}


	void BOARD::genMoves(int col, std::list<Move> *lst) {


		for (int pos = 0; pos < 64; pos++) {

			if ( Square[pos] != 0 and (colour(Square[pos]) == col) ) {
				genPosMoves(pos, lst);
			}
		}

	}




	void BOARD::genPosMoves(int pos, std::list<Move> *lst) {
		

		Debug::checkDistance(false);


		std::cout << "SHOULD CHANGE ATTACKED for moves originating from " << PosToStr(pos) << ": " << Attacked[0] << "->";
		//Attacked[0] = ((ulong)1) << (57-32);
		//std::cout << Attacked[0] << " ";

		//std::cout << PosToStr(pos) << std::endl;
		int piece = this->Square[pos];
		int black = isblack(piece);
		int white = black ^ 0b1;
		int pieceType = bleach(piece);



		assertD(bleach(piece) != 0);

		// might be incomplete
		if (bleach(piece) == PAWN) {

			int rank = pos / 8;
			int file = pos % 8;
			int whitepm = 2 * white - 1;
			int targetPos;


			// generating enPassants
			if (this->currentState.enPassantFile == file + 1) {
				lst->push_back(
					Move(piece | ((piece^0b1000) << 4) | (flagEnP << 8), pos, (rank + whitepm) * 8 + (file + 1))
				);
			}
			else if (this->currentState.enPassantFile == file - 1) {
				lst->push_back(
					Move(piece | ((piece ^ 0b1000) << 4) | (flagEnP << 8), pos, (rank + whitepm) * 8 + (file - 1))
				);
			}

			


			// if in non promotion vertical ranges
			if (rank <= 6 - white and rank >= 1 + black) {

				int target = 0;
				// captures
				{
					// if it is even possible for it to move on the LHS
					if (file != 0) {
						// if can capture on the LHS
						targetPos = pos + 8 * whitepm - 1;
						target = Square[targetPos];
						setAttacked(black, targetPos);


						if (target != 0 and (not sameColour(piece, target))) {
							lst->push_back(Move(piece | target << 4, pos, pos + 8 * whitepm - 1));
						}
						
					}
					// if it is even possible for it to move on the RHS
					if (file != 7) {
						targetPos = pos + 8 * whitepm + 1;
						target = Square[targetPos];
						setAttacked(black, target);

						// if can capture on the RHS
						if (target != 0 and (not sameColour(piece, target))) 
							lst->push_back(Move(piece | target << 4, pos, pos + 8 * whitepm + 1));
						
					}
				}

				// normal pushes
				{
					if (Square[pos + 8 * whitepm] == 0)
						lst->push_back( Move(piece, pos, pos + 8 * whitepm));
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
								lst->push_back(Move(piece | target << 4 | flagsAndPiece, pos, pos + 8 * whitepm - 1));
							
						}
						// if it is even possible for it to move on the RHS
						if (file != 7) {
							targetPos = pos + 8 * whitepm + 1;
							target = Square[targetPos];
							setAttacked(black, targetPos);
							// if can capture on the RHS
							if (target != 0 and (not sameColour(piece, targetPos)))
								lst->push_back( Move(piece | target << 4 | flagsAndPiece, pos, pos + 8 * whitepm + 1));
						}
					}

					// normal pushes
					{
						if (Square[pos + 8 * whitepm] == 0)
							lst->push_back( Move(piece | flagsAndPiece, pos, pos + 8 * whitepm));
					}
	




				}







			}




			// if it is on its starting square (and can double pawn push)
			if (rank == (1 + black * 5)) {
				if (Square[pos + whitepm * 8] == 0 and Square[pos + whitepm * 2 * 8] == 0) {
					lst->push_back(Move(piece, pos, pos + whitepm * 2 * 8));
				}
				
			}




		}


		// TODO: Add castling stuff here
		else if (bleach(piece) == KING) {

			// TODO: add castling stuff here

			int rank = pos / 8;
			int file = pos % 8;

			int dir, targetPos;
			int *dirs;
			dirs =  (int*) & Info::directionInfoFlat[KING];
			//int* dists = (int*)&distanceInfoAdd18[pos];

			// for all the directions it can go
			for (int iDir = 0; dirs[iDir] != 0; iDir++) {
				dir = dirs[iDir];

				if ( Info::distanceInfoAdd18[pos][dir+18] != 0) {
					targetPos = pos + dir;
					//setAttacked(black, targetPos);

					// if not same colour (i.e. can move into or capture it)
					if (Square[targetPos] == 0 or (not sameColour(piece, Square[targetPos]))) {
						setAttacked(black, targetPos);
						lst->push_back(
							Move(piece | (Square[targetPos] << 4), pos, targetPos)
						);

					}
				}

				
			}
			



		}
		// if normal
		else {

			int maxDist;


			int targetPos, dir, dist;
			Move move;
			//std::cout << "else reached: " << Info::directionInfoFlat[pieceType][0] << " " << std::endl;

			for (int iDir = 0; Info::directionInfoFlat[pieceType][iDir] != 0; iDir++) {
				dist = 1;
				dir = Info::directionInfoFlat[pieceType][iDir];
				maxDist = Info::distanceInfoAdd18[pos][dir + 18];

				targetPos = pos + dir;


				// while going through empty space
				std::cout << "looking at piece: " << piece <<" with dir: " << dir << " from: " << PosToStr(pos) << " to: " << PosToStr(targetPos) << ", (maxDist = " << maxDist << ")";
				while (dist <= maxDist and Square[targetPos] == 0) {
					
					std::cout << PosToStr(targetPos) << ", ";

					move = Move(piece, pos, targetPos);
					lst->push_back(move);
					setAttacked(black, targetPos);


					dist++;
					targetPos += dir;
				}

				std::cout << " finished now" << std::endl;



				// if it didnt stop because it ran out of room and if it can capture
				if ((dist <= maxDist) && (!sameColour(piece, Square[targetPos])) ) {

					move = Move(piece | (Square[targetPos] << 4), pos, targetPos);

					lst->push_back(move);
					setAttacked(black, targetPos);
				}




			}



		}

		std::cout << "attacked ended up at " << Attacked[0] << std::endl;

	}



	void BOARD::setAttack(int colour, ulong value) {
		this->Attacked[colour] = value;
	}
	
	void BOARD::printAttack0() {
		std::cout << this->Attacked[0] << std::endl;
	}




}