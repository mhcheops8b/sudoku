#include <iostream>
#include <string.h>

#include "regsudoku.h"
#include "samsudoku.h"

int main(int argc, char **argv) {

	if (argc < 3) {
		cout << "Usage: " << argv[0] << " type filename" << endl;
		cout << "\ttype - REG (region), STD (standard), SAM (samuraj) sudoku" << endl;
		return 0;
	}

	//cout << "argv[1] = " << argv[1] << endl;

	if (!strncmp(argv[1], "REG",3)) {
		regionsudokuboard rsdk;

		if (rsdk.read_sudoku(argv[2])) {
			rsdk.gen_regions();
			rsdk.solve_recursive(0);
		}
		
		return 0;
	}

	
	if (!strncmp(argv[1], "STD", 3)) {
	//	cout << "HERE" << endl;
		sudokuboard sdk;

		if (sdk.read_sudoku(argv[2])) {
			sdk.solve_recursive(0);
		}

		return 0;
	}
	
	if (!strncmp(argv[1], "SAM", 3)) {
		samsudoku sam;

		sam.init_field();
		sam.read_sudoku(argv[2]);
		//sam.display_sudoku();
		//cout << endl;
		sam.solve_middle_recursive(0);
		
		return 0;
	}
	
	cout << "Error unknown type." << endl;
	return 1;
}
