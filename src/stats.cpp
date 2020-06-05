#include "stats.hpp"
#include "const.hpp"
#include <SFML/Graphics.hpp>

GameStats::GameStats()
    : score(0), level(0), lines(0), time(0) {}

std::string GameStats::nums_dir = const_list.resources_dir + "/nums";

int GameStats::getScore() {
    return score;
}

int GameStats::getLevel() {
    return level;
}

int GameStats::getTime() {
    return time;
}

void GameStats::addLinesCleared(int n) {
    addScore(n);
    int old_lines = lines;
    lines += n;

    if (lines % 10 < 4 && old_lines % 10 >= 4) {
        level++;
    }
}

void GameStats::addTimeInSeconds(int t) {
    time += t;
}

void GameStats::addScore(int lines) {
    int x = 0;
    switch(lines) {
        case 1:
            x = 40;
            break;
        case 2:
            x = 80;
            break;
        case 3:
            x = 300;
            break;
        case 4:
            x = 1200;
            break;
        default:
            x = 0;
    }

    score += x * (level+1);
}

void GameStats::printStatsToWindow(sf::RenderWindow& window) {
    printScore(window);
    printLevel(window);
    printLinesCleared(window);
}

void GameStats::printScore(sf::RenderWindow& window) {
    printNumber(window, std::string(6 - std::to_string(score).length(), '0') + std::to_string(score), const_list.positions.score_x, const_list.positions.score_y);
}

void GameStats::printLevel(sf::RenderWindow& window) {
    printNumber(window, std::to_string(level), const_list.positions.level_x, const_list.positions.level_y);
}

void GameStats::printLinesCleared(sf::RenderWindow& window) {
    printNumber(window, std::to_string(lines), const_list.positions.lines_x, const_list.positions.lines_y);
}

void GameStats::printNumber(sf::RenderWindow& window, std::string number, float x_pos, float y_pos) {
    for (const auto& c : number) {
        auto i = &c - &number[0];
        sf::Texture num_texture;
        num_texture.loadFromFile(nums_dir + "/" + c + ".png");
        sf::Sprite num_sprite(num_texture);
        num_sprite.setPosition(x_pos + i*30, y_pos);
        window.draw(num_sprite);
    }
}