#ifndef BLOCK_FACTORY_HPP
#define BLOCK_FACTORY_HPP

#include <vector>

#include "block.hpp"

class BlockFactory {
    private:
        static std::vector<Block> blocks;
    public:
        static Block getRandomBlock();
};

#endif // BLOCK_FACTORY_HPP
