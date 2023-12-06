# sudoku

Sudoku puzzles solvers.

Usage: `sudoku[.exe]` `<sudoku_type>` `<input_filename>`

`<sudoku_type>`
  - `STD` - standard sudoku
  - `REG` - region sudoku 
  - `SAM` - samurai sudoku

`<input_filename>` - path to input file

Input files syntax:

## Standard sudoku:

`header`

`input_data`

`header` = `m n N|A S|D`

`m`  cols, `n`  rows in a block. 
(Whole sudoku contains (m x n) x (m x n) elements)

`N|S`: `N` - numeric (numbers), `A` - ascii (A-Z characters)

`S|D`: `S` - standard (rows, columns, blocks), `D` - diagonal (standard + diagonals)

 `input_data` - list of digits (characters A-Z), when (m x n) >=10 delimited by spaces. Unfilled space as dot `.`

 ## Region sudoku

`header`

`input_data`

`[region_map]`

`header` = `m n N|A S|D <type>`

`m`  cols, `n`  rows in a block. 
(Whole sudoku contains (m x n) x (m x n) elements.)

`N|A`: `N` - numeric (numbers), `A` - ascii (A-Z characters)

`S|D`: `S` - standard (rows, columns, blocks), `D` - diagonal (standard + diagonals)

`type`:
  - `T8` - 8x8 sudoku with ...
  - `T9`, `T9-15`, `T9-17` - 9x9 sudoku with ...
  - `TR` - use region map

 `input_data` - list of digits (characters A-Z), when (m x n) >=10 delimited by spaces. Unfilled space as dot `.`

 `region_map` - comma separated mapping of elements to regions. Each region has its own number starting from 1.

 ## Samurai sudoku

 `input_data` 

 `input_data` - in the shape of Samurai sudoku (only digits [0-9] are supported).
