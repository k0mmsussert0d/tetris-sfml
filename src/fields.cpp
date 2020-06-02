#include <vector>
#include <map>

#include "fields.hpp"
#include "block.hpp"
#include "const/colors.hpp"

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

std::vector<PointColor> Fields::getUsedFields() {

    std::vector<PointColor> res;

    for (int i = 0; i < status_matrix.size(); ++i ) {
        auto column = status_matrix[i];
        for (int j = 0; j < column.size(); ++j) {
            if (status_matrix[i][j] != NONE) {
                res.push_back({ { i, j }, status_matrix[i][j] });
            }
        }
    }

    return res;
}