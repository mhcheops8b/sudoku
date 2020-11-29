#include <iostream>
#include <fstream>

#include "regsudoku.h"

using namespace std;

void regionsudokuboard::solve_recursive(int level) {

//	cout << "Level: " << level << endl;

	if (level == rowsize*colsize*rowsize*colsize) {
		// print solution
		display_sudoku();
		cout << "----" << endl;
	}
	else {
		int col = level / (rowsize * colsize);
		int row = level % (rowsize * colsize);

		if (field[col][row] == 0) {
			for (int elem = 1; elem <= rowsize*colsize; elem++)
				if (can_be_filled(col, row, elem)) {
					field[col][row] = elem;
					//display_sudoku();
					solve_recursive(level+1);
					field[col][row] = 0;
				}
		}
		else
			solve_recursive(level+1);

	}
}

	void regionsudokuboard::print_regionmaps() {
		for (int introw = 0; introw < rowsize*colsize; introw++) {
			for (int intcol = 0; intcol < rowsize*colsize; intcol++)
				cout << regionmap[intcol][introw] << " ";
			cout << endl;
		}
	}

bool regionsudokuboard::can_be_filled(int col, int row, int element) {

	int rc = rowsize*colsize;
	for (int introw = 0; introw < rc; introw++)
		if (field[col][introw] == element)
			return false;

	for (int intcol = 0; intcol < rc; intcol++)
		if (field[intcol][row] == element)
			return false;

	return test_region(col, row, element);	
} 



void regionsudokuboard::gen_regions() {
	int indices[MAXROWSIZE*MAXCOLSIZE];

	for (int idx = 0; idx < rowsize*colsize; idx++)
		indices[idx] = 0;

	for (int col = 0; col < rowsize*colsize; col++)
	for (int row = 0; row < rowsize*colsize; row++) {
		
		int regidx = regionmap[col][row]-1;
		int elemidx = indices[regionmap[col][row]-1];
		
		region[regidx][elemidx][0] = row;
		region[regidx][elemidx][1] = col;

		indices[regidx]++;

	}
}

bool regionsudokuboard::test_region(int col, int row, int element) {
		


	int regidx = regionmap[col][row] - 1;

//	cout << col << " " << row << " " << regidx << endl;
	
//	cout << "DEBUG: " << endl;
	

	for (int elem_idx = 0; elem_idx < rowsize*colsize; elem_idx++) {
//		cout << "Region: " << regidx+1 << endl;
//		cout << "C: " << region[regidx][elem_idx][1] << " R: " << region[regidx][elem_idx][0] << endl;
		if (field[region[regidx][elem_idx][1]][region[regidx][elem_idx][0]] == element) 
			return false;
	}

	return true;
}


void regionsudokuboard::print_regions() {
	for (int reg = 0; reg < rowsize*colsize; reg++) {
		cout << "Region " << reg + 1 << ":" << endl;
		for (int elem = 0; elem < rowsize*colsize; elem++) {
			cout << "[" << region[reg][elem][0] << ", " << region[reg][elem][1] << "], " ;	

		}	
		cout << endl;


	}
}

