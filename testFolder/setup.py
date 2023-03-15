from setuptools import setup, Extension
from Cython.Build import cythonize
import os

#C:\Users\Jim\PyCharmProjects\ChessCPPAttemptBStrap\testFolder\

print(os.environ["CC"])

extensions = [
    Extension("testPYX", ["testFolder/testPYX.pyx"], extra_compile_args=["-std=c++20"], language="c++", extra_link_args=[])
]


#setup(ext_modules=cythonize(extensions))

setup(
    name="testPYX",
    ext_modules=cythonize(extensions),
    zip_safe=False,
    include_dirs=["InPycharmProjects"]
)



