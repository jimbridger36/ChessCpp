##distutils: language = c++
##distutils: extra_compile_args = ["-std=c++20"]
##distutils: sources = InPycharmProject2/Universal.cpp
##distutils: sources = InPycharmProject2/UniversalH.cpp
##distutils: sources = InPycharmProject2/ZStuff.cpp
##distutils: sources = InPycharmProject2/ZStuffH.cpp
# above was fully commented out
##distutils: sources = InPycharmProject2/Info.cpp
##distutils: sources = InPycharmProject2/InfoH.cpp
##distutils: sources = InPycharmProject2/Board.cpp
##distutils: sources = InPycharmProject2/Whtable.cpp
##distutils: sources = InPycharmProject2/WhtableH.cpp
##distutils: sources = InPycharmProject2/StartUpFunctions.cpp
##distutils: sources = InPycharmProject2/StartUpFunctions.h

from libcpp cimport bool
from libc.string cimport memcpy
import copy
import numpy as np
cimport numpy as np


DEF cppSourceFolder = "InPycharmProject2/"

DEF randomSeed = "hello"

startingFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


DEF fileCharLength = 100



# PieceEnum, StringToPos, reprMove
IF True:
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
	def StringToPos(pos):
		if len(pos) != 2:
			raise ValueError

		file = ord(pos[0]) - 97
		if not (file < 8 and file >= 0):
			raise ValueError

		rank = int(pos[1]) - 1
		if not (rank < 8 and rank >= 0):
			raise ValueError
		return rank * 8 + file

	cdef str reprMove(Move move):
		black = (move.piece >> 3) & 1
		white = 1 - black
		string = 'Move: '
		string += 'Black ' if black else 'White '

		if (move.piece >> 8) & 1:
			string += 'EnPassant '
		elif (move.piece >> 9) & 1:
			string += 'Castle '
		elif (move.piece >> 10) & 1:
			string += 'Promotion '
		elif (move.piece >> 11) & 1:
			string += 'Draw flag set '
		movingPiece = charPieceEnum[move.piece & 0b0111]
		if black:
			movingPiece = movingPiece.upper()

	#= Move()

ctypedef unsigned long long ulong


# extern blocks
IF True:
	cdef extern from "InPycharmProject2/Universal.h":
		cdef cppclass Move:
			char start
			short piece
			char end
			Move()

	cdef extern from "InPycharmProject2/StartupFunctions.h" namespace "StartUpFunctions":
		void InitAll(int ZSeed)

	cdef extern from "InPycharmProject2/Info.h" namespace "Info":
		int enumToPieceVal[16]
		int directionInfoFlat



	cdef extern from "InPycharmProject2/Board.h" namespace "Board":
		cdef cppclass irreversibleState:
			char castleRights
			char enPassantFile
			char fiftyMoveCounter
			char blackToPlay

		cdef cppclass BOARD:
			int Square[64]

			BOARD()
			BOARD(int _Square[64], irreversibleState _state, char _fileToReadFrom[fileCharLength], int numMoves);

			int* getSquarePtr();

			ulong* getAttackedPtr();



	cdef extern from "InPycharmProject2/Debug.h" namespace "Debug":
		void genAllMovesDB(BOARD board)
		void printDirectionInfoFlat()
		void saveDistanceInfoToFile(const char* fileName)

		int* getDirInfoPointer();
		int* getDistInfoFlat();


charPieceEnum = {'k' : PieceEnum.king, 'n' : PieceEnum.knight, 'r' : PieceEnum.rook, 'p' : PieceEnum.pawn, 'b' : PieceEnum.bishop, 'q' : PieceEnum.queen}
for key in list(charPieceEnum.keys()):
	charPieceEnum[charPieceEnum[key]] = key



def getAllRed(pyBoard Board, colour = 0):

	genAllMovesDB(Board.board)
	cdef ulong* attack
	attack = Board.board.getAttackedPtr()
	lst = []
	for i in range(64):
		if attack[colour] & (1 << i):
			lst.append([i, "red"])

	return lst




# HASH function and PE (formerly called PieceEnum
IF True:
	cpdef ulong HASH(string):
		cdef ulong hash = 5381

		for CHAR in string:
			hash = hash*33 + ord(CHAR)
		return hash

	ctypedef public enum PE:
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

