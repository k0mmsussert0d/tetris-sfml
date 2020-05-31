#include "block.hpp"

#include <vector>
#include <algorithm>

Block::Block (std::vector<std::vector<int>> mappings) {
    x_pos = 0;
    y_pos = 0;

    for (std::vector<int>& mapping : mappings) {
        Variant variant = { mapping };
        variants.push_back(variant);
    }

    active_variant_i = 0;
}

std::vector<Point> Block::getPoints() {
    std::vector<Point> res;

    for (int const& value : variants[active_variant_i].points) {
        Point p;
        p.x = (value % 4) + x_pos;
        p.y = (value / 4) + y_pos;

        res.push_back(p);
    }
    
    return res;
}

void Block::moveX(int move) {
    int bk = x_pos;
    this->x_pos += move;
    if (!validate_move()) {
        this->x_pos = bk; 
    }
}

void Block::moveY(int move) {
    int bk = y_pos;
    this->y_pos += move;
    if (!validate_move()) {
        this->y_pos = bk;
    }
}

void Block::rotate() {
    if (active_variant_i + 1 >= variants.size()) {
        this->active_variant_i = 0;
    } else {
        this->active_variant_i += 1;
    }
}

bool Block::validate_move() {
    auto points = getPoints();
    return std::any_of(points.begin(), points.end(), [](Point p){ return p.x >= 0 && p.x < 10 && p.y >= 0 && p.y < 20; });
}