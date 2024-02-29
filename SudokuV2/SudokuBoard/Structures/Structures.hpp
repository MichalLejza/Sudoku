#ifndef SUDOKUV2_STRUCTURES_HPP
#define SUDOKUV2_STRUCTURES_HPP

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <vector>
#include <utility>

#pragma once

class Field
{
    std::pair<uint16_t, uint16_t> coordinates;
    uint16_t value;
    std::set<uint16_t> possible;

public:
    Field(uint16_t X, uint16_t Y, uint16_t value);
    ~Field() = default;
    uint16_t getValue() const;
    void setValue(uint16_t v);
    void setPossibilities(std::set<uint16_t> p);
    std::set<uint16_t> getPossibilities() const;
    void removeElementFromPossibilities(uint16_t v);
    bool numberExistsInPossibilities(uint16_t number);
};

class Column
{
    std::vector<Field *> fields;

public:
    explicit Column(std::vector<Field *> &values);
    ~Column() = default;
    void removePossibleNumbers(uint16_t v);
    size_t countFieldsWithGivenPossibleNumber(uint16_t number);
    std::set<uint16_t> numbersInColumn();
};

class Square
{
    std::vector<std::vector<Field *>> fields;

public:
    explicit Square(std::vector<std::vector<Field *>> &values);
    ~Square() = default;
    void removePossibleNumbers(uint16_t v);
    size_t countFieldsWithGivenPossibleNumber(uint16_t number);
    std::set<uint16_t> numbersInSquare();
};

class Row
{
    std::vector<Field *> fields;

public:
    explicit Row(std::vector<Field *> &values);
    ~Row() = default;
    void removePossibleNumbers(uint16_t v);
    size_t countFieldsWithGivenPossibleNumber(uint16_t number);
    std::set<uint16_t> numbersInRow();
};

class Domain
{
public:
    uint16_t X, Y, value;
    Field *field;
    Square *square;
    Row *row;
    Column *column;
public:
    Domain(uint16_t x, uint16_t y, uint16_t v, Field *f, Square *s, Row *r, Column *c);
    ~Domain() = default;
    std::set<uint16_t> getPossibilities() const;
    void setValue(uint16_t v);
    void preparePossibilities() const;
    void makeMove(int &stop);
    void print() const;
    uint16_t getValue();
};


#endif
