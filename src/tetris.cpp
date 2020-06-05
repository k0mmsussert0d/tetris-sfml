#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <map>

#include "const.hpp"
#include "block.hpp"
#include "fields.hpp"
#include "blockfactory.hpp"
#include "stats.hpp"
#include "const/colors.hpp"
#include "const/dirs.hpp"
#include "window.hpp"

int main() {
    sf::RenderWindow renderWindow(sf::VideoMode(534, 686), "Tetris");
    sf::Texture tiles_texture;
    tiles_texture.loadFromFile(const_list.resources_dir + "tiles1.png");
    sf::Texture bg_texture;
    bg_texture.loadFromFile(const_list.resources_dir + "bg.png");

    Window window(renderWindow, bg_texture, tiles_texture);

    bool rotate = false;
    DIR dx = none;
    float timer = 0, delay = 0.3;
    bool pause = false;
    srand(time(0));

    sf::Clock clock;

    Fields fields;

    BlockFactory blockFactory;
    Block block = blockFactory.getRandomBlock();

    GameStats gameStats;

    while (renderWindow.isOpen()) {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event e;
        while (renderWindow.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                renderWindow.close();
            } else if (e.type == sf::Event::KeyPressed) {
                 if (e.key.code == sf::Keyboard::Up) {
                     rotate = true;
                 } else if (e.key.code == sf::Keyboard::Left) {
                     dx = left;
                 } else if (e.key.code == sf::Keyboard::Right) {
                     dx = right;
                 } else if (e.key.code == sf::Keyboard::Down) {
                     timer += 0.3;
                 } else if (e.key.code == sf::Keyboard::P) {
                     pause = !pause;
                 }
            }
        }

        if (!pause) {
            if (timer > delay) { // move block down

            auto full_lines_indices = fields.getFullLinesIndices();

                if (full_lines_indices.size() > 0) {
                    gameStats.addLinesCleared(full_lines_indices.size());

                    for (auto &line_index : full_lines_indices) {
                        fields.removeLineOfIndex(line_index);
                    }

                    window.drawBackground();
                    window.drawColorPoints(fields.getUsedFields());
                    window.refreshWindow();

                    continue;
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

        window.drawBackground();
        window.drawColorPoints(fields.getUsedFields());
        window.drawBlock(block);
        window.refreshWindow();

        gameStats.printStatsToWindow(renderWindow);
        
        if (pause) {
            // draw_paused_text(renderWindow);
        }

        dx = none;
        rotate = false;

        renderWindow.display();
    }
    return 0;
}