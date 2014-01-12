import sys

if sys.version_info[0] == 3:
    from asciicompat._asciicompat import asciistr
else:
    asciistr = str
