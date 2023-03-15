# distutils : include_dirs = CppLib
# distutils : sources = CppLib/ch.c ch2.c
# distutils : language_level = 3
cdef extern from "CppLib/ch.c":
    pass

cdef extern from "CppLib/ch2.c":
    pass
cdef extern from "CppLib/ch2.h":
    pass

cdef extern from "CppLib/ch.h":
    int func1(int a)
    int func2(int a)


cdef int a, b
a = 6
b = func1(a)
print(b)

b = func2(a)
print(b)

