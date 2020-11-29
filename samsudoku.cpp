
#include "samsudoku.h"


const int expected_sizes[21] = { 18, 18, 18, 18, 18, 18, 21, 
								 21, 21,  9,  9,  9, 21, 21, 
								 21, 18, 18, 18, 18, 18, 18 };

inline int samsudoku::getfield(int col, int row) {
	return field[row][col];
}

inline void samsudoku::setfield(int col, int row, int element) {
	field[row][col] = element;
}

void samsudoku::init_field() {
	for (int col = 0; col < 21; col++)
	for (int row = 0; row < 21; row++)
		setfield(col, row, 0);
}

void samsudoku::display_sudoku() {
	for (int row = 0; row < 21; row++) {
	
		for (int col = 0; col < 21; col++) {
			int elem = getfield(col, row);

			if (elem)
				cout << char(elem+'0') << " ";
			else
				cout << '.' << " ";
		}
		cout << endl;
	}
			
}

bool samsudoku::read_sudoku(char *filename) {
	ifstream infile;
	infile.open(filename, ifstream::in);
	char buffer[512];

	if (!infile.good()) {
		cerr << "Error opening file \"" << filename << "\"." << endl;
		infile.close();
		return false;
	}

	int intcol = 0, introw = 0;

	do {
		infile.getline(buffer, 512);
		if (infile.good()) {
			char *pom = buffer;

			while (*pom && introw < 21 && intcol < expected_sizes[introw]) {
				while (*pom && (*pom == ' ' || *pom == '\t')) pom++;
				//skipws
				int value = 0;
				if ((*pom >= '1' && *pom <= '9') || *pom == '.') {
					
					if (*pom == '.')
						value = 0;
					else
						value = *pom - '0';
					switch (expected_sizes[introw])
					{
					case 18:
						if (intcol >= 9)
							setfield(intcol + 3, introw, value);
						else
							setfield(intcol, introw, value);
						break;
					case 9:
						setfield(intcol + 6, introw, value);
						break;
					default:
						setfield(intcol, introw, value);
					};

					intcol++;
					pom++;
				}
				else {
					cerr << "Unknown character '" << *pom << "'." << endl;
					return false;
				}
			}
			if (intcol != expected_sizes[introw]) {
				cerr << "Insufficient number digits on the line." << endl;
				cerr << buffer << endl;
				return false;
			}

			intcol = 0;
			introw++;
		}

	} while (infile.good() && introw < 21);

	if (introw != 21) {
		cerr << "Not enough rows." << endl;
		return false;
	}
	return true;
}

bool samsudoku::read_sudoku_old(char *filename) {

	ifstream infile;
	infile.open(filename, ifstream::in);
	char buffer[512];

	if (!infile.good()) {
		cerr << "Error opening file \"" << filename << "\"." << endl; 	
		infile.close();
		return false;
	}

	if (	!read_3x3board(infile,0,0)  ||
		infile.getline(buffer,512),!read_3x3board(infile,12,0) ||
		infile.getline(buffer,512),!read_3x3boardReduced(infile,6,6) ||
		infile.getline(buffer,512),!read_3x3board(infile,0,12) ||
		infile.getline(buffer,512),!read_3x3board(infile,12,12))
	{
		infile.close();
		return false;
	}
	
	infile.close();
	return true;
}


bool samsudoku::read_3x3board(ifstream& ifs, int fromcol, int fromrow) {
	char buffer[512];
	int intcol = 0, introw = 0;

	do {	
		ifs.getline(buffer, 512);
		if (ifs.good()) {
			char *pom = buffer;

			while (*pom && intcol < 9) {
				while (*pom && (*pom == ' ' || *pom == '\t')) pom++;
				//skipws
				if ((*pom>='1' && *pom<='9') || *pom=='.') {
					if (*pom=='.')
						setfield(fromcol+intcol, fromrow+introw, 0);
					else
						setfield(fromcol+intcol, fromrow+introw, *pom - '0');
					intcol++;	
					pom++;
				}
				else {
					cerr << "Unknown character '" << *pom << "'." << endl;
					return false;
				}
			}
			if (intcol != 9) {
				cerr << "Not enough digits on the line." << endl;
				cerr << buffer << endl;
				return false;
			}
		
			intcol = 0;
			introw++;
		}

	} while (ifs.good() && introw < 9);

	if (introw != 9) {
		cerr << "Not enough rows." << endl;
		return false;
		
	}
	return true;
}

