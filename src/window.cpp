#include <SFML/Graphics.hpp>

#include "window.hpp"
#include "const.hpp"

Window::Window(sf::RenderWindow& window, sf::Texture bg_texture, sf::Texture tile_texture)
    : window(window), background_texture(bg_texture), tile_texture(tile_texture) {}

void Window::refreshWindow() {
    window.display();
}

void Window::drawBackground() {
    sf::Sprite bg(background_texture);

    window.clear(sf::Color::White);
    window.draw(bg);
}

void Window::drawBlock(Block block) {
    auto points = block.getPoints();
    for (const auto& p: points) {
        drawPoint(p, block.color);
    }
}

void Window::drawColorPoints(std::vector<PointColor> color_points) {
    for (const auto& p : color_points) {
        drawPoint(p.point, p.color);
    }
}

void Window::drawPoint(Point point, COLOR color) {
    sf::Sprite tile(tile_texture);
    tile.setTextureRect(sf::IntRect(color * const_list.point_size, 0, const_list.point_size, const_list.point_size));
    tile.setPosition(point.x * const_list.point_size + const_list.x_offset, point.y * const_list.point_size + const_list.y_offset);
    window.draw(tile);
}

void Window::displayGameStats(GameStats game_stats) {
    displayScore(std::to_string(game_stats.getScore()));
    displayLevel(std::to_string(game_stats.getLevel()));
    displayLinesCleared(std::to_string(game_stats.getLinesCleared()));
}

void Window::displayScore(std::string score) {
    displayNumber(std::string(5 - score.length(), '0') + score, const_list.positions.score_x, const_list.positions.score_y);
}

void Window::displayLevel(std::string level) {
    displayNumber(level, const_list.positions.level_x, const_list.positions.level_y);
}

void Window::displayLinesCleared(std::string lines_cleared) {
    displayNumber(lines_cleared, const_list.positions.lines_x, const_list.positions.lines_y);
}

void Window::displayNumber(std::string number, float x_pos, float y_pos) {
    for (const auto &c : number) {
        auto i = &c - &number[0];
        sf::Texture num_texture;
        num_texture.loadFromFile(const_list.resources_dir + "/nums/" + c + ".png");
        sf::Sprite num_sprite(num_texture);
        num_sprite.setPosition(x_pos + i * const_list.point_size, y_pos);
        window.draw(num_sprite);
    }
}

void Window::animateLineRemoval(Fields fields, GameStats game_stats, std::vector<int> lines_to_remove) {
    sf::Clock clock;
    float timer = 0, remove_delay = 0.1;

    for (int i = 4, j = 5; i >= 0; --i, ++j) {
        for (const auto &l : lines_to_remove) {
            timer = 0;
            Point left { l, i };
            Point right { l, j };
            fields.removeSinglePoint(left);
            fields.removeSinglePoint(right);
        }
        drawBackground();
        displayGameStats(game_stats);
        drawColorPoints(fields.getUsedFields());
        refreshWindow();
        while (timer < remove_delay) {
            clock.restart();
            timer += clock.getElapsedTime().asSeconds();
        }
    }
}

void Window::displayGameStart() {
    displayMsg("pressenter.png");
}

void Window::displayPause() {
    displayMsg("paused.png");
}

void Window::displayGameOver() {
    displayMsg("gameover.png");
}

void Window::displayMsg(std::string filename) {
    sf::Texture msg_text;
    msg_text.loadFromFile(const_list.resources_dir + "/" + filename);
    sf::Sprite msg(msg_text);
    msg.setPosition(const_list.positions.com_x, const_list.positions.com_y);
    window.draw(msg);
}