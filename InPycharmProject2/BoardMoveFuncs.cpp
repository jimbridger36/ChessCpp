#include "Board.h"
#include "Universal.h"


namespace Board {

	// this 

	void BOARD::doIrreversibleZChanges(irreversibleState OLD, irreversibleState NEW) {

		// castling
		uchar change = OLD.castleRights ^ NEW.castleRights;

		ulong tmp = ZStuff::castlingRightsZ[OLD.castleRights] ^ ZStuff::castlingRightsZ[NEW.castleRights];

		assert(tmp == ZStuff::castlingRightsZ[OLD.castleRights ^ NEW.castleRights]);

		this->ZVal ^= tmp;
		/*
		if (change) {
			for (int bit = 0; bit < 4; bit++) {
				if (getBit(change, bit))
					this->ZVal ^= ZStuff::castlingRightsZ[bit];

			}
		}
		*/

		// enPassant
		this->ZVal ^= ZStuff::enPassantFileZ[OLD.enPassantFile];
		this->ZVal ^= ZStuff::enPassantFileZ[NEW.enPassantFile];
		// the actual file of enpassant file is just the value in memory - 1 (so that 0 is null)


		/*
		if (OLD.enPassantFile != nullPosition) // if old is relevant then remove it (since it is being replaced with new)
			this->ZVal ^= ZStuff::enPassantFileZ[OLD.enPassantFile];
		if (NEW.enPassantFile != nullPosition) // if new is relevant then add it 
			this->ZVal ^= ZStuff::enPassantFileZ[NEW.enPassantFile];
		*/

		// the only difference between this and the one with prevcurrentPly as parameter is this if statement
		if(OLD.blackToPlay != NEW.blackToPlay)
			this->ZVal ^= ZStuff::blackToPlayZ;


	}


	void BOARD::doIrreversibleZChanges() {
		this->doIrreversibleZChanges(this->currentPly);
	}

	void BOARD::doIrreversibleZChanges(int prevcurrentPly) {

		irreversibleState OLD = stateStack[prevcurrentPly], NEW = stateStack[prevcurrentPly + 1];

		// castling
		uchar change = OLD.castleRights ^ NEW.castleRights;

		ulong tmp = ZStuff::castlingRightsZ[OLD.castleRights] ^ ZStuff::castlingRightsZ[NEW.castleRights];

		assert(tmp == ZStuff::castlingRightsZ[OLD.castleRights ^ NEW.castleRights]);

		this->ZVal ^= tmp;
		/*
		if (change) {
			for (int bit = 0; bit < 4; bit++) {
				if (getBit(change, bit))
					this->ZVal ^= ZStuff::castlingRightsZ[bit];

			}
		}
		*/

		// enPassant
		this->ZVal ^= ZStuff::enPassantFileZ[OLD.enPassantFile];
		this->ZVal ^= ZStuff::enPassantFileZ[NEW.enPassantFile];
		// the actual file of enpassant file is just the value in memory - 1 (so that 0 is null)


		/*
		if (OLD.enPassantFile != nullPosition) // if old is relevant then remove it (since it is being replaced with new)
			this->ZVal ^= ZStuff::enPassantFileZ[OLD.enPassantFile];
		if (NEW.enPassantFile != nullPosition) // if new is relevant then add it
			this->ZVal ^= ZStuff::enPassantFileZ[NEW.enPassantFile];
		*/

		this->ZVal ^= ZStuff::blackToPlayZ;

		// fifty move counter is irrelevant


	}


