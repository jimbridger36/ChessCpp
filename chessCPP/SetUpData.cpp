//
// Created by Hurst on 24/01/2022.
//

#include "SetUpData.h"

int* getDirsPlus18Ptr(){
	return (int*)&dirDistPlus18;
}

int getTest(int i1, int i2){
	return dirDistPlus18[i1][i2];
}

int testArr[2][3];

int val;

int getVal(){
	return val;
}

int getTestArr(int i, int j){
	return testArr[i][j];
}


void ComputeDistances(){

	int drank, dfile;
	for(int rank = 0; rank < 8; rank++){
		for(int file = 0; file < 8; file++){

			for(int dir = -18; dir <= 18; dir++){
				drank = dir / 8;
				if (dir < 0)
					drank;




			}






		}





	}





}





