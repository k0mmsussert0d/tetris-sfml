#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>

#include "const.hpp"
#include "block.hpp"
#include "fields.hpp"
#include "blockfactory.hpp"
#include "const/colors.hpp"
#include "const/dirs.hpp"

using namespace sf;

const std::string resourcesDir = "./resources/";

void draw(RenderWindow&, Fields, Block, Sprite, Sprite);

int main() {
    RenderWindow window(VideoMode(534, 686), "Tetris");

    Texture tiles_texture;
    tiles_texture.loadFromFile(resourcesDir + "tiles.png");
    Sprite s(tiles_texture);
    s.setTextureRect(IntRect(0, 0, 30, 30));

    Texture bg_texture;
    bg_texture.loadFromFile(resourcesDir + "bg.png");
    Sprite bg(bg_texture);

    bool rotate = false;
    DIR dx = none;
    float timer = 0, delay = 0.3;

    Clock clock;

    Fields fields;

    BlockFactory blockFactory;
    Block block = blockFactory.getRandomBlock();

    while (window.isOpen()) {

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

        draw(window, fields, block, bg, s);

        dx = none;
        rotate = false;

        window.display();
    }
    return 0;
}

void draw(RenderWindow& window, Fields fields, Block block, Sprite bg_sprite, Sprite block_sprite) {
    window.clear(Color::White);
    window.draw(bg_sprite);

    std::vector<Point> points = block.getPoints();
    for (Point p : points) {
        block_sprite.setPosition(p.x * 30 + x_offset, p.y * 30 + y_offset);
        window.draw(block_sprite);
    }
}