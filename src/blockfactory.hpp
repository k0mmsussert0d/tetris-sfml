#ifndef BLOCK_FACTORY_HPP
#define BLOCK_FACTORY_HPP

#include <vector>

#include "block.hpp"

class BlockFactory {
    private:
        std::vector<Block> blocks;
    public:
        BlockFactory();
        Block getRandomBlock();
};

#endif // BLOCK_FACTORY_HPP
