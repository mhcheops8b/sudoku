#ifndef _STDSUDOKU_H_
#define _STDSUDOKU_H_

#define MAXROWSIZE 5
#define MAXCOLSIZE 5

struct sudokuboard {
	int rowsize;
	int colsize;

	int field[MAXROWSIZE*MAXCOLSIZE][MAXROWSIZE*MAXCOLSIZE];

	int sudoku_type;
	int element_type;

	bool read_sudoku(char *filename);
	void solve_recursive(int level); 
	void display_sudoku(); 
	bool can_be_filled(int col, int row, int element); 
	void debug_dump();

	static const int TYPE_STANDARD = 1;
	static const int TYPE_DIAGONAL = 2;

	static const int ELEM_NUMERIC  = 1;
	static const int ELEM_ALPHABET = 2;
};


#endif
