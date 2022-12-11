#include <iostream>
#include <fstream>

#include "regsudoku.h"

using namespace std;

// 8x8
int local8_regionmap[MAXROWSIZE*MAXCOLSIZE][MAXROWSIZE*MAXCOLSIZE] =
{
	{1,1,1,1,2,2,2,2},
	{1,1,1,1,2,2,2,2},
	{3,3,4,4,4,4,5,5},
	{3,3,4,4,4,4,5,5},
	{3,3,6,6,6,6,5,5},
	{3,3,6,6,6,6,5,5},
	{7,7,7,7,8,8,8,8},
	{7,7,7,7,8,8,8,8}
};

// 9x9
int local9_regionmap[MAXROWSIZE*MAXCOLSIZE][MAXROWSIZE*MAXCOLSIZE] =
{
	{1,1,1,2,2,2,3,3,3},
	{1,1,1,1,2,3,3,3,3},
	{1,4,1,2,2,2,3,6,3},
	{4,4,4,2,5,2,6,6,6},
	{4,5,5,5,5,5,5,5,6},
	{4,4,4,8,5,8,6,6,6},
	{7,4,7,8,8,8,9,6,9},
	{7,7,7,7,8,9,9,9,9},
	{7,7,7,8,8,8,9,9,9}

};

// 9x9 2015
int local9_15_regionmap[MAXROWSIZE * MAXCOLSIZE][MAXROWSIZE * MAXCOLSIZE] =
{
	{1,1,1,1,2,2,2,2,2},
	{3,3,3,1,1,2,2,2,2},
	{3,3,3,4,1,1,5,5,5},
	{6,3,3,4,4,1,5,5,5},
	{6,6,3,4,4,4,7,5,5},
	{6,6,6,8,4,4,7,7,5},
	{6,6,6,8,8,4,7,7,7},
	{9,9,9,9,8,8,7,7,7},
	{9,9,9,9,9,8,8,8,8}
};

// 9x9 2017
int local9_17_regionmap[MAXROWSIZE * MAXCOLSIZE][MAXROWSIZE * MAXCOLSIZE] =
{
	{1,1,1,1,1,2,2,2,2},
	{1,1,3,3,3,4,4,2,2},
	{1,3,3,3,3,4,4,4,2},
	{1,3,3,5,5,5,4,4,2},
	{6,7,7,5,5,5,4,4,2},
	{6,7,7,5,5,5,8,8,9},
	{6,7,7,7,8,8,8,8,9},
	{6,6,7,7,8,8,8,9,9},
	{6,6,6,6,9,9,9,9,9}
};

