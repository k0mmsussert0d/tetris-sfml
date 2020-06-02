#include <cstdlib>

#include "blockfactory.hpp"
#include "block.hpp"
#include "const/colors.hpp"

const Block I ({{4, 5, 6, 7},      {2, 6, 10, 14},     {8, 9, 10, 11},     {1, 5, 9, 13}},  cyan);
const Block Z ({{0, 1, 5, 6},      {2, 5, 6, 9},       {4, 5, 9, 10},      {5, 8, 9, 12}},  blue);
const Block S ({{1, 2, 4, 5},      {1, 5, 6, 10},      {5, 6, 8, 9},       {0, 4, 5, 9}},   purple);
const Block T ({{1, 4, 5, 6},      {1, 5, 6, 9},       {4, 5, 6, 9},       {1, 4, 5, 9}},   pink);
const Block L ({{2, 4, 5, 6},      {1, 5, 9, 10},      {4, 5, 6, 8},       {0, 1, 5, 9}},   l_green);
const Block J ({{0, 4, 5, 6},      {1, 2, 5, 9},       {4, 5, 6, 10},      {1, 5, 8, 9}},   yellow);
const Block O ({{1, 2, 5, 6}}, red);


std::vector<Block> BlockFactory::blocks =  { I, Z, S, T, L, J, O };

Block BlockFactory::getRandomBlock() {
    int n = rand() % blocks.size();

    return blocks[n];
}