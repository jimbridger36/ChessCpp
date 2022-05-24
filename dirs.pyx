#distutils: language = c++
#distutils: extra_compile_args = ["-std=c++20"]
import numpy as np
cimport numpy as np
from libc.stdlib cimport malloc, free
from cython cimport sizeof as size
from libcpp.unordered_map cimport unordered_map
cimport cython

IF True:
	ctypedef public enum PieceEnum:
		empty = 0
		pawn = 1
		knight = 2
		bishop = 3
		rook = 4
		king = 5
		queen = 6

		white = 0
		black = 8
		wpawn = pawn | white




cdef extern from "chessCPP/SetUpData.h":
	int dirDistPlus18[64][37]
	int dirsForPiece[16][9]




VecToIntMat= np.array([[-18, -17, -16, -15, -14],
				       [-10,  -9,  -8,  -7,  -6],
				       [ -2,  -1,   0,   1,   2],
				       [  6,   7,   8,   9,  10],
				       [ 14,  15,  16,  17,  18]], dtype=np.int32)


# to access the distance you can go in the direction, +8, to directions[rank,file,+8+18], ALWAYS ADD 18
# doing direction stuff

if True:
	directionsVec = {PieceEnum.rook : np.array( [[1,0], [-1,0], [0,1], [0,-1]] ),
	              PieceEnum.bishop : np.array( [[1,1], [1,-1], [-1,1], [-1,-1]] ),
	              PieceEnum.queen : np.concatenate(([[1,0], [-1,0], [0,1], [0,-1]],[[1,1], [1,-1], [-1,1], [-1,-1]])),
	              PieceEnum.knight : np.array( [[2,1], [2,-1], [-2,1], [-2,-1], [1,2], [1,-2], [-1,2], [-1,-2]] )
	              }

	import copy
	directions = {PieceEnum.rook : [],
	              PieceEnum.bishop : [],
	              PieceEnum.queen : [],
	              PieceEnum.knight : []
	}









def ComputePieceDirs():
	for piece in [PieceEnum.rook, PieceEnum.bishop, PieceEnum.queen, PieceEnum.knight]:
		oldArr = directionsVec[piece]
		newArr = np.zeros((oldArr.shape[0]), dtype=np.int_32)
		for index, vec in enumerate(oldArr):
			newArr[index] = 8*vec[0] + vec[1] # converting from vec to int
		directions[piece] = newArr
		for index, dir in enumerate(newArr):
			dirsForPiece[piece][index] = dir




def f(rank, file):
	return 8 * rank + file



cdef public np.ndarray distanceInfoArrVec = np.zeros((8,8,5,5),dtype=np.int32)

cdef public np.ndarray distanceSquare = np.zeros((8,8,37),dtype=np.int32)
cdef public np.ndarray distanceInfoFlat = np.zeros((64,37))


def computeDistanceInfo():
		for rank in range(8):
			for file in range(8):
				distanceInfoArrVec[rank,file][0+2,1+2] = 7-file
				distanceInfoArrVec[rank,file][1+2,1+2] = min(7 - rank,7 - file)
				distanceInfoArrVec[rank,file][1+2,0+2] = 7-rank
				distanceInfoArrVec[rank,file][1+2,-1+2] = min(file, 7 - rank)
				distanceInfoArrVec[rank,file][0+2,-1+2] = file
				distanceInfoArrVec[rank,file][-1+2,-1+2] = min(file, rank)
				distanceInfoArrVec[rank,file][-1+2,0+2] = rank
				distanceInfoArrVec[rank,file][-1+1,1+2] = min(7 - file, rank)
				# moving in same spot
				distanceInfoArrVec[rank,file][0+2,0+2] = 0

				# bloody horse movement

				distanceInfoArrVec[rank,file][1+2,2+2] = 1 if file <= 5 and rank <= 6 else 0
				distanceInfoArrVec[rank,file][2+2,1+2] = 1 if file <= 6 and rank <= 5 else 0
				distanceInfoArrVec[rank,file][2+2,-1+2] = 1 if file >= 1 and rank <= 5 else 0
				distanceInfoArrVec[rank,file][1+2,-2+2] = 1 if file >= 2 and rank <= 6 else 0
				distanceInfoArrVec[rank,file][-1+2,-2+2] = 1 if file >= 2 and rank >= 1 else 0
				distanceInfoArrVec[rank,file][-2+2,-1+2] = 1 if file >= 1 and rank >= 2 else 0
				distanceInfoArrVec[rank,file][-2+2,1+2] = 1 if file <= 6 and rank >= 2 else 0
				distanceInfoArrVec[rank,file][-1+2,2+2] = 1 if file <= 5 and rank >= 1 else 0

		# computing the direction info
		global directions
		for piece in list ( directionsVec.keys() ):
			oldArr = directionsVec[piece]
			newArr = np.zeros((oldArr.shape[0]),dtype=np.int32)
			for ind, vec in enumerate(oldArr):
				newArr[ind] = 8 * vec[0] + vec[1]
			directions[piece] = newArr


		for rank in range(8):
			for file in range(8):
				for dRank in range(-2,3):
					for dFile in range(-2,3):
						distanceSquare[rank,file][dRank*8 + dFile + 18] = distanceInfoArrVec[rank,file][dRank+2,dFile+2]

		for rank in range(8):
			for file in range(8):
				for move in range(-18,18+1):
					distanceInfoFlat[rank*8 + file][move+18] = distanceSquare[rank,file][move+18]
					dirDistPlus18[rank*8 + file][move+18] = distanceSquare[rank, file][move+18]





val = 3

print(val)




