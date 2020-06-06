#ifndef STATS_HPP
#define STATS_HPP

#include <SFML/Graphics.hpp>

class GameStats {
    private:
        int score;
        int level;
        int lines;
        int time;
        static std::string nums_dir;
        void addScore(int);
        void printScore(sf::RenderWindow&);
        void printLevel(sf::RenderWindow&);
        void printLinesCleared(sf::RenderWindow&);
        void printNumber(sf::RenderWindow&, std::string, float, float);
    public:
        GameStats();
        int getScore();
        int getLevel();
        int getLinesCleared();
        int getTime();
        void addLinesCleared(int);
        void addTimeInSeconds(int);
        void printStatsToWindow(sf::RenderWindow&);
};

#endif // STATS_HPP