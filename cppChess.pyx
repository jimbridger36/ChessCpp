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

# importing
from libcpp cimport bool
from libc.string cimport memcpy
import copy
import numpy as np
cimport numpy as np
from helperPY import *

ctypedef unsigned long long ulong

IF True:
	# default data declarations
	IF True:
		DEF cppSourceFolder = "InPycharmProject2/"

		DEF defaultSeed = "hello"

		startingFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
		DEF fileCharLength = 100
		DEF maxMoves = 6000
		DEF nullPosition = 64

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
			int directionInfoFlat[16][9]
			int distanceInfoAdd18[64][37]
			int colourEnPassantRank[2]



		cdef extern from "InPycharmProject2/Board.h" namespace "Board":
			cdef cppclass irreversibleState:
				char castleRights
				char enPassantFile
				char fiftyMoveCounter
				char blackToPlay

			cdef cppclass BOARD:
				int Square[64]
				int currentPly

				irreversibleState stateStack[maxMoves]
				Move moveStack[maxMoves]

				BOARD()
				BOARD(int _Square[64], irreversibleState _state, char _fileToReadFrom[fileCharLength], int numMoves);

				void makeMove(Move move)
				void unmakeMove()

				int* getSquarePtr();

				ulong* getAttackedPtr();
				ulong getAttacked(int index);

				#void setAttack(int col, ulong value)





		cdef extern from "InPycharmProject2/Debug.h" namespace "Debug":
			Move* genAllMovesDB(BOARD board, int& num)
			void printDirectionInfoFlat()
			void checkDistance(bool printTrue)
			void printAttack0D(BOARD board)
			ulong printZVal(BOARD board)


			#void saveDistanceInfoToFile(const char* fileName)




			#int* getDirInfoPointer();
			#int* getDistInfoFlat(int* ptr);

	# setting up charPieceEnum
	IF True:
		charPieceEnum = {'z' : 0 , 'k' : PieceEnum.king, 'n' : PieceEnum.knight, 'r' : PieceEnum.rook, 'p' : PieceEnum.pawn, 'b' : PieceEnum.bishop, 'q' : PieceEnum.queen}
		for key in list(charPieceEnum.keys()):
			charPieceEnum[key.upper()] = charPieceEnum[key] + 8


		for key in list(charPieceEnum.keys()):
			charPieceEnum[charPieceEnum[key]] = key

	# PosToStr, reprMove, movToStr
	IF True:
		def PosToStr(pos):
			rank = pos // 8
			file = pos % 8
			return chr(ord('a') + file) + str(rank + 1)

		# reprMove
		'''cdef str reprMove(Move move):
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
					movingPiece = movingPiece.upper()'''

		cdef str reprMove(Move move):
			moving = move.piece & 0b1111
			captured = (move.piece >> 4) & 0b1111
			flags = (move.piece >> 8) & 0b1111
			promPiece = (move.piece >> 12) & 0b1111
			start = move.start
			end = move.end
			string = "| " +charPieceEnum[moving] + " " + PosToStr(start) + "-> " + PosToStr(end)
			if captured != 0:
				string+= ", captured: " + charPieceEnum[captured]
			if flags != 0:
				string += ", flags: " + str(flags) + ", PromPiece: " + str(promPiece)
			return string


		def pairStrToPos(a, b):
			ra, rb = a, b
			if type(a) == str:
				ra = StringToPos(a)
			if type(b) == str:
				rb = StringToPos(b)
			return ra, rb


		cdef movToString(Move move):
			moving = move.piece & 0b1111
			captured = (move.piece >> 4) & 0b1111
			flags = (move.piece >> 8) & 0b1111
			promPiece = move.piece >> 12

			string = ''
			if flags != 0:
				string = 'FLAGS'

			#TODO: write code to do this for flagged moves, probs from reprMove (commented out) above

			if (moving & 0b0111) == PE.pawn:
				string += PosToStr(move.start)
			else:
				print('moving piece: ', moving & 0b0111)
				string += charPieceEnum[moving & 0b0111]
				string += PosToStr(move.start)
			if captured != 0:
				string += 'x'

			if captured != 0:
				string += charPieceEnum[captured & 0b0111] + PosToStr(move.end)
			else:
				string += PosToStr(move.end)

	# HASH function, PE (formerly called PieceEnum), setting up pyDistanceInfo, pyDirectionInfo
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

		distanceInfoPy = np.zeros((64, 37), dtype=int)
		for i in range(64):
			for j in range(37):
				distanceInfoPy[i][j] = distanceInfoAdd18[i][j]

		directionInfoPy = np.zeros((16,9), dtype=int)

		for i in range(16):
			for j in range(9):
				directionInfoPy[i][j] = directionInfoFlat[i][j]




