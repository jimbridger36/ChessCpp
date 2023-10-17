#pragma once
#include "Debug.h"
#include "Universal.h"

#include <string>
#include <fstream>

namespace Debug {

	void printDirectionInfoFlat() {
		
		for (int piece = 0; piece < 16; piece++) {
			for (int entry = 0; Info::directionInfoFlat[piece][entry] != 0; entry++) {
				std::cout << Info::directionInfoFlat[piece][entry] << " ";
			}
			std::cout << std::endl;


		}


	}

	void saveDistanceInfoFlatToFile(const char* fileName) {


		//const char* fullName = (std::string("C:\Users\Jim\PyCharmProjects\ChessCPPAttemptBStrap\InPycharmProject2\") + std::string(fileName)).c_str();
		const char* fullName = fileName;
		std::cout << fullName << std::endl;

		std::ofstream fw(fullName, std::ofstream::out);


		if (not fw.is_open()) {
			std::cout << std::string(fileName) + " failed to open";
		}
		assert(fw.is_open());
		

		int dist;

		for (int pos = 0; pos < 64; pos++) {
			for (int entry = 0; entry < 37; entry++) {
				dist = Info::distanceInfoFlat[pos][entry];
				fw << dist << " ";
				//assert(dist == 0 or dist == 1);
			}
			fw << std::endl;


		}

		fw.close();
	}


	int* getDirInfoPointer() {
		return (int*) &Info::directionInfoFlat;
	}

	int* getDistInfoFlat() {
		return (int*)&Info::directionInfoFlat;
	}


	void genAllMovesDB(Board::BOARD board) {

		std::list<Move>** lst, *lstPtr;

		lstPtr = new std::list<Move>();
		lst = &lstPtr;
		board.genAllMoves(lst);

		ulong* attack;
		attack = board.getAttackedPtr();
		std::cout << (attack[0]) << std::endl;
		std::cout << attack[1] << std::endl;




	}



}