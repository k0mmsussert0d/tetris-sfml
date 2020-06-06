#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "block.hpp"
#include "const.hpp"
#include "fields.hpp"
#include "stats.hpp"

class Window {
    private:
        sf::RenderWindow& window;
        sf::Texture background_texture;
        sf::Texture tile_texture;
        void displayScore(std::string);
        void displayLevel(std::string);
        void displayLinesCleared(std::string);
        void displayNumber(std::string, float, float);
        void displayMsg(std::string);
    public:
        Window(sf::RenderWindow&, sf::Texture, sf::Texture);
        void refreshWindow();
        void drawBackground();
        void drawBlock(Block);
        void drawColorPoints(std::vector<PointColor>);
        void drawPoint(Point, COLOR);
        void displayGameStats(GameStats);
        void animateLineRemoval(Fields, GameStats, std::vector<int>);
        void displayGameStart();
        void displayGameOver();
        void displayPause();
};

#endif // WINDOW_HPP