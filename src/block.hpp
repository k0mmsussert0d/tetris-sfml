#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include <map>

#include "const/colors.hpp"

struct Point {
    int x;
    int y;
};

struct Variant {
    std::vector<int> points;
};

class Block {
    private:
        std::vector<Variant> variants; // available transformations
        int active_variant_i;
        int x_pos;
        int y_pos;
        bool validate_move();
    public:
        Block(std::vector<std::vector<int>>, COLOR);
        std::vector<Point> getPoints();
        COLOR color;
        bool moveX(int);
        bool moveY(int);
        bool rotate();
};

#endif // BLOCK_HPP