#ifndef FIELDS_HPP
#define FIELDS_HPP

#include <vector>
#include <map>

#include "block.hpp"
#include "const.hpp"

class Fields {
    private:
        std::vector<std::vector<COLOR>> status_matrix;
        std::map<Point, COLOR> matrix;
    public:
        Fields();
        bool validateBlock(Block&);
        void saveBlock(Block&);
        std::vector<Point> getUsedFields();
};

#endif // FIELDS_HPP