bool samsudoku::read_3x3boardReduced(ifstream& ifs, int fromcol, int fromrow) {
	char buffer[512];
	int intcol = 0, introw = 0;

	do {	
		ifs.getline(buffer, 512);
		if (ifs.good()) {
			char *pom = buffer;

			while (*pom && intcol < 3) {
				while (*pom && (*pom == ' ' || *pom == '\t')) pom++;
				//skipws
				if ((*pom>='1' && *pom<='9') || *pom=='.') {
					if (*pom=='.')
						setfield(fromcol+intcol+3, fromrow+introw, 0);
					else
						setfield(fromcol+intcol+3, fromrow+introw, *pom - '0');
					intcol++;	
					pom++;
				}
				else {
					cerr << "Unknown character '" << *pom << "'." << endl;
					return false;
				}
			}
			if (intcol != 3) {
				cerr << "Not enough digits on the line." << endl;
				cerr << buffer << endl;
				return false;
			}
		
			intcol = 0;
			introw++;
		}

	} while (ifs.good() && introw < 3);

	if (introw != 3) {
		cerr << "3Not enough rows." << endl;
		return false;
		
	}


	do {	
		ifs.getline(buffer, 512);
		if (ifs.good()) {
			char *pom = buffer;

			while (*pom && intcol < 9) {
				while (*pom && (*pom == ' ' || *pom == '\t')) pom++;
				//skipws
				if ((*pom>='1' && *pom<='9') || *pom=='.') {
					if (*pom=='.')
						setfield(fromcol+intcol, fromrow+introw, 0);
					else
						setfield(fromcol+intcol, fromrow+introw, *pom - '0');
					intcol++;	
					pom++;
				}
				else {
					cerr << "Unknown character '" << *pom << "'." << endl;
					return false;
				}
			}
			if (intcol != 9) {
				cerr << "Not enough digits on the line." << endl;
				cerr << buffer << endl;
				return false;
			}
		
			intcol = 0;
			introw++;
		}

	} while (ifs.good() && introw < 6);

	if (introw != 6) {
		cerr << "6Not enough rows." << endl;
		return false;
		
	}

	do {	
		ifs.getline(buffer, 512);
		if (ifs.good()) {
			char *pom = buffer;

			while (*pom && intcol < 3) {
				while (*pom && (*pom == ' ' || *pom == '\t')) pom++;
				//skipws
				if ((*pom>='1' && *pom<='9') || *pom=='.') {
					if (*pom=='.')
						setfield(fromcol+intcol+3, fromrow+introw, 0);
					else
						setfield(fromcol+intcol+3, fromrow+introw, *pom - '0');
					intcol++;	
					pom++;
				}
				else {
					cerr << "Unknown character '" << *pom << "'." << endl;
					return false;
				}
			}
			if (intcol != 3) {
				cerr << "Not enough digits on the line." << endl;
				cerr << buffer << endl;
				return false;
			}
		
			intcol = 0;
			introw++;
		}

	} while (ifs.good() && introw < 9);

	if (introw != 9) {
		cerr << "9Not enough rows." << endl;
		return false;
		
	}
	return true;
}


bool samsudoku::can_be_filled_middle(int col, int row, int element) {

	for (int icol = 0; icol < 9; icol++)
		if (getfield(6 + icol, row) == element)
			return false;


	for (int irow = 0; irow < 9; irow++)
		if (getfield(col, 6 + irow) == element)
			return false;


	int intcol = col - 6;
	int introw = row - 6;

	int regcol = (intcol / 3) * 3;
	int regrow = (introw / 3) * 3;

	for (int icol = 0; icol < 3; icol++)
	for (int irow = 0; irow < 3; irow++)
		if (getfield(6+regcol+icol, 6+regrow+irow) == element)
			return false;




	if (col < 9 && row < 9) {
	
		for (int icol = 0; icol < 9; icol++)
			if (getfield(icol, row) == element)
				return false;
	
		for (int irow = 0; irow < 9; irow++)
			if (getfield(col, irow) == element)
				return false;
	
	}

	if (col < 9 && row > 11) {
	
		for (int icol = 0; icol < 9; icol++)
			if (getfield(icol, row) == element)
				return false;
	
		for (int irow = 0; irow < 9; irow++)
			if (getfield(col, 12 + irow) == element)
				return false;
	
	}


	if (col > 11 && row < 9) {
	
		for (int icol = 0; icol < 9; icol++)
			if (getfield(12 + icol, row) == element)
				return false;
	
		for (int irow = 0; irow < 9; irow++)
			if (getfield(col, irow) == element)
				return false;
	
	}

	if (col > 11 && row > 11) {
	
		for (int icol = 0; icol < 9; icol++)
			if (getfield(12 + icol, row) == element)
				return false;
	
		for (int irow = 0; irow < 9; irow++)
			if (getfield(col, 12 + irow) == element)
				return false;
	
	}

	return true;
}

