
#pragma once
#include <string>
#include "Universal.h"

/*
[ROOK] = 5;
[KNIGHT] = 3;
[QUEEN] = 8;
[BISHOP] = 3;
[PAWN] = 1;
[KING] = 50;
*/


Move::Move() {
    piece = 0;
    start = nullPosition;
    end = nullPosition;
};
    
Move::Move(short _piece, char _start, char _end) {
    piece = _piece;
    start = _start;
    end = _end;
};
/*
 bool Move::isNull() {
    return (piece == 0) && (start == nullPosition) && (end == nullPosition);
};

 
// getters
inline int Move::movingPiece() {
    return piece & 0b1111;
}
inline int Move::flags() {
    return (piece >> 8) & 0b1111;
}
inline bool Move::flagsNotPromotion() {
    if ((piece >> 8) & 0b1011)
        return true;
    else
        return false;
}
inline int Move::promotionPiece() {
    return (piece >> 8) & 0b1111;
}
inline bool Move::enPassant() {
    return (piece >> 8) & 0b0001;
}
inline bool Move::castle() {
    return (piece >> 8) & 0b0010;
}
inline bool Move::promotion() {
    return (piece >> 8) & 0b0100;
}
inline bool Move::draw() {
    return (piece >> 8) & 0b1000;
}

//setters
inline void Move::setCapturedPiece(int _piece) {
    piece |= _piece << 4;
}
inline void Move::setMovingPiece(int _piece) {
    piece |= _piece;
}
inline void Move::setFlags(int _flags) {
    piece |= _flags << 8;
}
inline void Move::setPromotionPiece(int _piece) {
    piece |= _piece << 12;
}
inline void Move::setEnPassant() {
    piece |= 0b0001 << 8;
}
inline void Move::setCastle() {
    piece |= 0b0010 << 8;
}
inline void Move::setPromotion() {
    piece |= 0b0100 << 8;
}
inline void Move::setDraw() {
    piece |= 0b1000 << 8;
}



inline int Move::capturedPiece() {
    return (piece >> 4) & 0b1111;
}
*/

// BST Stuff
/*
Coord operator+(Coord c1, Coord c2) {
    return Coord(c1.rank + c2.rank, c1.file + c2.file);
};
*/

    
Coord::Coord(int pos) {
    rank = pos / 8;
    file = pos % 8;
}
Coord::Coord(char _rank, char _file) {
    rank = _rank;
    file = _file;
}
    



Coord Coord::operator+(const Coord& coord) {
    return Coord(rank + coord.rank, file + coord.file);
}

Coord Coord::operator+(int pos) {
    if (pos > 0)
        return Coord(rank + (pos / 8), file + (pos % 8));
    else
        return Coord(rank - ((-pos) / 8), file - ((-pos) / 8));
}
    

int Coord::toPos() {
        // rank * 8
    return (rank << 3) + file;
}

bool Coord::inBounds() {
    return 0 <= rank && rank < 8 && 0 <= file && file < 8;
}

std::string Coord::str() {
    std::string msg = "(";
    msg += std::to_string(rank) + ", ";
    msg += std::to_string(file) + ")";
    return msg;
}
    
Coord::Coord() {
    rank = nullPosition / 8;
    file = nullPosition % 8;
}

void PiecePos::moveTo(short newPos) {
    pos = newPos;
}

PiecePos::PiecePos() {
    piece = 0;
    pos = nullPosition;
}

PiecePos::PiecePos(short _piece, short _pos) {
    piece = _piece;
    pos = _pos;
}



// 

