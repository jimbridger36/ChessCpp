#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include "Universal.h"
#pragma once


#define fileCharLength 100

#define nullDepth 0


/*
struct Move{
    short piece;
    char start;
    char end;
    Move(){
        piece = 0;
        start = nullPosition;
        end = nullPosition;
    }

    Move(short _piece, char _start, char _end){
        piece = _piece;
        start = _start;
        end = _end;
    }


};
*/

/*
struct compMove{
    ushort piece;
    uchar start;
    uchar end;
    compMove(){
        piece = 0;
        start = nullPosition;
        end = nullPosition;
    }

    compMove(int piece_, int start_, int end_){
        piece = piece_;
        start = start_;
        end = end_;
    }

    compMove(Move move){
        piece = move.piece;
        start = move.start;
        end = move.end;
    }

    Move unpack(){
        Move move;
        move.piece = (int)piece;
        move.end = (int)end;
        move.start = (int)start;
        return move;
    }


};
*/

void printFree(char* str);

namespace Whtable {




    struct individualEntry {
        char eval;
        uchar depth;
        bool inline isNull(char type);
    };

    struct Entry {
        individualEntry entries[3]; // 6
    public:
        Move bestMove; // 4
        Entry();
        uchar repetitions; // 1


        void setEval(int depth, int eval, int boundFlag);
    };

    typedef std::unordered_map<ulong, Entry> mapType;

    /*
    //const char* str = "hello";
    mapType doShit(mapType&, char const* = "hello");
    void read(mapType& outmap);
    void write(mapType& map);


    bool inline isNull(Entry& entry){
        return entry.entries[0].isNull(0) && entry.entries[1].isNull(1) && entry.entries[2].isNull(2) && isNull(entry.bestMove);
    }
    bool inline isNull(int& val){
        return val == 0;
    }

    */


    /*
    const char* fullToC(char[fullSize] fileFull){
        int i;
        for (i = fullSize - 1; fileFull[i] == 0; i--){
        }

        char* file = (char*)std::malloc(i + 1);
        for (; i > 0; i--)
            file[i] = fileFull[i];
        return (const char*)file;
    }
    */


    void printChar(int num);



    class HT {
    public:
        mapType map;
        int size;

        HT();

        HT(int empty);
        HT(char file[fileCharLength], int readReps = 0);




    public:
        void set4();

        void writeToFile(char* file, int writeRepetitions);
        void readIndexesFromFile(char* file);

        void readFromFile(char* file, bool readRepetitions = false);

        // returns true if a bestMove has been found
        bool check(ulong key, bool blackToPlay, int depth, int& alpha, int& beta, int& eval, Move& bestMove);

        ulong* getKeys();

        void printKeys();

        void setEntry(ulong key, Entry val);
    };

    void printStuff(char* string);




}