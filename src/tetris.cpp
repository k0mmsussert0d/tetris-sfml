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
            if (!block.moveY(1)) { //  block hit the bottom
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

void draw(RenderWindow& window, Fields fields, Block block, Texture bg_texture, Texture block_texture) {
    
    Sprite bg(bg_texture);
    
    window.clear(Color::White);
    window.draw(bg);

    auto points = block.getPoints();
    for (Point p : points) {
        Sprite tile(block_texture);
        tile.setTextureRect(IntRect(block.color * 30, 0, 30, 30));
        tile.setPosition(p.x * 30 + x_offset, p.y * 30 + y_offset);
        window.draw(tile);
    }

    auto old_points = fields.getUsedFields();
    for (const auto &p : old_points) {
        Sprite old_tile(block_texture);
        old_tile.setTextureRect(IntRect(p.color * 30, 0, 30, 30));
        old_tile.setPosition(p.point.x * 30 + x_offset, p.point.y * 30 + y_offset);
        window.draw(old_tile);
    }
}