def pyCheckDist():
	checkDistance(False)
'''
def getAllRed(pyBoard Board, colour = 0):
	IF True:
		cdef Move* moves
		cdef int num

		print('initial attacked')
		#printAttack0D(Board.cBoard)

		moves = genAllMovesDB(Board.cBoard, num)


		#print('after attacked')
		#printAttack0D(Board.cBoard)

		print("there are ", num, " moves")
		cdef ulong* attack
		attack = Board.cBoard.getAttackedPtr()
		#print('initial attacked')
		#printAttack0D(Board.cBoard)
		lst = []

		lstMoves = []

		print("lstMoves: ")
		print("")
		for i in range(num):
			lstMoves.append(reprMove(moves[i]))
			print(reprMove(moves[i]))
		print('lstMoves ended')

		#Board.cBoard.setAttack(0, <ulong> 3)
		attack = Board.cBoard.getAttackedPtr()

		cdef ulong att
		att = Board.cBoard.getAttacked(0)
		print(att)

		att = attack[0]
		print(att)
		print(attack[0], attack[1])
		for i in range(64):
			if (attack[colour] >> i) & 1:
				lst.append([i, "red"])

		return lst
'''




'''def initAll(seed):
	IF True:
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
			raise ValueError, "initAll needs a string or int as a seed"'''


# pyBoard class
IF True:
	cdef class pyBoard:
		cdef BOARD cBoard



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

				#self.cBoard = BOARD()
				print("about to do BOARD constructor")
				self.cBoard = BOARD(square, _state, fileArr, numMoves)

		cdef Move pyGenNormalMove(self, start, end):
			cdef Move move
			move.start = start
			move.end = end
			move.piece = self.cBoard.Square[start]
			move.piece |= self.cBoard.Square[end] << 4
			return move


		def printZ(self):
			printZVal(self.cBoard)

		def doNormalMove(self, start, end):
			start, end = pairStrToPos(start, end)
			cdef Move move = self.pyGenNormalMove(start, end)
			print('about to do this move ' + reprMove(move))
			self.cBoard.makeMove(move)


		def pyUndoMove(self):
			cdef Move move
			for i in range(maxMoves):
				move = self.cBoard.moveStack[i]
				if not ( (move.piece == 0) and (move.start == 64) and (move.end == 64) ):
					print(i, reprMove(move))


			self.cBoard.unmakeMove()

		def getSquare(self):
			IF True:
				cdef int newSquare[64]
				memcpy(&newSquare, self.cBoard.getSquarePtr(), 64 * 4)

				pySquare = np.zeros((8, 8), dtype='i')
				for rank in range(8):
					for file in range(8):
						pySquare[rank, file] = newSquare[8 * rank + file]

				return pySquare

		def getAllRed(self, colour = 0):
			IF True:
				cdef Move * moves
				cdef int num

				print('initial attacked')
				printAttack0D(self.cBoard)

				moves = genAllMovesDB(self.cBoard, num)

				print('after attacked')
				printAttack0D(self.cBoard)

				print("there are ", num, " moves")
				#cdef ulong * attack
				#attack = self.cBoard.getAttackedPtr()
				#print('initial attacked')
				#printAttack0D(self.cBoard)
				#print(self.getSquare()[11])
				lst = ([],[])

				lstMoves = []

				print("lstMoves: ")
				print("")
				for i in range(num):
					lstMoves.append(reprMove(moves[i]))
					print(reprMove(moves[i]))
				print('lstMoves ended')

				#Board.cBoard.setAttack(0, <ulong> 3)
				attack = self.cBoard.getAttackedPtr()



				print('attacked: ', attack[0], attack[1])
				for colour in [0,1]:
					for i in range(64):
						if (attack[colour] >> i) & 1:
							lst[colour].append([i, "red"])

				return lst





def pyInitAll(seed):
	InitAll(<int>seed)


def numToColSq(num : int, col='red'):
	lst = []
	for i in range(64):
		if ((num >> i) & 1) == 1:
			lst.append([i,col])
	return lst

# just getDir/DistInfo
'''
IF True:
	def getDirInfo():
		cdef int* dirs = getDirInfoPointer()


		a = np.zeros((16,9), dtype=int)
		for i in range(16):
			for j in range(9):
				a[i,j] = dirs[9*i + j]
		return a

	def getDistInfo():
		a = np.zeros((64,37), dtype=int)
		for i in range(64):
			for j in range(37):
				a[i,j] = distanceInfoAdd18[i][j]
		return a

'''
pyInitAll(1)


