#distutils: language=c++
from libc.stdlib cimport malloc, free
from libcpp.list cimport list as llist
cimport cython.operator.dereference as deref
cimport cython.operator.preincrement as preincrement
from cython cimport sizeof as size
from libcpp.unordered_map cimport unordered_map as htable



cdef extern from "chessCPP/htSRC.cpp":
	void doStuff()
	int func(int, int)


print(func(1,1))

