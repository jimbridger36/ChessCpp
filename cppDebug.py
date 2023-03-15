#distutils: language = c++
#distutils: extra_compile_args = ["-std=c++20"]
import numpy as np
fileToSaveDirectionInfoTo = "InPycharmProject2/distanceInfoFile.dat"

MAXGAMELENGTH = 5000

#checkmate value = 256
def flipy(arr):
	if True:
		maxrow = arr.shape[0] - 1
		newArr = np.zeros(arr.shape, dtype=np.int32)

		for row in range(arr.shape[0] // 2):
			newArr[row] = arr[maxrow-row]
			newArr[maxrow-row] = arr[row]

		if arr.shape[0] % 2 == 1:
			newArr[arr.shape[0] // 2] = arr[arr.shape[0] // 2]
		return newArr

def zeroes(shape):
	return np.zeros(shape,dtype=np.int32)



class PieceEnum:
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





VecToIntMat= np.array([[-18, -17, -16, -15, -14],
				       [-10,  -9,  -8,  -7,  -6],
				       [ -2,  -1,   0,   1,   2],
				       [  6,   7,   8,   9,  10],
				       [ 14,  15,  16,  17,  18]], dtype=np.int32)


# to access the distance you can go in the direction, +8, to directions[rank,file,+8+18], ALWAYS ADD 18
# doing direction stuff
if True:
	directionsVec = {PieceEnum.rook : np.array( [[1,0], [-1,0], [0,1], [0,-1]], dtype=np.int32 ),
	              PieceEnum.bishop : np.array( [[1,1], [1,-1], [-1,1], [-1,-1]], dtype=np.int32 ),
	              PieceEnum.queen : np.array([[1,0], [-1,0], [0,1], [0,-1],[1,1], [1,-1], [-1,1], [-1,-1]], dtype=np.int32),
	              PieceEnum.knight : np.array( [[2,1], [2,-1], [-2,1], [-2,-1], [1,2], [1,-2], [-1,2], [-1,-2]], dtype=np.int32 ),
	              }
	import copy
	directions = {PieceEnum.rook : [],
	              PieceEnum.bishop : [],
	              PieceEnum.queen : [],
	              PieceEnum.knight : [],
	}

	for piece in [PieceEnum.rook, PieceEnum.bishop, PieceEnum.queen, PieceEnum.knight]:
		oldArr = directionsVec[piece]
		newArr = zeroes((oldArr.shape[0]))
		for index, vec in enumerate(oldArr):
			newArr[index] = 8*vec[0] + vec[1] # converting from vec to int
		directions[piece] = newArr
	'''
	assert(-7 in directions[PieceEnum.queen])
	assert(-7 in directions[PieceEnum.bishop])'''




intToPieceString = {
	0 : 'empty       ',
	1 : 'whitePawn   ',
	2 : 'whiteKnight ',
	3 : 'whiteBishop ',
	4 : 'whiteRook   ',
	5 : 'whiteKing   ',
	6 : 'whiteQueen  ',

	8 : 'empty       ',
	9 : 'blackPawn   ',
	10 : 'blackKnight',
	11 : 'blackBishop',
	12 : 'blackRook  ',
	13 : 'blackKing  ',
	14 : 'blackQueen '
}
# a grid of arrays of length 8, this array represents the distance to the edge in that direction
# the grid is accessed by its position number
#
distanceInfoArrVec = np.zeros((8,8,5,5),dtype=np.int32)
# distance info will be like this, a 8x8 grid of a 5x5 item, this item has the distance possible in the normal directions,
# to access the cell that represents going 1 up, 0 across go item[1+2,0+2] or a up, b across item[a+2,b+2]
# for horse possibilities (2,1) for example, go item[2+2,1+2]

distanceSquare = np.zeros((8,8,37), dtype=np.int32)
distanceInfoFlat = np.zeros((64,37), dtype=np.int32)

dirsPlus18 = {}
dirToDistance = {}

# get stuff for python

# computeDistanceInfo
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
            distanceInfoArrVec[rank,file][-1+2,1+2] = min(7 - file, rank)
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
        dirsPlus18[piece] = newArr + 18


    for rank in range(8):
        for file in range(8):
            for dRank in range(-2,3):
                for dFile in range(-2,3):
                    distanceSquare[rank,file][dRank*8 + dFile + 18] = distanceInfoArrVec[rank,file][dRank+2,dFile+2]

    for rank in range(8):
        for file in range(8):
            for move in range(-18,18+1):
                distanceInfoFlat[rank*8 + file][move+18] = distanceSquare[rank,file][move+18]

def saveArrToFileInt2D(arr, file):
    with open(file, 'wb') as f:
        for x in range(arr.shape[0]):
            for y in range(arr.shape[1]):
                f.write(bytes([arr[x][y]]))

def saveDistanceInfoToFile(fileName = "InPycharmProject2/DebugOutputPy.txt"):
    saveArrToFileInt2D(distanceInfoFlat, fileToSaveDirectionInfoTo)
    with open(fileName, 'w') as file:
        for pos in range(64):
            for dir in range(37):
                file.write(str(int(distanceInfoFlat[pos,dir])) + " ")
            file.write("\n")








def compareTheFiles(file1 = "InPycharmProject2/DebugOutputPy.txt", file2 = "InPycharmProject2/DebugOutput.txt"):
    with open(file1, 'r') as f1:
        with open(file2, 'r') as f2:
            l1 = f1.readline()
            l2 = f2.readline()
            if l1 != l2:
                print("files are different")
                return False

    return True






computeDistanceInfo()

def getLine(arr):
    string = '{ '
    for i in range(len(arr)):
        string += str(arr[i])
        if i != len(arr) - 1:
            string +=', '

    string += ' }'
    return string








print(saveDistanceInfoToFile())


string = ''
arr1 = []
for i in range(64):
    string = ''
    arr2 = []
    for j in range(37):
        arr2.append(distanceInfoFlat[i][j])

    arr1.append(getLine(arr2))
a = getLine(arr1)
