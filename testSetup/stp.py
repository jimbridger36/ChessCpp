from setuptools import setup, Extension
from Cython.Build import cythonize

cl = "CppLib/"
'''
extensions = [Extension(
    "testpyx1", ["testpyx1.pyx"],
    include_dirs=["CppLib"]


)


]
'''

setup(
    ext_modules = cythonize("testpyx1.pyx"),
    zip_safe = False
)



