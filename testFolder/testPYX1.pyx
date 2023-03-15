#distutils: language = c++
#distutils: extra_compile_args = ["-std=c++20"]

#distutils: sources = testFolder/testCPP2.cpp
'''
###distutils: sources = testCPP.cpp
'''
#from testPXD cimport A


cdef extern from "testCPP.cpp":
    int func(int a)

def show():
    cdef int a, A
    a = 3
    A = func(a)
    print(A)



