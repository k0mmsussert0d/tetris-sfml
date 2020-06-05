#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "block.hpp"
#include "const.hpp"
#include "fields.hpp"

class Window {
    private:
        sf::RenderWindow& window;
        sf::Texture background_texture;
        sf::Texture tile_texture;
    public:
        Window(sf::RenderWindow&, sf::Texture, sf::Texture);
        void refreshWindow();
        void drawBackground();
        void drawBlock(Block);
        void drawColorPoints(std::vector<PointColor>);
        void drawPoint(Point, COLOR);
};

#endif // WINDOW_HPP