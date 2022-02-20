#include <iostream>
#include <string.h>

#include "regsudoku.h"
#include "samsudoku.h"

int main(int argc, char **argv) {

	if (argc < 3 || argc > 3) {		
		if (argc < 1 || !argv)
			cout << "Usage: " << "<executable_name>";
		else
			cout << "Usage: " << argv[0];

		cout << " <type> <filename>" << endl;
		cout << "\t<type> - REG (region), STD (standard), SAM (samuraj) sudoku" << endl;
		cout << "\t<filename> - the file that is being read as input" << endl;
		
		if (argc > 3)
		{
			cout << "More than two arguments have been provided.\n";
		}
		
		return 0;
	}

	

	//cout << "argv[1] = " << argv[1] << endl;

	if (!strncmp(argv[1], "REG",3)) {
		regionsudokuboard rsdk;

		if (rsdk.read_sudoku(argv[2])) {
			rsdk.display_sudoku();
			cout << endl;
			rsdk.print_regionmap();
			cout << endl;
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
