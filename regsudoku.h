#ifndef _REGSUDOKU_H_
#define _REGSUDOKU_H_

#include "stdsudoku.h"

#define MAXROWSIZE 5
#define MAXCOLSIZE 5

struct regionsudokuboard:sudokuboard {

	int regionmap[MAXROWSIZE*MAXCOLSIZE][MAXROWSIZE*MAXCOLSIZE];
	int region[MAXROWSIZE*MAXCOLSIZE][MAXROWSIZE*MAXCOLSIZE][2];
	
	void gen_regions();
	bool test_region(int col, int row, int element);
	bool read_sudoku(char *filename);
	bool can_be_filled(int col, int row, int element); 
	void print_regionmaps();
	void print_regions();
	void print_regionmap();
	void set_region_map(int rows, int cols, int(&region_map)[MAXROWSIZE * MAXCOLSIZE][MAXROWSIZE * MAXCOLSIZE]);
	void solve_recursive(int level); 

};

#endif
