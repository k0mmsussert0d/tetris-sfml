#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <map>

#include "const.hpp"
#include "block.hpp"
#include "fields.hpp"
#include "blockfactory.hpp"
#include "const/colors.hpp"
#include "const/dirs.hpp"

using namespace sf;

const std::string resourcesDir = "./resources/";

void draw(RenderWindow&, Fields, Block, Texture, Texture);
void animateRemoval(RenderWindow& window, Fields fields, Texture block_texture, std::vector<int> rows_to_remove_indices);
void draw_background(RenderWindow& window, Texture bg_texture);
void draw_block(RenderWindow& window, Texture block_texture, Block block);
void draw_color_points(RenderWindow& window, Texture block_texture, std::vector<PointColor> color_points);
void draw_point(RenderWindow& window, Texture block_texture, Point point, COLOR color);


int main() {
    RenderWindow window(VideoMode(534, 686), "Tetris");

    Texture tiles_texture;
    tiles_texture.loadFromFile(resourcesDir + "tiles1.png");
    Sprite s(tiles_texture);

    Texture bg_texture;
    bg_texture.loadFromFile(resourcesDir + "bg.png");

    bool rotate = false;
    DIR dx = none;
    float timer = 0, delay = 0.3;
    srand(time(0));

    Clock clock;

    Fields fields;

    BlockFactory blockFactory;
    Block block = blockFactory.getRandomBlock();

    while (window.isOpen()) {

        s.setTextureRect(IntRect(block.color * 30, 0, 30, 30));
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            } else if (e.type == Event::KeyPressed) {
                 if (e.key.code == Keyboard::Up) {
                     rotate = true;
                 } else if (e.key.code == Keyboard::Left) {
                     dx = left;
                 } else if (e.key.code == Keyboard::Right) {
                     dx = right;
                 } else if (e.key.code == Keyboard::Down) {
                     timer += 0.3;
                 }
            }
        }

        if (timer > delay) { // move block down

            auto full_lines_indices = fields.getFullLinesIndices();

            if (full_lines_indices.size() > 0) {
                // add score etc.
                for (auto &line_index : full_lines_indices) {
                    fields.removeLineOfIndex(line_index);
                }
            } else if (!block.moveY(1)) { //  block hit the bottom
                fields.saveBlock(block);
                block = blockFactory.getRandomBlock();
            } else if (!fields.validateBlock(block)) {  // block hit the other block
                block.moveY(-1);
                fields.saveBlock(block);
                block = blockFactory.getRandomBlock();
            }
            timer = 0;
        }

        if (dx) { // move block sideways
            block.moveX(dx);
        }

        if (rotate) { // rotate block
            block.rotate();
        }

        draw(window, fields, block, bg_texture, tiles_texture);

        dx = none;
        rotate = false;

        window.display();
    }
    return 0;
}

// void animateRemoval(RenderWindow& window, Fields fields, Texture block_texture, std::vector<int> rows_to_remove_indices) {

//     for (auto row : rows_to_remove_indices) {
//         for (int i = 4, j = 5; i >= 0; --i, ++j) {
//             Clock removal_clock;
//             float timer = 0, delay = 0.1;

//             Point l = { row, i };
//             Point r = { row, j };

//             fields.removeSinglePoint(l);
//             fields.removeSinglePoint(r);

//             auto points = fields.getUsedFields();

//             draw_color_points(window, block_texture, points);

//             while (timer < delay) {
//                 timer += removal_clock.getElapsedTime().asSeconds();
//                 removal_clock.restart();
//             }

//         } 
//     }
// }

void draw(RenderWindow& window, Fields fields, Block block, Texture bg_texture, Texture block_texture) {
    
    draw_background(window, bg_texture);
    draw_block(window, block_texture, block);
    auto old_points = fields.getUsedFields();
    draw_color_points(window, block_texture, old_points);
}

void draw_background(RenderWindow& window, Texture bg_texture) {
    Sprite bg(bg_texture);

    window.clear(Color::White);
    window.draw(bg);
}

void draw_block(RenderWindow& window, Texture block_texture, Block block) {
    auto points = block.getPoints();
    for (const auto &p : points) {
        draw_point(window, block_texture, p, block.color);
    }
}

void draw_color_points(RenderWindow& window, Texture block_texture, std::vector<PointColor> color_points) {
    for (const auto &p : color_points) {
        draw_point(window, block_texture, p.point, p.color);
    }
}

void draw_point(RenderWindow& window, Texture block_texture, Point point, COLOR color) {
    Sprite tile(block_texture);
    tile.setTextureRect(IntRect(color * 30, 0, 30, 30));
    tile.setPosition(point.x * 30 + x_offset, point.y * 30 + y_offset);
    window.draw(tile);
}