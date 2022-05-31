#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sys/stat.h>
#include <string>

#define fullSize 50

typedef unsigned long ulong;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

#define nullDepth 0
#define nullPosition 70
#define defaultFile "FILE.dat"

int func(int a, int b){
    return a;
}


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


void printFree(char* str){
    printf(str);
    std::free(str);
}






struct individualEntry {
    char eval;
    uchar depth;
    bool inline isNull(char type){
        bool val = depth == nullDepth;
        if (type == 2){
            return val && eval == 0;
        }
        else if(type == 0){
            return val && eval == SCHAR_MIN;
        }
        else if(type == 1) {
            return val && eval == SCHAR_MAX;
        }
        else{
            return false;
        }
    }
};

struct Entry{
    individualEntry entries[3]; // 6
    compMove bestMove; // 4
    uchar repetitions; // 1

    Entry(){
        individualEntry indEntry;
        // 2
        indEntry.eval = 0;
        indEntry.depth = nullDepth;
        entries[2] = indEntry;
        // 0
        indEntry.eval = SCHAR_MIN;
        entries[0] = indEntry;
        // 1
        indEntry.eval = SCHAR_MAX;
        entries[1] = indEntry;
        repetitions = 0;
    }
    void setEval(int depth, int eval, int boundFlag){
        entries[boundFlag].eval = (char)eval;
        entries[boundFlag].depth = (uchar)depth;
    }

    void setBestMove(Move move){
        bestMove = compMove(move);
    }
    Move inline getBestMove(){
        return bestMove.unpack();
    }

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


void printChar(int num){
    std::string msg = "";
    for (int i = 0; i < num; i++)
        msg += "a";
    printf(msg.c_str());
}



class ht{
public:
	std::unordered_map<ulong, Entry> map;
	int size = 0;

    ht(){
        map = mapType();
    }

	ht(int empty){
		map = mapType();
	}
	ht(char* file, int readReps){
	    int bytes;
		struct stat results;
		stat(file, &results);
		bytes = results.st_size;
		int number = bytes / (sizeof(Entry) + sizeof(ulong));
		map = mapType((number * 13 )/ 10);

	    this->readFromFile(file, readReps);
	}




public:
    void set4(){
        Entry entry = Entry();
        map[1] = entry;
        map[2] = entry;
        map[3] = entry;
        map[4] = entry;
        size += 4;
    }

	void writeToFile(char* file, int writeRepetitions){
		std::ofstream wf(file, std::ios::out | std::ios::binary);

		printf("can only print one");

		if (!wf){
			printf("opening");
			printf(file);
			printf(" didnt work.\n");
		}
		ulong key;
		Entry entry;
		auto endIter = map.end();


		for(auto iter = map.begin(); iter != endIter; iter++){
			key = iter->first;
			entry = iter->second;

			if (!writeRepetitions)
				entry.repetitions = 0;

			wf.write((char*)&key, sizeof(ulong));
			wf.write((char*)&entry, sizeof(Entry));
		}


        wf.close();

		struct stat results;
		int fileSize;
		if ( stat(defaultFile, &results) == 0){
			fileSize = results.st_size;
			printf(("FileSize: " + std::to_string(fileSize)).c_str());
			std::string msg;
			msg += "map successfully saved to: ";
			msg += file;
			msg += "   with size: ";
			if (fileSize > 10000000){// bigger than 10 megabytes
				msg += std::to_string(fileSize / 1000000) + " MB";
			}else if(fileSize > 10000){
				msg += std::to_string(fileSize / 1000) + " KB";
			}
			else{
				msg += std::to_string(fileSize) + " B";
			}
			msg += "\n";
			printf(msg.c_str());
		}
		else{
			printf("an error occured while reading the size of the file that has been written to: ");
			printf(file);
			printf("\n");
		}
	}
	void readIndexesFromFile(char* file) {

    std::ifstream rf(file, std::ios::in | std::ios::binary);
    int bytes = 0;
    struct stat results;
    if (stat(file, &results) == 0) {
        bytes = results.st_size;
    } else {
        printf("failed to read file with name: ");
        printf(file);
        printf("\n");
        return;
    }
    int number = bytes / (sizeof(Entry) + sizeof(ulong));
    ulong key;
    Entry entry;

    printf(" [");


    for (int i = 0; i < number; i++) {
        rf.read((char *) &key, sizeof(ulong));
        rf.read((char *) &entry, sizeof(Entry));
        printf((std::to_string(key) + ", ").c_str());

    }
    printf("]. ");
    printf(("read: " + std::to_string(number) + " keyVal pairs from file: " + defaultFile + "\n").c_str());

    rf.close();
}

	void readFromFile(char* file, bool readRepetitions = false) {

		std::ifstream rf(file, std::ios::in | std::ios::binary);
		int bytes = 0;
		struct stat results;
		if (stat(file, &results) == 0) {
			bytes = results.st_size;
		} else {
			printf("failed to read file with name: ");
			printf(file);
			printf("\n");
			return;
		}
		int number = bytes / (sizeof(Entry) + sizeof(ulong));
		ulong key;
		Entry entry;

		for (int i = 0; i < number; i++) {
			rf.read((char *) &key, sizeof(ulong));
			rf.read((char *) &entry, sizeof(Entry));
			if (!readRepetitions)
				entry.repetitions = 0;
			map[key] = entry;
			size += 1;
		}
		printf(("read: " + std::to_string(number) + " keyVal pairs from file: " + defaultFile + "\n").c_str());

		rf.close();
	}

	// returns true if a bestMove has been found
	bool check(ulong key, bool blackToPlay ,int depth, int& alpha, int& beta, int& eval , Move& bestMove) {
		Entry entry = map[key];
		char wanted = 1;

		// checking the bounds first
		if (entry.entries[wanted].depth > depth) {
			if (blackToPlay) {
				beta = std::min(beta, (int) entry.entries[1].eval);
			} else {
				alpha = std::max(alpha, (int) entry.entries[0].eval);
			}
			if (alpha >= beta) {
				return false; // cutoff
			}// if bestMove is null
		}

		// then check for an 2 match
		if (entry.entries[2].depth > depth) {
			eval = (int) entry.entries[2].eval;
			if (blackToPlay)
				beta = std::min(beta, eval);
			else
				alpha = std::max(alpha, eval);
		}

		if (entry.bestMove.start != nullPosition) {
			bestMove = entry.bestMove.unpack();
			return true;
		}
		return false;
	}

    ulong*  getKeys(){
        ulong* arr = (ulong*) std::malloc(sizeof(ulong) * size);

        int counter = 0;

		for(auto iter = map.begin(); iter != map.end(); iter++){
		    arr[counter] = iter->first;
		    counter++;
		}
        return arr;
    }

    void printKeys(){
        ulong* arr = this->getKeys();


        std::string msg = "[" + std::to_string(arr[0]);
        for (int i = 1; i < size; i++){
            msg += ", " + std::to_string(arr[i]);
        }
        msg += "]\n";
        printf(msg.c_str());
        std::free(arr);
    }

    void setEntry(ulong key, Entry val){
        map[key] = val;
    }
};

void printStuff(char* string){
    printf(string);
}