bool regionsudokuboard::read_sudoku(char *filename) {

	ifstream infile;
	
	infile.open(filename, ifstream::in);
	
	if (infile.good()) {
		char buffer[512];
		bool firstline = true, enough = false, map_enough = false;
		int intcol = 0, introw = 0;

		do {
			infile.getline(buffer, 512);
			if (infile.good() && !enough) {
				char *pom = buffer;
				if (firstline) {
					//cout << "HERE" << endl;

					//skip_whitespaces
					while (*pom && (*pom == ' ' || *pom == '\t'))
						pom++;

					int col = 0;
					while (*pom >= '0' && *pom <= '9') {
						col = 10* col + (*pom - '0');
						pom++;
					}
					colsize = col;


					/*
					if (col != COLSIZE) {
						cerr << "COL doesnot match COLSIZE" << endl;
						infile.close();
						return false;
					}
					*/

					//skip_whitespaces
					while (*pom && (*pom == ' ' || *pom == '\t'))
						pom++;

					int row = 0;
					while (*pom>='0' && *pom<='9') {
						row = 10* row + (*pom - '0');
						pom++;
					}
					rowsize = row;

					/*
					if (row != ROWSIZE) {
						cerr << "ROW doesnot match ROWSIZE" << endl;
						infile.close();
						return false;
					}
					*/

					//skip_whitespaces
					while (*pom && (*pom == ' ' || *pom == '\t'))
						pom++;
					
					if (*pom != 'A' && *pom != 'N') {
						cerr << "Unknown element type." << endl;
						infile.close();
						return false;
					}
					else {
						if (*pom == 'A')
							element_type  = ELEM_ALPHABET;
						else
							element_type = ELEM_NUMERIC;
					}
					pom++;
					
					//skip_whitespaces
					while (*pom && (*pom == ' ' || *pom == '\t'))
						pom++;
				
					if (*pom != 'D' && *pom != 'S') {
						cerr << "Unknown sudoku type." << endl;
						infile.close();
						return false;
					}
					else {
						if (*pom == 'D')
							sudoku_type  = TYPE_DIAGONAL;
						else
							sudoku_type = TYPE_STANDARD;
					}

					firstline = false;
				}
				else {
				
					if (element_type == ELEM_NUMERIC) {	
						while (*pom && intcol < rowsize*colsize) {
							//cout << *pom << endl;
							if (*pom>='1' && *pom<='9') {
								field[intcol++][introw] = (*pom - '0');
}
							else {
								if (*pom == '.')	
									field[intcol++][introw] = 0;
								else {
									cerr << "Unknown character '" << *pom << "'." << endl;
									infile.close();
									return false;

								}
							}
							pom++;
						}
						intcol = 0;						
						introw++;
						if (introw == rowsize*colsize)
							enough = true;

					}	
					else {
						while (*pom) {
							//cout << *pom << endl;
							if (*pom>='A' && *pom<='Z') {
								field[intcol++][introw] = (*pom - 'A' + 1);
}
							else {
								if (*pom == '.')	
									field[intcol++][introw] = 0;
								else {
									cerr << "Unknown character '" << *pom << "'." << endl;
									infile.close();
									return false;
								}
							}
							pom++;
						}
						intcol = 0;						
						introw++;
						if (introw == rowsize*colsize)
							enough = true;
					}

				}
			}

		} while(infile.good() && !enough);

		//skip - empty line
		infile.getline(buffer, 512);

		intcol = 0; 
		introw = 0;
		do {
			
			infile.getline(buffer, 512);
			if (infile.good() && !map_enough) {
				char *pom = buffer;

				//cout << buffer <<endl;
				// skipws
				while (*pom && (*pom == ' ' || *pom == '\t')) pom++;
				
				while (*pom) {	
					int val = 0;
					//readnumber
					while (*pom>='0' && *pom<='9') {
						val = 10 * val + (*pom - '0');
						pom++;
					}
					if (val > 0) {
						cout << "C:" << intcol << " R:" << introw << " V:" << val << endl;	
						regionmap[intcol][introw] = val;
						intcol++;
						
						
					}
					if (intcol == rowsize*colsize)
						break;

					//skipws
					while (*pom && (*pom == ' ' || *pom == '\t')) pom++;
					//skipdelimiter ','
					if (*pom != ',') {
						cout << "'" << *pom << "'"<< endl;
						cerr << "Missing , ." << endl;
						infile.close();
						return false;
					}
					else pom++;
					//skipws
					while (*pom && (*pom == ' ' || *pom == '\t')) pom++;

				}
				introw++;
				intcol=0;
				if (introw == rowsize*colsize)
					map_enough = true;

			}
		
		} while(infile.good() && !map_enough);

	}
	else {
		cerr << "Error opening file \"" << filename << "\"." << endl; 	
		infile.close();
		return false;
	}	

	infile.close();
	return true;
}
