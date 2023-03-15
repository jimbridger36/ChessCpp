from setuptools import setup, Extension
from Cython.Build import cythonize
import os
import numpy as np

# "Debug.cpp"
sourceCPPFiles = ["Board.cpp", "Info.cpp", "StartUpFunctions.cpp", "Universal.cpp", "Whtable.cpp", "ZStuff.cpp", "BoardMoveFuncs.cpp", "BoardZFuncs.cpp", "BoardMoveGen.cpp", "Debug.cpp"]
for index, file in enumerate(sourceCPPFiles):
    sourceCPPFiles[index] = "InPycharmProject2/" + file


#C:\Users\Jim\PyCharmProjects\ChessCPPAttemptBStrap\\testFolder\\

extensions = [
    Extension("cppChess", ["cppChess.pyx"] + sourceCPPFiles, extra_compile_args=["-std=c++20"], language="c++",
              include_dirs= ["InPycharmProject2", np.get_include()],
              define_macros= [("FROMCYTHON", None)]



              )
]


#setup(ext_modules=cythonize(extensions))


print(os.path.abspath(__file__))

setup(
    name="cppChess",
    ext_modules=cythonize(extensions),
    zip_safe=False
)



