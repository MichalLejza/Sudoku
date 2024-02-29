#include "Structures.hpp"

Field::Field(uint16_t X, uint16_t Y, uint16_t value)
{
    this -> coordinates = std::pair<uint16_t, uint16_t> {X,Y};
    this -> value = value;
    this -> possible = std::set<uint16_t>();
}

uint16_t Field::getValue() const
{
    return this -> value;
}

void Field::setValue(uint16_t v)
{
    this -> value = v;
    this -> possible.clear();
}

void Field::setPossibilities(std::set<uint16_t> p)
{
    this -> possible = std::move(p);
}

std::set<uint16_t> Field::getPossibilities() const
{
    return this -> possible;
}

void Field::removeElementFromPossibilities(uint16_t v)
{
    this -> possible.erase(v);
}

bool Field::numberExistsInPossibilities(uint16_t number)
{
    return possible.find(number) != possible.end();
}