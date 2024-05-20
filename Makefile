all:
	gcc src/corrupt.c -o bin/corrupt

create_dirs:
	mkdir bin
	mkdir out