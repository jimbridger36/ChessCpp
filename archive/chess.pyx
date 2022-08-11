#distutils: language = c++
#distutils: extra_compile_args = ["-std=c++20"]
import numpy as np
cimport numpy as np
from libc.stdlib cimport malloc, free
from cython cimport sizeof as size
from libcpp.unordered_map cimport unordered_map as htable
from libcpp cimport bool

ctypedef unsigned char uchar
ctypedef int[:,:] intMV
ctypedef int[:] intArr
ctypedef Py_ssize_t ind
DEF intSize = 4
DEF clearStackMem = False
DEF PointerSize = 8
DEF nullPosition = 70
ctypedef unsigned long ulong
import random


ctypedef int stackType

DEF DefaultFenString = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
DEF doingEnPassant = True
DEF checkMateVal = 256 # 8 bits long

cdef int enumToPieceVal[16]
enumToPieceVal[<int>PieceEnum.rook] = 5
enumToPieceVal[<int>PieceEnum.knight] = 3
enumToPieceVal[<int>PieceEnum.queen] = 8
enumToPieceVal[<int>PieceEnum.bishop] = 3
enumToPieceVal[<int>PieceEnum.pawn] = 1
enumToPieceVal[<int>PieceEnum.king] = 50

enumToPieceVal[PieceEnum.rook | PieceEnum.black] = -5
enumToPieceVal[PieceEnum.knight | PieceEnum.black] = -3
enumToPieceVal[PieceEnum.queen | PieceEnum.black] = -8
enumToPieceVal[PieceEnum.bishop | PieceEnum.black] = -3
enumToPieceVal[PieceEnum.pawn | PieceEnum.black] = -1
enumToPieceVal[PieceEnum.king | PieceEnum.black] = -50






cdef ulong pieceZVals[64][16]
cdef ulong miscZVals[13]

cdef ulong genRandUlong():
	cdef ulong rand1, rand2, rand3
	rand1 = random.getrandbits(32)
	rand2 = random.getrandbits(32)
	rand3 = rand1 | (rand2 << 64)
	return rand3

cdef htable[unsigned char, char] enPassantToFile = htable[uchar, char]()
cdef char i1
cdef unsigned char val
for i1 in range(0,8):
	val = i1
	val = (val << i1) >> 1
	enPassantToFile[val] = i1







def initZVals(str seed):
	random.seed(hash(seed))
	cdef ulong rand = genRandUlong()
	assert(rand != (rand >> 32))
	for square in range(64):
		pieceZVals[square][0] = 0
		for piece in range(1, 16):
			rand = genRandUlong()
			assert(rand != (rand >> 32))
			pieceZVals[square][piece] = rand
	for i in range(13):
		rand = genRandUlong()
		assert(rand != ((rand >> 32) << 32))
		miscZVals = rand








#checkmate value = 256




