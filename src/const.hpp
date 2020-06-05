#ifndef CONST_HPP
#define CONST_HPP

const struct Const {
    const int point_size = 30;
    const int x_offset = 28;
    const int y_offset = 28;
    const std::string resources_dir = "./resources/";

    const struct Positions {
        int level_x = 357;
        int level_y = 28;

        int lines_x = 357;
        int lines_y = 179;

        int score_x = 357;
        int score_y = 103;
    } positions;
} const_list;

#endif // CONST_HPP
