#include <vector>

#include "fields.hpp"
#include "const.hpp"

Fields::Fields() {
    std::vector<std::vector<COLOR>> status_matrix(
            10,
            std::vector<COLOR>(20, NONE)
    );

    this->status_matrix = status_matrix;
};

bool Fields::validateBlock(Block& b) {
    std::vector<Point> points = b.getPoints();
    for (Point p : points) {
        if (status_matrix[p.x][p.y] != NONE) {
            return false;
        }
    }

    return true;
};

void Fields::saveBlock(Block& b) {
    if (!this->validateBlock(b)) {
        return;
    }

    for (Point p : b.getPoints()) {
        status_matrix[p.x][p.y] = b.color;
    }
}

std::vector<Point> Fields::getUsedFields() {
    for (auto column : status_matrix) {
        
    }
}