#ifndef FIELDS_HPP
#define FIELDS_HPP

#include <vector>
#include <map>

#include "block.hpp"
#include "const/colors.hpp"

struct PointColor {
    Point point;
    COLOR color;
};

class Fields {
    private:
        std::vector<std::vector<COLOR>> status_matrix;
    public:
        Fields();
        bool validateBlock(Block&);
        void saveBlock(Block&);
        std::vector<PointColor> getUsedFields();
};

#endif // FIELDS_HPP