void regionsudokuboard::solve_recursive(int level) {

//	cout << "Level: " << level << endl;

	if (level == rowsize*colsize*rowsize*colsize) {
		// print solution
		std::cout << "Solution:\n";
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

	if (sudoku_type == TYPE_DIAGONAL)
	{
		// assumes rowsize == colsize

		// main diagonal
		if (col == row) 
		{
			for (int d = 0; d < rc; d++)
			if (field[d][d] == element)
				return false;	
		}

		// other diagonal
		if (col == rc - 1 - row)
		{
			for (int d = 0; d < rc; d++)
			if (field[rc - 1 - d][d] == element)
				return false;
		}
	}

	if (has_region)
		return test_region(col, row, element);

	return true;
} 

void regionsudokuboard::print_regionmap()
{
	for (int c = 0; c < rowsize * colsize; c++)
	{ 
		for (int r = 0; r < rowsize * colsize; r++)
			std::cout << regionmap[r][c];
		std::cout << '\n';
	}

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
void regionsudokuboard::set_region_map(int rows, int cols, int(&region_map)[MAXROWSIZE*MAXCOLSIZE][MAXROWSIZE*MAXCOLSIZE])
{
	//switched r and c meaning!
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			regionmap[c][r] = region_map[r][c];
}
bool regionsudokuboard::read_sudoku(char *filename) {

	ifstream infile;
	
	infile.open(filename, ifstream::in);
	
	if (infile.good()) {
		char buffer[512];
		bool firstline = true, enough = false, map_enough = false;
		bool region_read = false;
		int number_of_digits = 1;
		int intcol = 0, introw = 0;
		has_region = true;

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
						col = 10 * col + (*pom - '0');
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
					while (*pom >= '0' && *pom <= '9') {
						row = 10 * row + (*pom - '0');
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
						cerr << "Unknown element type.\nExpecting A for letter or N for numbers." << endl;
						infile.close();
						return false;
					}
					else {
						if (*pom == 'A')
						{
							element_type = ELEM_ALPHABET;
						}
						else {
							element_type = ELEM_NUMERIC;
							if (rowsize * colsize >= 10)
								number_of_digits = 2;
						}
					}
					pom++;

					//skip_whitespaces
					while (*pom && (*pom == ' ' || *pom == '\t'))
						pom++;

					if (*pom != 'D' && *pom != 'S') {
						cerr << "Unknown sudoku type.\nExpecting S for standard or D for diagonal sudoku." << endl;
						infile.close();
						return false;
					}
					else {
						if (*pom == 'D')
							sudoku_type = TYPE_DIAGONAL;
						else
							sudoku_type = TYPE_STANDARD;
					}
					pom++;
					//skip_whitespaces
					while (*pom && (*pom == ' ' || *pom == '\t'))
						pom++;

					if (*pom == 'T')
					{
						pom++;
						switch (*pom)
						{
						case 'R':
							region_read = true;
							break;
						case '8':
							region_read = false;
							set_region_map(8, 8, local8_regionmap);
							break;
						case '9':
							pom++;
							region_read = false;
							if (!*pom)
								set_region_map(9, 9, local9_regionmap);
							else {
								if (!strncmp(pom, "-15", 3))
								{
									set_region_map(9, 9, local9_15_regionmap);
									pom += 3;
								}
								else
								{
									if (!strncmp(pom, "-17", 3))
									{
										set_region_map(9, 9, local9_17_regionmap);
										pom += 3;
									}
								}
							}
							break;
						case 'N':
							region_read = false;
							has_region = false;
							break;
						default:
							cerr << "Unknown sudoku region type.\nExpecting T for type selection followed by:\n\
\tR: for reading from file (default)\n\
\t8: for standard Pravda 8x8 sudoku\n\
\t9: for standard Pravda 9x9 sudoku.\n\
\t9-15 for standard Pravda 9x9 sudoku in year 2015\n\
\t9-17 for standard Pravda 9x9 sudoku in year 2017\n\
\tN: for no regions (just rows, cols and optionally diagonals with D type)" << endl;
							infile.close();
							return false;
						};
					}
					else
					{
						//std::cout << "'" << (int)*pom << "'";
						if (!*pom)
						{
							region_read = true;

						}
						else
						{
							cerr << "Unknown sudoku region type.\nExpecting T for type selection followed by:\n\
\tR: for reading from file (default)\n\
\t8: for standard Pravda 8x8 sudoku\n\
\t9: for standard Pravda 9x9 sudoku." << endl;
							infile.close();
							return false;
						}
					}

					firstline = false;
				}
				else {

					if (element_type == ELEM_NUMERIC) {
						while (*pom && intcol < rowsize*colsize) {
							//cout << *pom << endl;
							if (*pom >= '1' && *pom <= '9') {
								if (number_of_digits == 1)
									field[intcol++][introw] = (*pom - '0');
								else
								{
									int val = 0;
									while (*pom >= '1' && *pom <= '9')
										val = 10 * val + (*pom - '0');
									if (val< 1 || val > rowsize * colsize)
									{
										cerr << "Use delimiters for boards with 10 or more rows / columns.\n";
										cerr << buffer << '\n';
										for (int ll = 0; ll < (pom - buffer) - 1; ll++)
											cerr << ' ';
										cerr << '^' << '\n';

										infile.close();
										return false;
									}
								}
							}
							else {
								if (*pom == '.')
									field[intcol++][introw] = 0;
								else {
									if (*pom == ' ' || *pom == '\t' || *pom == ',')
									{
										// skip ws and delimiters
									}
									else {
										cerr << "Unknown character '" << *pom << "'." << endl;
										cerr << buffer << '\n';
										for (int ll = 0; ll < (pom - buffer) - 1; ll++)
											cerr << ' ';
										cerr << '^' << '\n';

										infile.close();
										return false;

									}
								}
							}
							pom++;
						}
						intcol = 0;
						introw++;
						if (introw == rowsize * colsize)
							enough = true;

					}
					else {
						while (*pom) {
							//cout << *pom << endl;
							if (*pom >= 'A' && *pom <= 'Z') {
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
						if (introw == rowsize * colsize)
							enough = true;
					}

				}
			}

		} while (infile.good() && !enough);

		if (region_read)
		{

			//skip - empty line
			infile.getline(buffer, 512);

			// Read region_map
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
						while (*pom >= '0' && *pom <= '9') {
							val = 10 * val + (*pom - '0');
							pom++;
						}
						if (val > 0) {
							//cout << "C:" << intcol << " R:" << introw << " V:" << val << endl;	
							regionmap[intcol][introw] = val;
							intcol++;


						}
						if (intcol == rowsize * colsize)
							break;

						//skipws
						while (*pom && (*pom == ' ' || *pom == '\t')) pom++;
						//skipdelimiter ','
						if (*pom != ',') {
							cout << "'" << *pom << "'" << endl;
							cerr << "Missing , ." << endl;
							infile.close();
							return false;
						}
						else pom++;
						//skipws
						while (*pom && (*pom == ' ' || *pom == '\t')) pom++;

					}
					introw++;
					intcol = 0;
					if (introw == rowsize * colsize)
						map_enough = true;

				}

			} while (infile.good() && !map_enough);
		}
	}
	else {
		cerr << "Error opening file \"" << filename << "\"." << endl; 	
		infile.close();
		return false;
	}	

	infile.close();
	return true;
}
