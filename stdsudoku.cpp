#include <iostream>
#include <fstream>

#include "stdsudoku.h"

using namespace std;

void error_place(ostream &os, char *buffer, char *current_position) {
	os << buffer << endl;
	for (int i = 0; i < (current_position - buffer); i++)
		os << " ";
	os << "^" << endl;
}


bool sudokuboard::read_sudoku(char *filename) {

		ifstream infile;
	
	infile.open(filename, ifstream::in);
	
	if (infile.good()) {
		char buffer[512];
		bool firstline = true, enough = false;
		int intcol = 0, introw = 0;

		do {
			infile.getline(buffer, 512);
			if ((infile.good() || infile.eof()) && !enough) {
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
					//std::cout << *pom << endl;
					if (*pom != 'A' && *pom != 'N') {
						error_place(cerr, buffer, pom);
						cerr << "Unknown element type." << endl << "  Expected 'A' for ascii (A - Z) or 'N' for numeric '1-9'." << endl;
						infile.close();
						return false;
					}
					else {
						if (*pom == 'A')
							element_type = ELEM_ALPHABET;
						else
							element_type = ELEM_NUMERIC;
					}
					pom++;
					
					//skip_whitespaces
					while (*pom && (*pom == ' ' || *pom == '\t'))
						pom++;
				
					if (*pom != 'D' && *pom != 'S') {
						error_place(cerr, buffer, pom);
						cerr << "Unknown sudoku type." << endl << " Expected 'D' for diagonal sudoku or 'S' for standard sudoku." << endl;
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
									error_place(cerr, buffer, pom);
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
									error_place(cerr, buffer, pom);
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
		} while(infile.good());
	}
	else {
		cerr << "Error opening file \"" << filename << "\"." << endl; 	
		infile.close();
		return false;
	}	

	infile.close();
	return true;
}

void sudokuboard::solve_recursive(int level) {

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
					solve_recursive(level+1);
					field[col][row] = 0;
				}
		}
		else
			solve_recursive(level+1);

	}
}

void sudokuboard::display_sudoku() {

	switch (element_type) {
		case ELEM_NUMERIC:
			for (int row = 0; row < rowsize*colsize; row++) {
				for (int col = 0; col < rowsize*colsize; col++)
					if (field[col][row])
						cout << field[col][row];
					else
							cout << '.';
				cout << " ";
				cout << endl;
			}
			break;

		case ELEM_ALPHABET:
			for (int row = 0; row < rowsize*colsize; row++) {
				for (int col = 0; col < rowsize*colsize; col++)
					cout << (('A' + field[col][row] - 1) == 64 ? '.':char('A' + field[col][row] - 1)) << " ";
				cout << endl;
			}

			break;

		default: 
			cerr << "Unknown element content type." << endl;
			break;

	};

}


bool sudokuboard::can_be_filled(int col, int row, int element) {

	int rc = rowsize*colsize;
	for (int introw = 0; introw < rc; introw++)
		if (field[col][introw] == element)
			return false;

	for (int intcol = 0; intcol < rc; intcol++)
		if (field[intcol][row] == element)
			return false;

	int regcol = (col / colsize) * colsize;
	int regrow = (row / rowsize) * rowsize;

	for (int introw = 0; introw < rowsize; introw++)
	for (int intcol = 0; intcol < colsize; intcol++) {
		if (field[regcol+intcol][regrow+introw] == element)
			return false;
	}

	if (sudoku_type == TYPE_DIAGONAL) {
		if (col == row) {
			for (int idx = 0; idx < rc; idx++)
				if (field[idx][idx] == element)
					return false;
		}

		if (col == rc - 1 - row) {
			for (int idx = 0; idx < rc; idx++)
				if (field[idx][rc - 1 - idx] == element)
					return false;
		
		}
	}

	return true;
}


void sudokuboard::debug_dump() {
	cout << "C: " << colsize << ", R: " << rowsize << endl;
	cout << "Elem_type:" << (element_type==ELEM_NUMERIC?'N':'A') << endl;
	cout << "Sudoku_type:" << (sudoku_type==TYPE_STANDARD?'S':'D') << endl;
}



#if 0
int main() {

	sudokuboard sdk;

	if (sdk.read_sudoku("c:\\Users\\Marek\\Documents\\20130126-12x12.txt")) {
		sdk.debug_dump();
		sdk.display_sudoku();
		//sdk.solve_recursive(0);
	}

	return 0;
}
#endif

#if 0
int main(int argc, char **argv) {

	if (argc < 3) {
		cout << "Usage: " << argv[0] << " type filename" << endl;
		cout << "\ttype - REG (region), STD (standard) sudoku" << endl;
		return 0;
	}

	if (!strncmp(argv[1], "REG",3)) {
		regionsudokuboard rsdk;

		if (rsdk.read_sudoku(argv[2])) {
			rsdk.gen_regions();
		//	rsdk.print_regions();
		//	rsdk.print_regionmaps();
		//	rsdk.display_sudoku();
			rsdk.solve_recursive(0);
		}
		
	}
	else 
	if (!strncmp(argv[1], "STD", 3)) {
		sudokuboard sdk;

		if (sdk.read_sudoku(argv[2])) {
			sdk.solve_recursive(0);
		}


	}
	else {
		cout << "Error unknown type." << endl;
		return 0;
	}
		



	/*gen_regions();
	print_regions();*/

	//sudokuboard sdk;

/*
	if (sdk.read_sudoku("mn_1.dat")) {
		sdk.solve_recursive(0);
	}

	if (sdk.read_sudoku("mn_2.dat")) {
		sdk.solve_recursive(0);
	}
*/

/*	if (sdk.read_sudoku("mn_4.dat")) {
		sdk.debug_dump();
		sdk.solve_recursive(0);
	}
*/

	//human_solve();
//	solve_recursive(0);
/*
	read_sudoku("mn_2.dat");
	solve_recursive(0);
	display_sudoku('A');
	return 0;
*/

}
#endif
