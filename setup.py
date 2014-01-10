from distutils.core import setup, Extension

asciicompat = Extension('asciicompat', sources=['asciicompat.c'])

setup (name='asciicompat',
       version='1.0',
       description='The missing type',
       ext_modules=[asciicompat],
       test_suite="tests")
