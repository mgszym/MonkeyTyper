#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <fmt/core.h>

class Options {

private:

    sf::Font font;

    std::array<sf::Text, 5> elements;
    int currentIndex;
    std::array<sf::Text, 3> levels;
    int selectedLevel;
    int previousSelectedLevel;
    std::array<sf::Text, 2> fonts;
    int selectedFont;
    int previousSelectedFont;
    std::array<sf::Text, 3> sizes;
    int selectedSize;
    int previousSelectedSize;


public:

    Options(float width, float height);

    auto draw(sf::RenderWindow &window) -> void;

    auto up() -> void;

    auto down() -> void;

    auto select() -> void;

    void setStart();

    //setters
    void setSelectedLevel(int level);

    void setSelectedFont(int font);

    void setSelectedSize(int size);

    void setToPrevious();

    void setPrevious(int level, int font, int size);


    //getters
    int getCurrentIndex() const;

    int getSelectedLevel() const;

    int getSelectedSize() const;

    int getSelectedFont() const;

};