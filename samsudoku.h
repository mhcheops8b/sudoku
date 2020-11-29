#ifndef _SAMSUDOKU_H_
#define _SAMSUDOKU_H_

#include <iostream>
#include <fstream>

using namespace std;

#define MAXROWSIZE 5
#define MAXCOLSIZE 5

struct samsudoku {

	int field[21][21];

	void init_field();
	bool read_sudoku(char *filename);
	bool read_sudoku_old(char *filename);
	bool read_3x3board(ifstream& ifs, int fromcol, int fromrow);
	bool read_3x3boardReduced(ifstream& ifs, int fromcol, int fromrow);
	void solve_recursive(int level); 
	void solve_middle_recursive(int level); 
	void solve_upperleft_recursive(int level);
	void solve_upperright_recursive(int level); 
	void solve_lowerleft_recursive(int level); 
	void solve_lowerright_recursive(int level); 
	void display_sudoku(); 
	bool can_be_filled(int offset_col, int offset_row, int col, int row, int element); 
	bool can_be_filled_middle(int col, int row, int element);
	void debug_dump();

	int getfield(int col, int row);
	void setfield(int col, int row, int element);

};


#endif
