#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <fmt/core.h>

class End {

private:

    sf::Text lost;
    sf::Text score;
    int scoreCount = 0;
    sf::Font font;
    sf::RectangleShape nameLabel;
    sf::Text nameBox;
    std::string nameString;
    int currentIndex = 0;
    std::array<sf::Text, 2> elements;

public:

    End(float width, float height);

    auto draw(sf::RenderWindow &window) -> void;

    auto up() -> void;

    auto down() -> void;

    void typing(int unicode);

    void setScoreCount(int scoreCount);

    int getCurrentIndex() const;

    const std::string &getNameString() const;

    int getScoreCount() const;

    void setNameString(const std::string &nameString);

};