void samsudoku::solve_middle_recursive(int level) {
	int introw, intcol;

//	cout << level << endl;
	if (level == 81) {
		solve_upperleft_recursive(0);
	}

	else {
		intcol = level % 9;
		introw = level / 9;

		if (!getfield(6+intcol, 6+introw))  {
			for (int element = 1; element <= 9; element++) 
				if (can_be_filled_middle(6 + intcol, 6 + introw, element)) {
					setfield(6+intcol, 6+introw, element);
					solve_middle_recursive(level+1);
					setfield(6+intcol, 6+introw, 0);
				}
		}
		else
			solve_middle_recursive(level+1);
	}
}


bool samsudoku::can_be_filled(int offset_col, int offset_row, int col, int row, int element) {
	
	for (int icol = 0; icol < 9; icol++)
		if (getfield(icol+offset_col, row) == element) 
			return false;

	for (int irow = 0; irow < 9; irow++)
		if (getfield(col, irow + offset_row) == element)
			return false;

	int intcol = col - offset_col;
	int introw = row - offset_row;

	int regcol = (intcol / 3) * 3;
	int regrow = (introw / 3) * 3;

	for (int icol = 0; icol < 3; icol++)
	for (int irow = 0; irow < 3; irow++)
		if (getfield(offset_col+regcol+icol, offset_row+regrow+irow) == element)
			return false;
	
	return true;
}

void samsudoku::solve_upperleft_recursive(int level) {
	int introw, intcol;

	//cout << level << endl;
	if (level == 81) {
		solve_upperright_recursive(0);
	}
	else {
		intcol = level % 9;
		introw = level / 9;

		if (!getfield(intcol, introw))  {
			for (int element = 1; element <= 9; element++) 
				if (can_be_filled(0, 0, intcol, introw, element)) {
					setfield(intcol, introw, element);
					solve_upperleft_recursive(level+1);
					setfield(intcol, introw, 0);
				}
		}
		else
			solve_upperleft_recursive(level+1);
	}
}

void samsudoku::solve_upperright_recursive(int level) {
	int introw, intcol;

	//cout << level << endl;
	if (level == 81) {
		solve_lowerleft_recursive(0);
	}
	else {
		intcol = level % 9;
		introw = level / 9;

		if (!getfield(12+intcol, introw))  {
			for (int element = 1; element <= 9; element++) 
				if (can_be_filled(12, 0, 12+intcol, introw, element)) {
					setfield(12+intcol, introw, element);
					solve_upperright_recursive(level+1);
					setfield(12+intcol, introw, 0);
				}
		}
		else
			solve_upperright_recursive(level+1);
	}
}

void samsudoku::solve_lowerleft_recursive(int level) {
	int introw, intcol;

	//cout << level << endl;
	if (level == 81) {
		solve_lowerright_recursive(0);
		
	}
	else {
		intcol = level % 9;
		introw = level / 9;

		if (!getfield(intcol, 12 + introw))  {
			for (int element = 1; element <= 9; element++) 
				if (can_be_filled(0, 12, intcol, 12 + introw, element)) {
					setfield(intcol, 12 + introw, element);
					solve_lowerleft_recursive(level+1);
					setfield(intcol, 12 + introw, 0);
				}
		}
		else
			solve_lowerleft_recursive(level+1);
	}
}

void samsudoku::solve_lowerright_recursive(int level) {
	int introw, intcol;

	//cout << level << endl;
	if (level == 81) {
		display_sudoku();
	}
	else {
		intcol = level % 9;
		introw = level / 9;

		if (!getfield(12 + intcol, 12 + introw))  {
			for (int element = 1; element <= 9; element++) 
				if (can_be_filled(12, 12, 12 + intcol, 12 + introw, element)) {
					setfield(12 + intcol, 12 + introw, element);
					solve_lowerright_recursive(level+1);
					setfield(12 + intcol, 12 + introw, 0);
				}
		}
		else
			solve_lowerright_recursive(level+1);
	}
}


/*
int main() {
	samsudoku sam;

	sam.init_field();
	sam.read_sudoku("ssud_01.dat");
	sam.display_sudoku();
	cout << endl;
	sam.solve_middle_recursive(0);
	
	return 0;
}
*/
