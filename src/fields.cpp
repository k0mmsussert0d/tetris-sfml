#include <vector>
#include <map>
#include <algorithm>

#include "fields.hpp"
#include "block.hpp"
#include "const/colors.hpp"

Fields::Fields() {
    std::vector<std::vector<COLOR>> status_matrix(
            20,
            std::vector<COLOR>(10, NONE)
    );

    this->status_matrix = status_matrix;
};

bool Fields::validateBlock(Block& b) {
    std::vector<Point> points = b.getPoints();
    for (Point p : points) {
        if (status_matrix[p.y][p.x] != NONE) {
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
        status_matrix[p.y][p.x] = b.color;
    }
}

std::vector<PointColor> Fields::getUsedFields() {

    std::vector<PointColor> res;

    for (int i = 0; i < status_matrix.size(); ++i ) {
        auto column = status_matrix[i];
        for (int j = 0; j < column.size(); ++j) {
            if (status_matrix[i][j] != NONE) {
                res.push_back({ { j, i }, status_matrix[i][j] });
            }
        }
    }

    return res;
}

void Fields::removeLineOfIndex(int index) {
    for (int i = index; i > 0; --i) {
        auto &row = status_matrix[i];
        auto next_row = status_matrix[i-1];

        if (std::all_of(next_row.cbegin(), next_row.cend(), [](COLOR c){ return c == NONE; })) {  // clear row found
            row.assign(10, NONE);
            break;
        }

        for (int i = 0; i < row.size(); ++i) {
            row[i] = next_row[i];
        }
    }
}

std::vector<int> Fields::getFullLinesIndices() {
    std::vector<int> res;

    for (auto &row : status_matrix) {
        int i = &row - &status_matrix[0];
        if (std::all_of(row.cbegin(), row.cend(), [](COLOR c){ return c != NONE; })) {  // full row found
            res.push_back(i);
        }
    }

    return res;
}

bool Fields::removeSinglePoint(Point p) {
    auto &point_to_remove = status_matrix[p.x][p.y];
    
    if (point_to_remove != NONE) {
        point_to_remove = NONE;
        return true;
    }

    return false;
}