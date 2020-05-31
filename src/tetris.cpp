#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>

#include "const.hpp"

using namespace sf;

const std::string resourcesDir = "./resources/";

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

    int n = 5;
    Block block = figures[n];

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
            block.moveY(1);
            timer = 0;
        }

        if (dx) { // move block sideways
            block.moveX(dx);
        }

        if (rotate) { // rotate block
            block.rotate();
        }

        std::vector<Point> points = block.getPoints();

        window.clear(Color::White);
        window.draw(bg);

        for (int i = 0; i < 4; i++) {
            s.setPosition(points[i].x * 30 + x_offset, points[i].y * 30 + y_offset);
            window.draw(s);
        }

        dx = none;
        rotate = false;

        window.display();
    }
    return 0;
}