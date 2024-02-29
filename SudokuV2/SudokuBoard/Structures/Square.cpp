#include "Structures.hpp"

Square::Square(std::vector<std::vector<Field *>> &values) : fields(values) {}

void Square::removePossibleNumbers(uint16_t v)
{
    for (const auto& a : fields)
        for (auto b : a)
            b -> removeElementFromPossibilities(v);
}

size_t Square::countFieldsWithGivenPossibleNumber(uint16_t number)
{
    size_t count = 0;
    for (auto & a : fields)
        for (auto & field : a)
            if (field -> numberExistsInPossibilities(number))
                count++;
    return count;
}

std::set<uint16_t> Square::numbersInSquare()
{
    std::set<uint16_t> numbers = std::set<uint16_t>();
    for (auto & a : fields)
        for (auto &field : a)
            if (field -> getValue() != 0)
                numbers.insert(field -> getValue());
    return numbers;
}