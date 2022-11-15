link ../week1/file.txt _ex2.txt
find ~/ -inum 1051474 > ex2.txt
find ~/ -inum 1051474 -exec rm {} \;
