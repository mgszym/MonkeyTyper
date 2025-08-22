#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <fmt/core.h>

class Menu {

private:

    int currentIndex{};
    sf::Font font;
    sf::Text shortcut;
    std::array<sf::Text, 5> elements;

public:

    Menu(float width, float height);

    auto draw(sf::RenderWindow &window) -> void;

    auto up() -> void;

    auto down() -> void;

    auto getCurrentIndex() const -> int;

};