#pragma once
#include <string>
#include <iostream>
#include <assert.h>
#include <list>
#define maxMoves 6000
#define nullPosition 64 // this is because 64 (for chars only available in uchar) as a signed char has the same bits as -64
#define defaultFenString "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
using std::cout;

//#define FROMCYTHON
#define NDEBUG
#define DEBUG 
#define bleach decolour
#define decolour(x) (x & 0b0111)
#define whiteify(x) (x & 0b0111)
#define blackify(x) (x | 0b1000)
#define isblack(x) (x >> 3)
#define iswhite(x) (!isblack(x))
#define isOfType(x, type) ( not( x ^ type) )
#define getBit(x,b) ( (x >> b) & 1)
#define setBit(x,b) ( x |= (((ulong)1) << b) )
#define colour(x) (getBit(x, 3))
#define flipBit(x, b) (x ^ (((ulong)1) << b))
#define setBitIP(x, b) (x = x | (((ulong)1) << b ))

#define setAttacked(col, pos) (this->Attacked[col] |=  ((ulong)1) << pos)


#define sameColour(a, b) (getBit(a, 3) == getBit(b, 3))


#define assertD assert


#ifdef FROMCYTHON
#define fileLibPath InPycharmProject2/
#else
#define fileLibPath 
#endif


#ifdef FROMCYTHON
    #define defaultFile  "InPycharmProject2/FILE.dat"
#else
    // vs version
    #define defaultFile  "FILE.dat"
#endif


typedef unsigned __int64 ulong;
typedef unsigned __int8 uchar;
typedef unsigned __int16 ushort;
typedef unsigned __int32 uint;

#define EMPTY 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define KING 5
#define QUEEN 6
#define WHITE 0
#define BLACK 8
#define White 0
#define Black 1

#define not !
#define or ||
#define and &&

#define DistanceInfoDirectionOffset 18
#define DistDirOffset DistanceInfoDirectionOffset
#define flagEnP 0b0001
#define flagProm 0b0100
#define flagCastling 0b0010






/*
[ROOK] = 5;
[KNIGHT] = 3;
[QUEEN] = 8;
[BISHOP] = 3;
[PAWN] = 1;
[KING] = 50;
*/

//const int distanceInfoAdd18[64][37] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 7, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 0, 1, 7, 6, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 1, 2, 7, 5, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 1, 3, 7, 4, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 1, 4, 7, 3, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 0, 1, 5, 7, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 0, 1, 6, 7, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 7, 7, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 6, 6, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 0, 1, 6, 6, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 1, 2, 6, 5, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 1, 3, 6, 4, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 1, 4, 6, 3, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 0, 1, 5, 6, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 0, 1, 6, 6, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 6, 6, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 5, 5, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 0, 1, 5, 5, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 1, 2, 5, 5, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 1, 3, 5, 4, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 1, 4, 5, 3, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 0, 1, 5, 5, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 0, 1, 5, 5, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 5, 5, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 3, 3, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 4, 4, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 3, 3, 1, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 1, 2, 4, 4, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 3, 3, 3, 1, 0, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 1, 3, 4, 4, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 3, 3, 3, 1, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 1, 4, 4, 3, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 3, 3, 2, 1, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 0, 1, 4, 4, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0, 1, 3, 3, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 4, 4, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 4, 4, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 3, 3, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 4, 4, 1, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 1, 2, 3, 3, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 3, 4, 4, 1, 0, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 1, 3, 3, 3, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 4, 4, 3, 1, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 1, 3, 3, 3, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 4, 4, 2, 1, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 0, 1, 3, 3, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0, 1, 4, 4, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 3, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5, 5, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 5, 5, 1, 0, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 5, 5, 1, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 3, 5, 4, 1, 0, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 4, 5, 3, 1, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 5, 5, 2, 1, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 5, 5, 1, 0, 0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0, 1, 5, 5, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 6, 6, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 6, 6, 1, 0, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 6, 5, 1, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 3, 6, 4, 1, 0, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 4, 6, 3, 1, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 5, 6, 2, 1, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 6, 6, 1, 0, 0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0, 1, 6, 6, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 7, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 7, 6, 1, 0, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 7, 5, 1, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 3, 7, 4, 1, 0, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 4, 7, 3, 1, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 5, 7, 2, 1, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 0, 1, 6, 7, 1, 0, 0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0, 1, 7, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };




class Move {
public:
    short piece;
    char start;
    char end;


    Move();
    Move(short _piece, char _start, char _end);
    /*
    // getters
    inline bool isNull();
    inline int capturedPiece();
    inline int movingPiece();
    inline int flags();
    inline bool flagsNotPromotion();
    inline int promotionPiece();
    inline bool enPassant();
    inline bool castle();
    inline bool promotion();
    inline bool draw();

    //setters
    inline void setCapturedPiece(int _piece);
    inline void setMovingPiece(int _piece);
    inline void setFlags(int _flags);
    inline void setPromotionPiece(int _piece);
    inline void setEnPassant();
    inline void setCastle();
    inline void setPromotion();
    inline void setDraw();
    */

    inline bool isNull() {
        return (piece == 0) && (start == nullPosition) && (end == nullPosition);
    }
     
    // getters
    inline int movingPiece() {
        return piece & 0b1111;
    }
    inline int flags() {
        return (piece >> 8) & 0b1111;
    }
    inline bool flagsNotPromotion() {
        if ((piece >> 8) & 0b1011)
            return true;
        else
            return false;
    }
    inline int promotionPiece() {
        return (piece >> 8) & 0b1111;
    }
    inline bool enPassant() {
        return (piece >> 8) & 0b0001;
    }
    inline bool castle() {
        return (piece >> 8) & 0b0010;
    }
    inline bool promotion() {
        return (piece >> 8) & 0b0100;
    }
    inline bool draw() {
        return (piece >> 8) & 0b1000;
    }
      
      // setters
    inline void setCapturedPiece(int _piece) {
        piece |= _piece << 4;
    }
    inline void setMovingPiece(int _piece) {
        piece |= _piece;
    }
    inline void setFlags(int _flags) {
        piece |= _flags << 8;
    }
    inline void setPromotionPiece(int _piece) {
        piece |= _piece << 12;
    }
    inline void setEnPassant() {
        piece |= 0b0001 << 8;
    }
    inline void setCastle() {
        piece |= 0b0010 << 8;
    }
    inline void setPromotion() {
        piece |= 0b0100 << 8;
    }
    inline void setDraw() {
        piece |= 0b1000 << 8;
    }
     
     
     
    inline int capturedPiece() {
        return (piece >> 4) & 0b1111;
    }





};



struct Coord {
public:
    char rank;
    char file;
public:
    Coord();
    Coord(int pos);
    Coord(char _rank, char _file);
    
    Coord operator+(const Coord& coord);

    Coord operator+(int pos);


    int toPos();

    bool inBounds();

    std::string str();
    
};

struct PiecePos {
    short piece;
    short pos;

    PiecePos(short _piece, short _pos);
    PiecePos();

    inline void moveTo(short newPos);


};


std::string PosToStr(int pos);

int StrToPos(std::string str);

// BST Stuff

// 

