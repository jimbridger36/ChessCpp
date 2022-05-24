//
// Created by Hurst on 24/01/2022.
//

#ifndef CHESSCPP_STRUCTS_H
#define CHESSCPP_STRUCTS_H

enum PieceEnum{
	empty = 0,
	pawn = 1,
	knight = 2,
	bishop = 3,
	rook = 4,
	king = 5,
	queen = 6,

	white = 0,
	black = 8,
	wpawn = pawn | white,
};

extern int dirDistPlus18[64][37];
extern int dirsForPiece[16][9];








#endif //CHESSCPP_STRUCTS_H
