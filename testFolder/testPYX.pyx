#distutils: language = c++
#distutils: extra_compile_args = ["-std=c++20"]
#distutils: sources = testFolder/testCPP.cpp


cdef extern from "testH.h":
    int func(int a)

cdef int a, A
a = 1
A = func(a)


