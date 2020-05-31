#ifndef CONST_HPP
#define CONST_HPP

#include "block.hpp"

#include <vector>

const int x_offset = 28;
const int y_offset = 28;

const Block I ({{4, 5, 6, 7},      {2, 6, 10, 14},     {8, 9, 10, 11},     {1, 5, 9, 13}});
const Block Z ({{0, 1, 5, 6},      {2, 5, 6, 9},       {4, 5, 9, 10},      {5, 8, 9, 12}});
const Block S ({{1, 2, 4, 5},      {1, 5, 6, 10},      {5, 6, 8, 9},       {0, 4, 5, 9}});
const Block T ({{1, 4, 5, 6},      {1, 5, 6, 9},       {4, 5, 6, 9},       {1, 4, 5, 9}});
const Block L ({{2, 4, 5, 6},      {1, 5, 9, 10},      {4, 5, 6, 8},       {0, 1, 5, 9}});
const Block J ({{0, 4, 5, 6},      {1, 2, 5, 9},       {4, 5, 6, 10},      {1, 5, 8, 9}});
const Block O ({{1, 2, 5, 6}});

std::vector<Block> figures = {I, Z, S, T, L, J, O};


enum DIR {
    left = -1,
    none,
    right
};

#endif // CONST_HPP