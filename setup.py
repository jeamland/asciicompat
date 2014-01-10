from distutils.core import setup, Extension

asciistr = Extension('asciistr',
                    sources = ['asciistr.c'])

setup (name='asciistr',
       version='1.0',
       description='The missing type',
       ext_modules=[asciistr],
       test_suite="tests")
