all: sudoku

sudoku: stdsudoku.o regsudoku.o samsudoku.o
	g++ -Wall --pedantic --ansi -O3 -o sudoku sudoku.cpp stdsudoku.o regsudoku.o samsudoku.o	

stdsudoku.o: stdsudoku.cpp stdsudoku.h
	g++ -Wall --pedantic --ansi -O3 -c stdsudoku.cpp

regsudoku.o: regsudoku.cpp regsudoku.h
	g++ -Wall --pedantic --ansi -O3 -c regsudoku.cpp

samsudoku.o: samsudoku.cpp samsudoku.h
	g++ -Wall --pedantic --ansi -O3 -c samsudoku.cpp
clean:
	@rm -f stdsudoku.o regsudoku.o samsudoku.o sudoku
.PHONY: clean
