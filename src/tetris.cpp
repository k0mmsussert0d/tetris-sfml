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
void draw_background(RenderWindow& window, Texture bg_texture);
void draw_block(RenderWindow& window, Texture block_texture, Block block);
void draw_color_points(RenderWindow& window, Texture block_texture, std::vector<PointColor> color_points);
void draw_point(RenderWindow& window, Texture block_texture, Point point, COLOR color);
void draw_paused_text(RenderWindow& window);


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
    bool pause = false;
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
                 } else if (e.key.code == Keyboard::P) {
                     pause = !pause;
                 }
            }
        }

        if (!pause) {
            if (timer > delay) { // move block down

            auto full_lines_indices = fields.getFullLinesIndices();

                if (full_lines_indices.size() > 0) {
                    // add score etc.
                    for (auto &line_index : full_lines_indices) {
                        fields.removeLineOfIndex(line_index);
                        draw(window, fields, block, bg_texture, tiles_texture);
                        continue;
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
        }

        draw(window, fields, block, bg_texture, tiles_texture);
        if (pause) {
            draw_paused_text(window);
        }

        dx = none;
        rotate = false;

        window.display();
    }
    return 0;
}


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

void draw_paused_text(RenderWindow& window) {
    Text paused_text;
    Font font;
    font.loadFromFile(resourcesDir + "/DejaVuSans.ttf");
    paused_text.setFont(font);
    paused_text.setString("[P]aused");
    paused_text.setCharacterSize(48);
    paused_text.setFillColor(Color::Red);
    paused_text.setStyle(Text::Bold);
    paused_text.setPosition(70, 200);
    window.draw(paused_text);
}