	void BOARD::makeMove(Move move) {

		bool black = getBit(move.piece, 3) > 0;
		bool white = not black;

		this->moveStack[this->currentPly] = move;
		this->currentPly++;

		currentState.fiftyMoveCounter++;


		// if not a standard move (if any flags are set)
		int flags = move.flags();

		// resetting fiftyMoveCounter
		if (move.capturedPiece() or (decolour(move.movingPiece()) == PAWN)) // moving piece == pawn handles promotions too. this doesnt handle changes in rook abilities but fuck that
			currentState.fiftyMoveCounter = 0;


		// promoting will be dealt with later
		// could add in double pawn push as a flag
		if (flags & (flagCastling | flagEnP)) {

			// if enPassant
			if (move.enPassant()) {
				// captured   file				rank
				removePiece( (move.end % 8) + (3 + white)*8 );

				// transferring the moving piece
				transferPiece(move.start, move.end);
			}
			else if (move.castle()) {
				clearCastleRights(black);

				// if kingside
				if ((move.end % 8) == 7 or (move.end % 8) == 6) {
					// move king
					transferPiece(move.start, move.start + 2);
					kingPosition[black] = move.start + 2;

					// move rook
					transferPiece(move.start + 3, move.start + 1);
				}
				// if queenside
				else {
					// move king
					transferPiece(move.start, move.start - 2);
					kingPosition[black] = move.start - 2;

					// move rook
					transferPiece(move.start - 4, move.start - 1);
				}
			}
			// could add in double pawn push in here
		}

		// if normal move or promotion
		else {
			if (decolour(move.movingPiece()) == KING)
				clearCastleRights(black); // if black then black king moving

			// if there is a capture
			if (move.capturedPiece()) {


				// white rook starting are 0, 7
				// black rook starting are 54, 63
				

				// if move starts or ends on rook sqaure

				for (int colour = 0; colour < 1; colour++) {
					// queenside
					if (move.start == colour * 8 + 0 or move.end == colour * 8 + 0) 
						clearCastleRights(colour, 1);
					
					// kingside
					if (move.start == colour * 8 + 7 or move.end == colour * 8 + 7)
						clearCastleRights(colour, 0); // kingside (not queenside)
				}



				removePiece(move.end);
				transferPiece(move.start, move.end);


			}// if no capture
			else {

				transferPiece(move.start, move.end);

				
				//				if a double pawn push															
				int newEnPFile = (decolour(move.movingPiece()) == PAWN and abs(move.end - move.start) == 16) ? (move.start % 8) + 1 : 0;

				this->currentState.enPassantFile = newEnPFile;
			}

			if (move.promotionPiece()) {
				// the pawn has already moved (and possible captured its piece) so just need to replace pawn with promotion peice
				removePiece(move.end);
				addPiece(move.end, move.promotionPiece());

			}


		}
		
		currentState.blackToPlay != currentState.blackToPlay;

		pushStateToStack();
		doIrreversibleZChanges();

		currentPly++;
	}

	void BOARD::unmakeMove() {
		// could do this by storing the complete state of the game after every move (including the change in ZVal) and putting this into a mega completeStateStack, but siply undoing the move might weed out some errors

		int oldPly = currentPly - 1;
		int oldBlack = 1 - currentState.blackToPlay;
		int oldWhite = currentState.blackToPlay;

		Move move = moveStack[oldPly]; // moveStack hold the move executed on that ply (e.g the starting move in in ply 0)
		gameOver = 0;


		doIrreversibleZChanges(stateStack[currentPly], stateStack[oldPly]);


		// if a move is enPassant or Castling

		if (move.flags() & (flagEnP | flagCastling)) {

			// if enPassant
			if (move.flags() == flagEnP) {

				// adding the taken piece
				addPiece((move.end % 8) + (3 + oldWhite) * 8, PAWN | (oldWhite << 3));

				// transferring the moving pawn
				transferPiece(move.end, move.start);
			}

			// else if rooking
			else if(move.flags() == flagCastling) {

				// if kingside
				if (move.end % 8 == 7) {
					// move king (back)
					transferPiece(move.start + 2, move.start);
					kingPosition[oldBlack] = move.start;

					// move rook
					transferPiece(move.start + 1, move.start + 3);
					
				}
				// if queenside
				else {
					// move king (back)
					transferPiece(move.start + 2, move.start);
					kingPosition[oldBlack] = move.start;

					// move rook
					transferPiece(move.start - 1, move.start - 4);
				}
			}
			// promotion handled later
		}

		// else if a normal move (or promotion)
		else {
			// if there is a capture
			if (move.capturedPiece()) {
				transferPiece(move.end, move.start);
				addPiece(move.end, move.capturedPiece());
			}
			//if no capture
			else {
				transferPiece(move.end, move.start);
			}

			// if promotion
			if (move.flags() == flagProm) {

				// doing this weirdly because otherwise it would put the queen (or other) backl
				removePiece(move.end);

				// putting the pawn back
				addPiece(move.start, move.movingPiece());


			}



		}
		currentState.blackToPlay != currentState.blackToPlay;








	}



}


