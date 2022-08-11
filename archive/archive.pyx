from libc.stdlib cimport malloc, free
cimport cython
from cython cimport sizeof as size
from cython cimport nogil

# part of a linked list implementation
IF True:

	ctypedef Node* NodePtr
	cdef Node* nullNodePtr
	ctypedef int nodeType

	cdef struct Node:
		Node* next
		Node* behind
		nodeType val

	cdef struct LL:
		Node* first
		Node* last
		int length
	'''
	cdef Node nod
	cdef nodeType nodeVal
	DEF nodeTypeSize = cython.sizeof(nodeVal)
	DEF nodeSize = cython.sizeof(nod)'''
	DEF nodeSize = 16

	cdef int ZERO = 0
	cdef LL lst


	cdef Node* chainNode(Node* nodePtr, nodeType val):
		cdef Node* newNodePtr = <Node*>malloc(size(Node))
		newNodePtr[0].val = val
		nodePtr[0].next = newNodePtr
		newNodePtr[0].next = <Node*>0
		return newNodePtr


	cdef void traverse(Node* ptr, list items):
		items.append(ptr[0].val)
		if ptr[0].next != <Node*>0:
			traverse(ptr[0].next,items)

	cdef void freeNode(Node* ptr):
		if ptr[0].next != <Node*>0:
			freeNode(ptr[0].next)
		free(ptr)

	cdef void delete(LL* listPtr, Node* ptr):
		listPtr.length -= 1
		if listPtr.

		pass

	from libcpp cimport vector


	def Traverse():
		lst = []
		traverse(ptr1, lst)
		return lst

	cdef int val2 = 2
	cdef Node node1
	node1.val = 1
	cdef Node* ptr1 = &node1

	cdef Node emptyNode


	cdef Node* ptr2 = chainNode(ptr1, <int>2)

	for i in range(10000):
		pass
	print(size(Node))


# Pawn move generation
'''def GenerateMoves(self,pos, SquareInt):
		rank = pos //8; file = pos % 8
		black = self.pieceInt > 7
		cdef list moves = []

		if black: moveDir = -1
		else: moveDir = 1

		# white move
		# if white and space ahead is empty
		if SquareInt[(rank + 1)*8 + file] == 0 and not black:
			moves.append(newMove(self.pieceInt, pos, (rank+1)*8 + file))
			# if it is in whites starting pos and white and there is space for it to go to
			if rank == 1 and not black and SquareInt[3*8 + file] == 0:
				moves.append(newMove(self.pieceInt, pos, 3*8 + file))
		# black move
		# if white and space ahead is empty
		elif SquareInt[(rank - 1)*8 + file] == 0 and black:
			moves.append(newMove(self.pieceInt, pos, (rank-1)*8 + file))
			# if it is in blacks starting pos and black and there is space for it to go to
			if rank == 6 and black and SquareInt[4*8 + file] == 0:
				moves.append(newMove(self.pieceInt, pos, 4*8 + file))


		# taking
		pieceInPos =  SquareInt[(rank + moveDir)*8 + (file + 1)]
		# to the right of the pawn
		
		if pieceInPos >= 1 + black*8 and pieceInPos <= 6 + black*8: # if pieceInPos is an enemy
			#TODO check if exposed to checkmate
			moves.append(newMove(self.pieceInt,pos, (rank + moveDir)*8 + (file+1)))
		#to the left of the pawn
		#pieceInPos ='''



