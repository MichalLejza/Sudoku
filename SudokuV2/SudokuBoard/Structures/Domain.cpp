#include "Structures.hpp"

Domain::Domain(uint16_t x, uint16_t y, uint16_t v, Field *f, Square *s, Row *r, Column *c) : X(x), Y(y), value(v), field(f), square(s), column(c), row(r) {}

std::set<uint16_t> Domain::getPossibilities() const
{
    return this -> field -> getPossibilities();
}

uint16_t Domain::getValue()
{
    return this -> value;
}

void Domain::setValue(uint16_t v)
{
    this -> value = v;
    this -> field -> setValue(v);
    this -> square -> removePossibleNumbers(v);
    this -> row -> removePossibleNumbers(v);
    this -> column -> removePossibleNumbers(v);
}

void Domain::makeMove(int &stop)
{
    if (this -> value == 0)
    {
        std::set<uint16_t> possibilities = this -> field -> getPossibilities();
        if (possibilities.empty())
            return;
        if (possibilities.size() == 1)
        {
            auto it = possibilities.begin();
            uint16_t v = *it;
            setValue(v);
            stop = 1;
            return;
        }
        else
        {
            for (uint16_t number : possibilities)
            {
                if (square -> countFieldsWithGivenPossibleNumber(number) == 1)
                {
                    setValue(number);
                    stop = 1;
                    return;
                }
                if (row -> countFieldsWithGivenPossibleNumber(number) == 1)
                {
                    setValue(number);
                    stop = 1;
                    return;
                }
                if (column ->countFieldsWithGivenPossibleNumber(number) == 1)
                {
                    setValue(number);
                    stop = 1;
                    return;
                }
            }
        }
    }
}

void Domain::preparePossibilities() const
{
    std::set<uint16_t> numbers = std::set<uint16_t>();
    std::set<uint16_t> rowNumbers = this -> row -> numbersInRow();
    std::set<uint16_t> columnNumbers = this -> column -> numbersInColumn();
    std::set<uint16_t> squareNumbers = this -> square -> numbersInSquare();

    for (int i = 1; i <= 9; i++)
        numbers.insert(i);
    for (auto a : rowNumbers)
        numbers.erase(a);
    for (auto a : columnNumbers)
        numbers.erase(a);
    for (auto a : squareNumbers)
        numbers.erase(a);

    this -> field ->setPossibilities(numbers);

    rowNumbers.clear();
    columnNumbers.clear();
    squareNumbers.clear();
    numbers.clear();
}

void Domain::print() const
{
    if (value == 0)
    {
        std::cout << this -> value << "  --  ";
        for (auto a : field -> getPossibilities())
            std::cout << a << ", ";
        std::cout << std::endl;
    }
    else
    {
        std::cout << "\x1B[32m";
        std::cout << this -> value << std::endl;
        std::cout << "\x1B[0m";
    }
}