def initAll(seed):
	def HASH(string):
		cdef ulong hash = 5381
		for char in string:
			hash = ((hash << 5) + hash) + ord(char)

		return hash

	if type(seed) == str:
		InitAll(HASH(seed))
	elif type(seed) == int:
		InitAll(seed)
	else:
		raise ValueError, "initAll needs a string or int as a seed"


cdef class pyBoard:
	cdef BOARD board



	def __init__(self, fenString = startingFen, fileToReadFrom = None):
		IF True:
			cdef int[64] square
			cdef irreversibleState _state


			fileStr = cppSourceFolder
			if (fileToReadFrom == None):
				fileStr += "FILE.dat"
			else:
				fileStr += fileToReadFrom

			cdef char[100] fileArr
			for i in range(100):
				fileArr[i] = 0
			for i, Char in enumerate(fileStr):
				fileArr[i] = ord(Char)

			if True:
				if fenString == 'empty':
					fenString = '8/8/8/8/8/8/8/8 w KQkq - 0 1'
				square = copy.deepcopy(np.zeros((64)).astype('i'))

				# fen stuff (setting square)
				if True:
					parts = fenString.split(' ')
					assert (len(parts) != 6, 'invalid fen string, must have 6 parts')

					pieceEnumstr = parts[0]

					rows = pieceEnumstr.split('/')

					for rank in range(8):

						file = 0
						row = rows[rank]
						CharInd = 0
						while file < 8:
							Char = row[CharInd]
							if ord(Char) >= 48 and ord(Char) <= 57:  # if it is a number
								file += int(Char)  # file += the integer
							else:
								if Char.isupper():
									colour = PieceEnum.white
								else:
									colour = PieceEnum.black

								# (7 - rank) makes sure that it adds them from the top down, not bottom up
								square[8 * (7 - rank) + file] = charPieceEnum[Char.lower()] | colour

								file += 1
							CharInd += 1


					if fenString == startingFen:
						print('starting config')
					elif fenString == '8/8/8/8/8/8/8/8 w KQkq - 0 1':
						print('empty board')
					else:
						print('weird starting')


				_state.blackToPlay = parts[1] == 'b'
				if parts[1] == 'b':
					assert(_state.blackToPlay == 1)


				#doing castling permissions
				castling = parts[2]
				if castling == '-':
					_state.castleRights = 0
				else:
					# setting the individual castling permissions
					_state.castleRights |= 1 << 0 if 'K' in castling else 0
					_state.castleRights |= 1 << 1 if 'Q' in castling else 0
					_state.castleRights |= 1 << 2 if 'k' in castling else 0
					_state.castleRights |= 1 << 3 if 'q' in castling else 0

				#doing the move counters
				_state.fiftyMoveCounter = int(parts[4])
				fullMoves = int(parts[5])
				numMoves = 2*fullMoves
				numMoves += 1 if parts[1] == 'b' else 0 # if it is black to play add 1, else 0




				if parts[3] == '-':
					enPassantFile = 64
				else:
					enPassantFile = StringToPos(parts[3]) % 8

			self.board = BOARD()
			self.board = BOARD(square, _state, fileArr, numMoves)




	cdef Move pyGenNormalMove(self, start, end):
		cdef Move move
		move.start = start
		move.end = end
		move.piece = self.board.Square[start]
		move.piece |= self.board.Square[end] << 4
		return move

	def doNormalMove(self, start, end):
		#self.board.
		pass









	def getSquare(self):
		IF True:
			cdef int newSquare[64]
			memcpy(&newSquare, self.board.getSquarePtr(), 64 * 4)

			pySquare = np.zeros((8,8), dtype='i')
			for rank in range(8):
				for file in range(8):
					pySquare[rank, file] = newSquare[8*rank + file]

			return pySquare


def pyInitAll(seed):
	InitAll(<int>seed)

def getDirInfo():
	cdef int* dirs = getDirInfoPointer()


	a = np.zeros((16,9), dtype=int)
	for i in range(16):
		for j in range(9):
			a[i,j] = dirs[16*i + j]
	return a

def getDistInfo():
	cdef int* dists = getDirInfoPointer()
	a = np.zeros((64,37), dtype=int)
	for i in range(64):
		for j in range(37):
			a[i,j] = dists[64*i + j]
	return a


pyInitAll(1)





