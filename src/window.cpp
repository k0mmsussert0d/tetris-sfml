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