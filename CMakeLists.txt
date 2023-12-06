add_library(regsudoku OBJECT)
target_sources(regsudoku PRIVATE regsudoku.cpp regsudoku.h)

add_library(samsudoku OBJECT)
target_sources(samsudoku PRIVATE samsudoku.cpp samsudoku.h)

add_library(stdsudoku OBJECT)
target_sources(stdsudoku PRIVATE stdsudoku.cpp stdsudoku.h)

add_executable(sudoku sudoku.cpp)
target_link_libraries(sudoku regsudoku samsudoku stdsudoku)

