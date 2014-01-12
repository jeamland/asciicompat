from distutils.core import setup, Extension

_asciicompat = Extension('asciicompat._asciicompat',
                         sources=['src/_asciicompat.c'])

setup(name='asciicompat',
      version='1.0',
      description='The missing type',
      author='Benno Rice',
      author_email='benno@jeamland.net',
      url='https://github.com/jeamland/asciicompat',
      packages=['asciicompat'],
      ext_modules=[_asciicompat],
      test_suite="tests")
