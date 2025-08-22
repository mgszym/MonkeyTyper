#include "Menu.h"

Menu::Menu(float width, float height) {

    if (!font.loadFromFile(R"(..\Assets\prstartk.ttf)")) {
        fmt::println("Error font Menu");
    }

    shortcut.setString("Shortcuts in-game:\n\nCtrl + S = Save\n\nCtrl + P = Options\n\nCtrl + E = Rage Quit");
    shortcut.setCharacterSize(30);
    shortcut.setFont(font);
    shortcut.setFillColor({255, 165, 0});
    shortcut.setPosition(width / 1.70, height / 6 * 4.25);

    //elements
    elements[0].setString("PLAY");
    elements[0].setCharacterSize(50);
    elements[0].setFillColor(sf::Color::Red);
    elements[0].setFont(font);
    elements[0].setPosition(width / 6, height / 6 * 1);

    elements[1].setString("LOAD GAME");
    elements[1].setCharacterSize(50);
    elements[1].setFillColor(sf::Color::Black);
    elements[1].setFont(font);
    elements[1].setPosition(width / 6, height / 6 * 2);

    elements[2].setString("SCOREBOARD");
    elements[2].setCharacterSize(50);
    elements[2].setFillColor(sf::Color::Black);
    elements[2].setFont(font);
    elements[2].setPosition(width / 6, height / 6 * 3);

    elements[3].setString("OPTIONS");
    elements[3].setCharacterSize(50);
    elements[3].setFillColor(sf::Color::Black);
    elements[3].setFont(font);
    elements[3].setPosition(width / 6, height / 6 * 4);

    elements[4].setString("EXIT");
    elements[4].setCharacterSize(50);
    elements[4].setFillColor(sf::Color::Black);
    elements[4].setFont(font);
    elements[4].setPosition(width / 6, height / 6 * 5);

    currentIndex = 0;

}

auto Menu::draw(sf::RenderWindow &window) -> void {

    window.draw(shortcut);
    for (const auto & element : elements) {
        window.draw(element);
    }

}

auto Menu::up() -> void {

    if (currentIndex - 1 >= 0) {
        elements[currentIndex].setFillColor(sf::Color::Black);
        currentIndex -= 1;
        elements[currentIndex].setFillColor(sf::Color::Red);
    }

}

auto Menu::down() -> void {

    if (currentIndex + 1 < elements.size()) {
        elements[currentIndex].setFillColor(sf::Color::Black);
        currentIndex += 1;
        elements[currentIndex].setFillColor(sf::Color::Red);
    }

}

auto Menu::getCurrentIndex() const -> int { return currentIndex; }
