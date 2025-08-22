#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <array>
#include <fmt/core.h>
#include <fstream>

class Scoreboard{

private:

    float width;
    float height;
    sf::Font font;
    sf::Text title;
    sf::Text back;
    std::map<int, std::string, std::greater<>> scores;
    std::array<sf::Text, 8> scoreTexts;

    auto updateScore() -> void;

public:

    Scoreboard(float width, float height);

    auto loadScores() -> void;

    auto draw(sf::RenderWindow &window) -> void;

};
