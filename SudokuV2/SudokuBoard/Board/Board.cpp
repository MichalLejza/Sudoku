#include "Board.hpp"

Board::Board()
{
    this -> board = std::vector< std::vector<uint16_t> > (N, std::vector<uint16_t>(N));
    this -> fields = std::vector< std::vector<Field *> > (N, std::vector<Field *>(N));
    this -> domains = std::vector< std::vector<Domain *> > (N, std::vector<Domain *>(N));
    this -> squares = std::vector<Square *>(N);
    this -> columns = std::vector<Column *>(N);
    this -> rows = std::vector<Row *>(N);
}

void Board::setBoard(const std::vector< std::vector<Domain *> >& b)
{
    for (uint16_t i = 0; i < N; i++)
        for (uint16_t j = 0; j < N ; j++)
            this -> board.at(i).at(j) = b.at(i).at(j) -> getValue();
}

Board *Board::copyBoard(Board *b)
{
    auto *newBoard = new Board();
    newBoard -> setBoard(b -> domains);
    newBoard -> prepareToSolve();
    return newBoard;
}

void Board::uploadBoard(const std::string &path)
{
    std::ifstream input(path);
    if (!input.is_open())
    {
        std::cerr << "Unable to open file with sudoku." << std::endl;
        exit(1);
    }
    for (uint16_t i = 0; i < N; i++)
    {
        for (uint16_t j = 0; j < N; j++)
        {
            if (!(input >> this -> board.at(i).at(j)))
            {
                std::cerr << "Error reading from the file." << std::endl;
                exit(1);
            }
        }
    }
    input.close();
}

void Board::prepareToSolve()
{
    createFields();
    createSquares();
    createRows();
    createColumns();
    createDomains();
    generatePossibilities();
}

bool Board::fullBoard()
{
    for (const auto& a : fields)
        for (const auto field : a)
            if (field -> getValue() == 0)
                return false;
    return true;
}

bool Board::cantMakeMove()
{
    for (const auto& a : fields)
        for (const auto field : a)
            if (field -> getValue() == 0 && field -> getPossibilities().empty())
                return true;
    return false;
}

void Board::solveSudoku(Board *b)
{
    if (fullBoard())
        return;
    if (cantMakeMove())
        return;

    int stop = 1;
    while (stop == 1)
    {
        stop = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                b -> domains.at(i).at(j) -> makeMove(stop);
    }

    Domain *toChange = nullptr;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (b -> fields.at(i).at(j) -> getValue() == 0)
                toChange = b -> domains.at(i).at(j);

    if (toChange != nullptr)
    {
        if (toChange -> getPossibilities().empty())
            return;
        for (auto a : toChange -> getPossibilities())
        {
            Board *tempB = copyBoard(b);
            tempB -> domains.at(toChange -> X).at(toChange -> Y) -> setValue(a);
            solveSudoku(tempB);
            delete tempB;
        }
    }
    else
    {
        b -> printSudokuBoard();
        return;
    }
}

void Board::printSudokuBoard()
{
    for (uint16_t i = 0; i < N; i++)
    {
        for (uint16_t j = 0; j < N; j++)
        {
            if (fields.at(i).at(j) -> getValue() == 0)
                std::cout << this -> fields.at(i).at(j) -> getValue() << "  ";
            else
                std::cout <<  "\x1B[32m" << this -> fields.at(i).at(j) -> getValue() << "  " << "\x1B[0m";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

__attribute__((unused)) void Board::printPossibilities()
{
    for (uint16_t i = 0; i < N; i++)
        for (uint16_t j = 0; j < N; j++)
            domains.at(i).at(j) -> print();
}

void Board::createFields()
{
    for (uint16_t i = 0; i < N; i++)
        for (uint16_t j = 0; j < N; j++)
            this -> fields.at(i).at(j) = new Field(i, j, board.at(i).at(j));
}

void Board::createRows()
{
    std::vector<Field *> vec = std::vector<Field *>(N);
    for (uint16_t i = 0; i < N; i++)
    {
        for (uint16_t j = 0; j < N; j++)
            vec.at(j) = fields.at(i).at(j);
        rows.at(i) = new Row(vec);
    }
}

void Board::createColumns()
{
    std::vector<Field *> vec = std::vector<Field *>(N);
    for (uint16_t i = 0; i < N; i++)
    {
        for (uint16_t j = 0; j < N; j++)
            vec.at(j) = fields.at(j).at(i);
        columns.at(i) = new Column(vec);
    }
}

void Board::createDomains()
{
    for (uint16_t i = 0; i < N; i++)
        for (uint16_t j = 0; j < N; j++)
            this -> domains.at(i).at(j) = new Domain(i, j, board.at(i).at(j), fields.at(i).at(j), squares.at((i / 3) * 3 + (j / 3)), rows.at(i), columns.at(j));
}

void Board::createSquares()
{
    std::vector< std::vector<Field *> > vec = std::vector< std::vector<Field *> > (3, std::vector<Field *>(3));
    for (uint16_t n = 0; n < N; n++)
    {
        for (uint16_t i = 0; i < 3; i++)
            for (uint16_t j = 0; j < 3; j++)
                vec.at(i).at(j) = fields.at((n / 3) * 3 + i).at((n % 3) * 3 + j);
        squares.at(n) = new Square(vec);
    }
}

void Board::generatePossibilities()
{
    std::set<uint16_t> possible = std::set<uint16_t>();
    for (uint16_t i = 0; i < N; i++)
        for (uint16_t j = 0; j < N; j++)
            if (board.at(i).at(j) == 0)
                domains.at(i).at(j) -> preparePossibilities();
}