def flipy(arr):
	if True:
		maxrow = arr.shape[0] - 1
		newArr = np.zeros(arr.shape)

		for row in range(arr.shape[0] // 2):
			newArr[row] = arr[maxrow-row]
			newArr[maxrow-row] = arr[row]

		if arr.shape[0] % 2 == 1:
			newArr[arr.shape[0] // 2] = arr[arr.shape[0] // 2]
		return newArr

def zeroes(shape):
	return np.zeros(shape,dtype=np.int32)


#pyStringToC
IF True:
	cdef char* pyStringToC(str string, untilSpaces = False):
		cdef int numChars = len(string), i


		cdef char* cstr = <char*> malloc(numChars + 1)
		for i in range(numChars):
			cstr[i] = <char>ord(string[i])
		cstr[numChars] = <char>0

		'''for i in range(len(string)):
			if string[i] != ' ':
				cstr[i] = ord(string[i])
			else:
				break'''
		return cstr


IF True:
	cdef extern from "htable.cpp":
		cdef struct Move:
			int piece
			int start
			int end


		cdef cppclass ht:
			ht()
			ht(int empty)
			ht(char* file, int readreps)

			void writeToFile(char* file, int writeRepetitions)
			void readIndexesFromFile(char* file)
			void readFromFile(char* file)
			void readFromFile(char* file, bool readReps)
			bool check(ulong key, bool blackToPlay ,int depth, int& alpha, int& beta, int& eval , Move& bestMove)
			ulong*  getKeys()
			void printKeys()
		void printStuff(char*)


'''
cdef public struct Move:
	int piece
	int start
	int end'''

# newMove Move 'constructor'
IF True:
	cdef Move newMove(int pieceEnum, int start, int end):
		cdef Move move
		move.piece = pieceEnum
		move.end = end
		move.start = start
		return move



# BST Stuff
IF True:
	from libcpp.list cimport list as llist
	cimport cython.operator.dereference as deref
	cimport cython.operator.preincrement as preincrement


	cdef struct bstNode:
		int key
		Move val
		bstNode* left
		bstNode* right


	cdef struct BST:
		bstNode* root
		int num


	cdef bstNode* makeBSTNode(Move* valPtr, int key):
		cdef bstNode* ptr = <bstNode*>malloc(size(bstNode))
		ptr[0].key = key
		ptr[0].val = valPtr[0]
		ptr[0].left = NULL
		ptr[0].right = NULL
		return ptr


	cdef bstNode* addItemToNode(bstNode* nodePtr, Move* valPtr, int key):
		cdef bstNode* newNodePtr
		if nodePtr == NULL:
			newNodePtr = makeBSTNode(valPtr, key)
			return newNodePtr
		if key < nodePtr[0].key: # try left
			nodePtr[0].left = addItemToNode(nodePtr[0].left, valPtr, key)
			return nodePtr
		else: # try right
			nodePtr[0].right = addItemToNode(nodePtr[0].right, valPtr, key)
			return nodePtr


	cdef bstAddItem(BST* bstPtr, Move val, int key):
		if bstPtr[0].root == NULL:
			bstPtr[0].root = makeBSTNode(&val, key)
		else:
			addItemToNode(bstPtr[0].root, &val, key)
		bstPtr[0].num += 1


	cdef void traverseNodePop(bstNode* node, llist[Move]* llistPtr):
		if node != NULL:
			traverseNodePop(node[0].left, llistPtr)
			llistPtr[0].push_back(node[0].val)
			traverseNodePop(node[0].right, llistPtr)
			free(node)

	cdef inline bint ifCaptureNode(bstNode* bstNodePtr):
		if bstNodePtr == NULL:
			return False
		else:
			return (bstNodePtr[0].val.piece >> 4) & 0b1111 > 0 or \
					ifCaptureNode(bstNodePtr[0].left) or \
					ifCaptureNode(bstNodePtr[0].right)


	cdef inline bint ifCaptureTree(BST* bst):
		return ifCaptureNode(bst[0].root)




	cdef void bstTraversePop(BST* tree, llist[Move]* ll):
		traverseNodePop(tree[0].root, ll)

	# only here for debugging
	cdef void traverseTreePrint(BST* tree):
		print('traversing tree')
		traverseNodePrint(tree[0].root)


	cdef void traverseNodePrint(bstNode* node):
		if node != NULL:
			traverseNodePrint(node[0].left)
			print(node[0].key, node[0].val)
			traverseNodePrint(node[0].right)



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
	              PieceEnum.queen : np.array([[1,0], [-1,0], [0,1], [0,-1],[1,1], [1,-1], [-1,1], [-1,-1]]),
	              PieceEnum.knight : np.array( [[2,1], [2,-1], [-2,1], [-2,-1], [1,2], [1,-2], [-1,2], [-1,-2]] )
	              }
	import copy
	directions = {PieceEnum.rook : [],
	              PieceEnum.bishop : [],
	              PieceEnum.queen : [],
	              PieceEnum.knight : []
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


def pcpy(str):
	printStuff(pyStringToC(str))


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
cdef public np.ndarray distanceInfoArrVec = np.zeros((8,8,5,5),dtype=np.int32)
# distance info will be like this, a 8x8 grid of a 5x5 item, this item has the distance possible in the normal directions,
# to access the cell that represents going 1 up, 0 across go item[1+2,0+2] or a up, b across item[a+2,b+2]
# for horse possibilities (2,1) for example, go item[2+2,1+2]

cdef public np.ndarray distanceSquare = np.zeros((8,8,37),dtype=np.int32)
cdef public np.ndarray distanceInfoFlat = np.zeros((64,37))

cdef dict dirsPlus18 = {}
cdef dict dirToDistance

# get stuff for python
IF True:
	def getDistanceInfoArrVec():
		return distanceInfoArrVec

	def getDistanceInfoFlat():
		return distanceInfoFlat

	def getDistanceSquare():
		return distanceSquare

# computeDistanceInfo
IF True:
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




# declaring PiecePos and makePiecePos
IF True:
	cdef public struct PiecePos:
		int piece
		int pos

	cdef PiecePos makePiecePos(int pieceEnum, int pos):
		cdef PiecePos piecePos
		piecePos.piece = pieceEnum; piecePos.pos = pos
		return piecePos


cdef inline bint capture(Move move):
	return (move.piece >> 4) & 0b1111

# reprMove
IF True:
	cdef str reprMove(Move item):
		cdef str msg = ''
		msg += str(item.piece & 0b1111) + ' at ' + str(item.start) + ' going to ' + str(item.end)
		if item.piece >> 4:
			msg += ' to capture ' + str(item.piece >> 4)
		return msg

# reprPiecePos, isColour, isBlack, isWhite
IF True:
	cpdef str reprPiecePos(PiecePos piecePos):
		return intToPieceString[piecePos.piece] + ' at ' + str(piecePos.pos)

	cpdef bint isColour(bint black, int piece):
		return (black == (piece >> 3)) and piece != 0

	cpdef bint isBlack(int piece):
		return piece >> 3 and piece != 0

	cpdef bint isWhite(int piece):
		return not piece >> 3 and piece != 0


cdef void checkBint(bint Bint):
	cdef int shouldBeInt = 1 if Bint > 0 else 0
	assert(Bint == shouldBeInt)


# KingMoves
'''IF True:
	cdef list KingMoves(intArr SquareFlat, int piece, int pos):

		cdef list moves = []
		cdef bint black = piece > 8

		for dir in directions[PieceEnum.king]:
			if distanceInfoFlat[pos][dir+18] > 0 and not isColour(black, SquareFlat[pos + dir]):
				moves.append(newMove)
		return moves'''


cdef class Piece:
	cdef public int pieceInt
	cdef public int pos


cdef int colEnPasRank[2]
colEnPasRank[0] = 3
colEnPasRank[1] = 4





# isOfType
IF True:
	cpdef makeVec2(x,y):
		return np.array([x,y])


	cpdef bint inBounds(np.ndarray pos):
		return not pos[0] < 0 or pos[0] > 8 or pos[1] < 0 or pos[1] > 8


	cpdef int VecToInt(np.ndarray[ndim=2,dtype=int] vec):
		return vec[0]*8 + vec[1]

	cpdef bint isOfType(int piece, int type):
		return (piece | type) == piece




cdef struct irreversibleState:
	char castle
	char enPassantSquare
	char fiftyMoveCounter

IF True:
	cdef struct Stack:
		stackType* arr
		int top
		int capacity


	cdef Stack makeStack(int length):
		cdef Stack stack
		stack.arr = <stackType*> malloc(length * size(stackType))
		stack.capacity = length
		return stack


	cdef void memcpy(stackType* dst, stackType* src, int length) :
		cdef ind i
		for i in range(length):
			dst[i] = src[i]


	cdef void enlarge(Stack* stackPtr) :
		cdef stackType* tmp = stackPtr[0].arr
		stackPtr[0].arr = <stackType*> malloc(stackPtr[0].capacity * 2 * size(stackType))
		memcpy(stackPtr[0].arr, tmp, stackPtr[0].capacity)
		stackPtr[0].capacity *= 2
		return



	cdef void push(Stack* stackPtr, stackType val) :
		if stackPtr[0].capacity == stackPtr[0].top:
			enlarge(stackPtr)
		stackPtr[0].arr[stackPtr[0].top] = val
		stackPtr[0].top += 1


	cdef list getAll(Stack* stackPtr):
		cdef list items = []
		cdef ind i
		for i in range(stackPtr[0].top-1, 0-1, -1):
			print(i)
			items.append(stackPtr[0].arr[i])
		return items


	cdef stackType pop(Stack* PTR):
		PTR[0].top -= 1
		IF clearStackMem:
			cdef stackType tmp = PTR[0].arr[PTR[0].top]
			PTR[0].arr[PTR[0].top] = 0
			return tmp
		ELSE:
			return PTR[0].arr[PTR[0].top]



	cdef stackType peek(Stack* stackPtr):
		return stackPtr[0].arr[stackPtr[0].top - 1]

	cdef void freeStackArr(Stack* stackPtr):
		free(stackPtr[0].arr)








cdef class Board:
	cdef public int[64] Square
	cdef public list pieceEnums
	cdef bint BlackToPlay
	cdef int fiftyMoveCounter, fullMoves
	cdef int whiteKingPos, blackKingPos
	cdef ht table
	cdef ulong ZVal
	cdef irreversibleState* stateStack
	cdef int currentPly
	cdef int[2] kingPositions

	cdef int enPassantSquare
	cdef uchar enPassant

	cdef bint CastleBool # if allowed to castle at all
	# white kingside, white queenside, black kingside, black queenside
	cdef char castleRights # whos allowed to castle
	cdef int materialBalance


	cdef int approximation(self, ulong hash):
		return 0





	cdef void GeneratePieceMoves(self, int pos, BST* bst, int piece = 0):
		if piece == 0:
			piece = self.Square[pos]

		if piece in [0,1,8,9, 5, 5+8]: # dont know how to deal with these yet DEBUG
			return
		cdef int maxDist
		cdef bint black = piece > 8
		checkBint(black)

		cdef int targetPos
		cdef int dir
		cdef int pieceType = piece & 0b0111
		cdef Move move

		cdef int eval

		for Adir in directions[pieceType]:
			dist = 1
			dir = Adir
			maxDist = distanceInfoFlat[pos,dir + 18]
			targetPos = pos + dir


			while dist <= maxDist and self.Square[targetPos] == 0:
										# flags TODO
				move = newMove(piece, pos, targetPos)

				eval = self.approximation(self.ZVal) #TODO, this is a placeholder
				#         tree, val,  key
				bstAddItem(bst, move, eval) # DEBUG change this

				print(dir, targetPos, 'dir, targetPos')

				dist += 1
				targetPos += dir

			# if it didnt stop because it ran out of room and if it is of different colour
			if (not dist > maxDist) and not isColour(black, self.Square[targetPos]):
				move = newMove(piece | (self.Square[targetPos] << 4), pos, targetPos)
				eval = self.approximation(self.ZVal) # TODO, placeholder like above
				bstAddItem(bst, move, eval)
				print(dir, targetPos, 'dir, targetPos capture')


	cdef llist[Move]* getAllMoves(self):
		moves = []
		newMoves = []
		cdef BST bstObj
		bstObj.root = NULL
		bstObj.num = 0
		cdef BST* bst = &bstObj


		for pos in range(64):
			if self.Square[pos] != <int>0:
				continue
			self.GeneratePieceMoves(pos, bst)

		cdef llist[Move] ll = llist[Move]()
		bstTraversePop(bst, &ll)
		return &ll


	def getRedSquares(self, pos):
		IF True:
			cdef BST bstOBJ
			cdef BST* bst = &bstOBJ
			bst[0].num = 0
			bst[0].root = NULL
			self.GeneratePieceMoves(pos, bst)
			cdef llist[Move] ll = llist[Move]()
			bstTraversePop(bst, &ll)

			moves = []
			cdef Move move

			cdef int numMoves = ll.size()

			cdef llist[Move].iterator ITER = ll.begin()
			for i in range(numMoves):
				move = deref(ITER)
				moves.append(<int>move.end)
				preincrement(ITER)
			ll.clear()
			return moves


	cdef inline void pushStateToStack(self):
		self.stateStack[self.currentPly].castle = self.castleRights
		self.stateStack[self.currentPly].enPassantSquare = self.enPassantSquare
		self.stateStack[self.currentPly].fiftyMoveCounter = self.fiftyMoveCounter


	cpdef void genZVal(self):
		IF True:
			cdef int square
			cdef ulong val = 0
			for square in range(64):
				val = val ^ pieceZVals[square][self.Square[square]]
			assert(val != 0, 'after the pieces')
			cdef int inc = 0

			# side to move
			if self.BlackToPlay:
				val = val ^ miscZVals[inc + 0]
			inc += 1

			#castle permissions
			cdef int i
			for i in range(4):
				if (self.castleRights >> (inc + i)) & 1:
					val = val ^ miscZVals[inc + i]
			inc += 4

			val ^= 0

			#en passant
			if self.enPassantSquare != 0:
				val = val ^ miscZVals[inc + self.enPassantSquare % 8]
			self.ZVal = val
			cdef bint asse = self.ZVal != 0
			assert(asse)

	def getZ(self):
		return self.ZVal



	cdef void updateZVal(self, Move move):
		IF True:
			# whos to move
			self.ZVal ^= miscZVals[0]

			# if change in castling rights
			cdef int i1
			cdef int change = self.stateStack[self.currentPly-1].castling ^ self.stateStack[self.currentPly].castling
			if change:
				for i1 in range(4):
					if (change >> i1) & 1:
						self.ZVal ^= miscZVals[1 + i1]

			# enPassant
			# if there is a change
			if self.enPassantSquare != self.stateStack[self.currentPly-1].enPassantSquare:
				if self.enPassantSquare == 0:
					self.ZVal ^= miscZVals[5 + (self.stateStack[self.currentPly-1].enPassantSquare % 8)]
				elif self.stateStack[self.currentPly-1].enPassantSquare == 0:
					self.ZVal ^= miscZVals[5 + (self.enPassantSquare % 8)]
				else:
					self.ZVal ^= miscZVals[5 + (self.enPassantSquare % 8)]
					self.ZVal ^= miscZVals[5 + (self.stateStack[self.currentPly-1].enPassantSquare % 8)]


			# if anything but a normal move
			if move.piece >> 8:
				# if en passant
				if (move.piece >> 8) & 1:
					# remove old pawn
					self.ZVal ^= pieceZVals[move.start][move.piece & 0b1111]

					# add new pawn
					self.ZVal ^= pieceZVals[move.end][move.piece & 0b1111]

					# remove captured pawn               colour                         piece with opposite colour
					self.ZVal ^= pieceZVals[colEnPasRank[((move.piece >> 3) ^ 1) & 1]][(move.piece & 0b1111) ^ 0b1000]

				# if castling
				elif (move.piece >> 8) & 0b10:

					#                       new rook position
					self.ZVal ^= pieceZVals[(move.start + move.end) / 2][PieceEnum.rook | (move.piece & 0b1000) ]

					#                       old rook position, if queenside                       old rook position
					self.ZVal ^= pieceZVals[move.start - 4 if (move.end - move.start - 2) else (move.start + 3)][PieceEnum.rook | (move.piece & 1000) ]

					# old king position
					self.ZVal ^= pieceZVals[move.start][move.piece & 0b1111]

					# new king position
					self.ZVal ^= pieceZVals[move.end][move.piece & 0b1111]
				# if promoting
				elif (move.piece >> 8) & 0b100:
					# old pawn position
					self.ZVal ^= pieceZVals[move.start][move.piece & 0b1111]

					# removing captured piece
					self.ZVal ^= pieceZVals[move.end][move.piece & 0b11110000]

					# adding new piece
					self.ZVal ^= pieceZVals[move.end][move.piece >> 12]
				# if draw
				elif (move.piece >> 8) & 0b1000:
					# do nothing
					pass
				return
				# finish

			# if a normal move
			# removing initial piece
			self.ZVal ^= pieceZVals[move.start][move.piece & 0b1111]

			# removing captured piece
			self.ZVal ^= pieceZVals[move.end][move.piece & 0b11110000]

			# adding new moved piece
			self.ZVal ^= pieceZVals[move.end][move.piece & 0b1111]

	def INCheck(self, black, pos):
		return self.inCheck(black, pos)


	cdef bool inCheck(self, bint black, int pos = 70):
		cdef BST bstOBJ
		checkBint(black)
		bstOBJ.root = NULL
		bstOBJ.num = 0
		cdef BST* bst
		bst = &bstOBJ
		if pos == 70:
			pos = self.kingPositions[black]

		self.GeneratePieceMoves(pos, bst, PieceEnum.queen | (black << 3))
		if ifCaptureTree(bst):
			return True


		self.GeneratePieceMoves(pos, bst, PieceEnum.knight | (black << 3))
		if ifCaptureTree(bst):
			return True

		return False










	# FEN, lowercase is black, upper is WHITE
	def __init__(self, htableFile = "FILE.dat", fenString = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'):
		if True:
			if fenString == 'empty':
				fenString = '8/8/8/8/8/8/8/8 w KQkq - 0 1'
			self.Square = copy.deepcopy(zeroes((64)))

			if True:
				parts = fenString.split(' ')
				assert(len(parts) != 6,'invalid fen string, must have 6 parts')

				pieceEnumstr = parts[0]

				rows = pieceEnumstr.split('/')

				charToPieceEnum = {'k' : PieceEnum.king, 'n' : PieceEnum.knight, 'r' : PieceEnum.rook, 'p' : PieceEnum.pawn, 'b' : PieceEnum.bishop, 'q' : PieceEnum.queen}


				for rank in range(8):

					file = 0
					strpos = 0
					row = rows[rank]
					while file < 8:
						Char = row[file]
						if ord(Char) >= 48 and ord(Char) <= 57: # if it is a number
							file += int(Char) # file += the integer
						else:
							if Char.isupper():
								colour = PieceEnum.white
							else:
								colour = PieceEnum.black

							# (7 - rank) makes sure that it adds them from the top down, not bottom up
							# Debug
							pieceEnum = charToPieceEnum[Char.lower()] | colour
							self.materialBalance += enumToPieceVal[pieceEnum]
							# setting the king position
							if isOfType(pieceEnum, PieceEnum.king):
								if isBlack(pieceEnum):
									self.kingPositions[<int>colour] = 8 * (7 - rank) + file
									if self.blackKingPos != 0: # if there is already a black king (i.e. the fen string has 2 black kings)
										assert(False, 'there are two black kings in the fen string')
									self.blackKingPos = 8 * (7 - rank) + file
								else:
									if self.whiteKingPos != 0:
										assert(False, 'there are two white kings in the fen string')
									self.whiteKingPos = 8 * (7 - rank) + file



							self.Square[8 * (7 - rank) + file] = charToPieceEnum[Char.lower()] | colour

							file += 1
						strpos += 1
				if fenString == DefaultFenString:
					print('starting config')
				elif fenString == '8/8/8/8/8/8/8/8 w KQkq - 0 1':
					print('empty board')
				else:
					print('weird starting')

				self.BlackToPlay = parts[1] == 'b'

				#doing castling permissions
				castling = parts[2]
				if castling == '-':
					self.CastleBool = False
				else:
					self.CastleBool = True
					# setting the individual castling permissions
					self.castleRights |= 1 >> 0 if 'K' in castling else 0
					self.castleRights |= 1 >> 1 if 'Q' in castling else 0
					self.castleRights |= 1 >> 2 if 'k' in castling else 0
					self.castleRights |= 1 >> 3 if 'q' in castling else 0


				#doing the move counters
				self.fiftyMoveCounter = int(parts[4])
				self.fullMoves = int(parts[5])

				if parts[3] == '-':
					self.enPassantSquare = -1
				else:
					self.enPassantSquare = StringToPos(parts[3])

		cdef char* cFile = pyStringToC(htableFile)
		printStuff(cFile)
		if htableFile == "none":
			self.table = ht(<int>0)
		else:
			self.table = ht(cFile, 0)
		free(cFile)

		self.stateStack = <irreversibleState*>malloc(5000*size(irreversibleState))

	cdef inline void transferPiece(self, int start, int end):
		#DEBUG
		assert(self.Square[end] == 0)

		# put the piece in the new spot
		self.ZVal ^= pieceZVals[end][self.Square[start]]
		self.Square[end] = self.Square[start]

		# then remove old piece
		self.ZVal ^= pieceZVals[start][self.Square[start]]
		self.Square[start] = 0

		self.ZVal ^= pieceZVals[end][piece]
		self.Square[end] = piece


	cdef inline void removePiece(self, int pos):
		#DEBUG
		assert(self.Square[pos] != 0)

		self.materialBalance -= enumToPieceVal[self.Square[pos]]

		self.ZVal ^= pieceZVals[pos][self.Square[pos]]
		self.Square[pos] = 0

	cdef inline addPiece(self, int pos, int piece):
		#DEBUG
		assert(self.Square[pos] == 0)

		self.materialBalance += enumToPieceVal[piece]

		self.ZVal ^= pieceZVals[pos][piece]
		self.Square[pos] = piece



	cdef bint makeMove(self, Move move):

		cdef bint black  = (move.piece & 0b1000) > 0
		cdef bint white = (move.piece & 0b1000) == 0
		checkBint(black)

		# if not a normal move, if flags are set
		if move.piece >> 8:
			# if en passant
			if (move.piece >> 8) & 1:

				# the captured pawn		# file          + rank * 8
				capturedPos =           (move.end % 8) + (3 + white) * 8
				self.removePiece(capturedPos)

				# moving the pawn doing the en passant
				self.transferPiece(move.start, move.end)

			


























	# getSquare, setBoard, setPiece, setPieceWithPiece
	IF True:
		def getSquare(self, flat = False, flip = False):
			cdef intMV mv = np.zeros((8,8), dtype=np.int32)
			if flat:
				return np.asarray(self.Square)
			for rank in range(8):
				for file in range(8):
					mv[rank,file] = self.Square[rank*8 + file]
			if flip:
				return flipy(np.asarray(mv))
			else:
				return np.asarray(mv)

		def setBoard(self, nparray):
			if True:
				if nparray.shape == (8,8):
					for rank in range(8):
						for file in range(8):
							self.Square[rank*8 + file] = nparray[rank,file]
				elif nparray.shape == (64):
					for rank in range(8):
						for file in range(8):
							self.Square[rank*8 + file] = nparray[rank,file]
				else:
					assert(False,'invalid board')

		cpdef setPiece(self, piece, pos = -100, pos2 = -100_000):
			if True:
				if pos != -100:
					if pos2 != -100_000:
						pos = pos*8 + pos2
					self.Square[pos] = piece
				else:
					self.setPieceWithPiece(piece)

		cpdef setPieceWithPiece(self, piece):
			self.Square[piece.pos] = piece.pieceInt









# ported
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



#unpacking stuff
IF True:
	cpdef np.ndarray unPackNP3(np.ndarray[int,ndim=3] inp):
		cdef np.ndarray arr

		arr = zeroes((inp.shape[0] * inp.shape[1], inp.shape[2]))

		for row in range(inp.shape[0]):
			for file in range(inp.shape[1]):
				arr[8*row + file] = inp[row,file]
		return arr


	cpdef int[:] unPack(intMV mv):
		cdef int[:] arr = zeroes((mv.shape[0] * mv.shape[1]))
		for row in range(mv.shape[0]):
			for file in range(mv.shape[1]):
				arr[8*row + file] = mv[row,file]
		return arr

	cpdef void unPackTo(intMV mv, int[:] out):
		for row in range(mv.shape[0]):
			for file in range(mv.shape[1]):
				out[8*row + file] = mv[row,file]

	cpdef PackInto(int[:] arr, intMV, mv):
		for rank in range(mv.shape[0]):
			for file in range(mv.shape[1]):
				mv[rank,file] = arr[8*rank + file]



