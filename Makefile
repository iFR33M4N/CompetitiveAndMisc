CC=gcc
CFLAGS= -g -Wall

graph: union.c
	$(CC) $(CFLAGS) union.c -o union

string: sortAndMatch.cpp
	g++-4.9 -std=c++14 -g -Wall  sortAndMatch.cpp -o srtNmtch

clean:
	rm union srtNmtch
