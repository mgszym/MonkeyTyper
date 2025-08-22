#pragma once

#include <SFML/Graphics.hpp>
#include <fmt/core.h>
#include <vector>
#include "Utilities.h"


class Game {

private:

    const int BACKSPACE_KEY = 0x0008;
    const int ENTER_KEY = 0x000D;

    sf::Font font;
    sf::RectangleShape line;
    //input
    sf::RectangleShape inputBox;
    sf::Text box;
    std::string inputString;
    //score
    sf::Text score;
    int scoreCounter;
    //miss counter
    sf::Text misses;
    int missCounter;
    //timer
    sf::Text timer;
    sf::Clock clock;
    sf::Time loadTime;
    //game logic
    sf::Font wordsFont;
    std::vector<sf::Text> words;
    std::vector<std::string> wordsList;
    int lastYPosition = -1;
    sf::Clock gameClock;
    float wordDelay;
    float wordSpeed;
    int wordSize;


public:

    Game(float width, float height);

    auto draw(sf::RenderWindow &window) -> void;

    auto typing(int unicode) -> void;

    auto renderWords(float xPosition, float width) -> void;

    auto saveGame(int level, int size, int font) -> void;

    auto loadGame() -> std::vector<int>;

    auto reset() -> void;

    auto startClock() -> void;


    //getters
    int getMissCounter() const;

    int getScoreCounter() const;


    //setters
    void setLevel(int index);

    void setSize(int index);

    void setFont(int index);

};
