#ifndef SUDOKUV2_BOARD_HPP
#define SUDOKUV2_BOARD_HPP

#include "../Structures/Column.cpp"
#include "../Structures/Field.cpp"
#include "../Structures/Row.cpp"
#include "../Structures/Square.cpp"
#include "../Structures/Domain.cpp"
#include "fstream"
#include "string"

#pragma once

#define N 9

class Board
{
    std::vector< std::vector<uint16_t> > board;
    std::vector< std::vector<Field *> > fields;
    std::vector< std::vector<Domain *> > domains;
    std::vector<Square *> squares;
    std::vector<Column *> columns;
    std::vector<Row *> rows;

public:
    Board();
    ~Board() = default;
    void setBoard(const std::vector< std::vector<Domain *> >& b);
    static Board *copyBoard(Board *b);
    void uploadBoard(const std::string &path);
    void prepareToSolve();
    bool fullBoard();
    bool cantMakeMove();
    void solveSudoku(Board *b);
    void printSudokuBoard();

    __attribute__((unused)) void printPossibilities();
    void createFields();
    void createRows();
    void createColumns();
    void createSquares();
    void createDomains();
    void generatePossibilities();
};


#endif
