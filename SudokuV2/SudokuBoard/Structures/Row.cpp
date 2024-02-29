#include "Structures.hpp"

Row::Row(std::vector<Field *> &values) : fields(values) {}

void Row::removePossibleNumbers(uint16_t v)
{
    for (auto& a : fields)
            a -> removeElementFromPossibilities(v);
}

size_t Row::countFieldsWithGivenPossibleNumber(uint16_t number)
{
    size_t count = 0;
    for (auto & field : fields)
        if (field ->numberExistsInPossibilities(number))
            count++;
    return count;
}

std::set<uint16_t> Row::numbersInRow()
{
    std::set<uint16_t> numbers = std::set<uint16_t>();
    for (auto & field : fields)
        if (field -> getValue() != 0)
            numbers.insert(field -> getValue());
    return numbers;
}