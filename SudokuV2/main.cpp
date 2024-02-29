#include "../SudokuV2/SudokuBoard/Board/Board.cpp"

int main()
{
    auto *board = new Board();
    board -> uploadBoard("/Users/michallejza/CLionProjects/SudokuV2/Data/Master/input3.txt");
    board -> prepareToSolve();
    board -> printSudokuBoard();
    board -> solveSudoku(board);
    delete board;
    return 0;
}
