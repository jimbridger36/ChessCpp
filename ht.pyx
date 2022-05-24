#distutils: language = c++
#distutils: extra_compile_args = ["-std=c++20"]
#cython: debug=True
import numpy as np
cimport numpy as np
from libc.stdlib cimport malloc, free
from cython cimport sizeof as size
from libcpp.unordered_map cimport unordered_map
cimport cython
from libcpp cimport bool


DEF fullSize = 50




ctypedef unsigned long ulong


# py string to C
IF True:
	cdef char* pyStringToC(str string):
		cdef char* cstr = <char*> malloc(fullSize)
		for i in range(fullSize):
			cstr[i] = <char>0
		for i in range(len(string)):
			cstr[i] = ord(string[i])
		return cstr

cdef char* defaultFile = pyStringToC("FILE.dat")



cdef extern from "htable.cpp":
	cdef struct Move:
		int piece
		int start
		int end
	void printf(char*)


	cdef cppclass ht:
		ht(int empty)
		ht(char* file, int readreps)

		void writeToFile(char* file, int writeRepetitions)
		void readIndexesFromFile(char* file)
		void readFromFile(char* file)
		void readFromFile(char* file, bool readReps)
		bool check(ulong key, bool blackToPlay ,int depth, int& alpha, int& beta, int& eval , Move& bestMove)
		ulong*  getKeys()
		void printKeys()



cdef Move move

move = Move()
move.piece = 1
move.piece = 5
move = func(move)


cdef ht* HT = new ht(<int>0)
HT.readFromFile(defaultFile)



cdef Move func(Move move):
	move.piece = 1
	return move

cdef Move* func2(Move* movePtr):
	return movePtr + 1







'''

cdef ht* table = new ht()



table.set4()

print(table.size)



table.writeToFile(pyStringToC("FILE.dat"), <int>0)


cdef char* string = pyStringToC("hello")


table.printKeys()


#printArr(arr, table.getNumKeys())


'''



