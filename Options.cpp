#include "Options.h"

Options::Options(float width, float height) {

    if (!font.loadFromFile(R"(..\Assets\prstartk.ttf)")) {
        fmt::println("Error font options");
    };

    currentIndex = 0;
    selectedLevel = 1;
    selectedFont = 1;
    selectedSize = 0;

    previousSelectedLevel = selectedLevel;
    previousSelectedFont = selectedFont;
    previousSelectedSize = selectedSize;

    //ELEMENTS
    elements[0].setString("BACK");
    elements[0].setCharacterSize(60);
    elements[0].setFillColor(sf::Color::Red);
    elements[0].setFont(font);
    elements[0].setPosition(width / 6, height / 6 * 1);

    elements[1].setString("LEVEL");
    elements[1].setCharacterSize(60);
    elements[1].setFillColor(sf::Color::Black);
    elements[1].setFont(font);
    elements[1].setPosition(width / 6, height / 6 * 2);

    elements[2].setString("FONT");
    elements[2].setCharacterSize(60);
    elements[2].setFillColor(sf::Color::Black);
    elements[2].setFont(font);
    elements[2].setPosition(width / 6, height / 6 * 3);

    elements[3].setString("SIZE");
    elements[3].setCharacterSize(60);
    elements[3].setFillColor(sf::Color::Black);
    elements[3].setFont(font);
    elements[3].setPosition(width / 6, height / 6 * 4);

    elements[4].setString("SAVE");
    elements[4].setCharacterSize(60);
    elements[4].setFillColor(sf::Color::Black);
    elements[4].setFont(font);
    elements[4].setPosition(width / 6, height / 6 * 5);

    //LEVELS
    levels[0].setString("easy");
    levels[0].setCharacterSize(40);
    levels[0].setFillColor(sf::Color::Black);
    levels[0].setFont(font);
    levels[0].setPosition(width / 6 + 400, height / 6 * 2);

    levels[1].setString("medium");
    levels[1].setCharacterSize(40);
    levels[1].setFillColor(sf::Color::Red);
    levels[1].setFont(font);
    levels[1].setPosition(width / 6 + 750, height / 6 * 2);

    levels[2].setString("hard");
    levels[2].setCharacterSize(40);
    levels[2].setFillColor(sf::Color::Black);
    levels[2].setFont(font);
    levels[2].setPosition(width / 6 + 1200, height / 6 * 2);

    //FONTS
    fonts[0].setString("arial");
    fonts[0].setCharacterSize(40);
    fonts[0].setFillColor(sf::Color::Black);
    fonts[0].setFont(font);
    fonts[0].setPosition(width / 6 + 400, height / 6 * 3);

    fonts[1].setString("pixel");
    fonts[1].setCharacterSize(40);
    fonts[1].setFillColor(sf::Color::Red);
    fonts[1].setFont(font);
    fonts[1].setPosition(width / 6 + 800, height / 6 * 3);

    //SIZES
    sizes[0].setString("6");
    sizes[0].setCharacterSize(40);
    sizes[0].setFillColor(sf::Color::Red);
    sizes[0].setFont(font);
    sizes[0].setPosition(width / 6 + 400, height / 6 * 4);

    sizes[1].setString("9");
    sizes[1].setCharacterSize(40);
    sizes[1].setFillColor(sf::Color::Black);
    sizes[1].setFont(font);
    sizes[1].setPosition(width / 6 + 750, height / 6 * 4);

    sizes[2].setString("12");
    sizes[2].setCharacterSize(40);
    sizes[2].setFillColor(sf::Color::Black);
    sizes[2].setFont(font);
    sizes[2].setPosition(width / 6 + 1200, height / 6 * 4);


}


auto Options::draw(sf::RenderWindow &window) -> void {

    for (const auto & element : elements) {
        window.draw(element);
    }

    for (const auto & level : levels) {
        window.draw(level);
    }

    for (const auto &f : fonts) {
        window.draw(f);
    }

    for (const auto & size : sizes) {
        window.draw(size);
    }

}

auto Options::up() -> void {

    if (currentIndex - 1 >= 0) {
        elements[currentIndex].setFillColor(sf::Color::Black);
        currentIndex -= 1;
        elements[currentIndex].setFillColor(sf::Color::Red);
    }

}

auto Options::down() -> void {

    if (currentIndex + 1 < elements.size()) {
        elements[currentIndex].setFillColor(sf::Color::Black);
        currentIndex += 1;
        elements[currentIndex].setFillColor(sf::Color::Red);
    }

}

auto Options::select() -> void {

    if (currentIndex == 1) {
        selectedLevel = (selectedLevel + 1) % levels.size();
        setSelectedLevel(selectedLevel);
    }

    if (currentIndex == 2) {
        selectedFont = (selectedFont + 1) % fonts.size();
        setSelectedFont(selectedFont);
    }

    if (currentIndex == 3) {
        selectedSize = (selectedSize + 1) % sizes.size();
        setSelectedSize(selectedSize);
    }
}


//setters
void Options::setSelectedLevel(int level) {

    if (level >= 0 && level < levels.size()) {
        for (auto &l: levels) {
            l.setFillColor(sf::Color::Black);
        }
        selectedLevel = level;
        levels[selectedLevel].setFillColor(sf::Color::Red);
    }

}

void Options::setSelectedFont(int font) {

    if (font >= 0 && font < fonts.size()) {
        for (auto &f: fonts) {
            f.setFillColor(sf::Color::Black);
        }
        selectedFont = font;
        fonts[selectedFont].setFillColor(sf::Color::Red);
    }

}

void Options::setSelectedSize(int size) {

    if (size >= 0 && size < sizes.size()) {
        for (auto &s: sizes) {
            s.setFillColor(sf::Color::Black);
        }
        selectedSize = size;
        sizes[selectedSize].setFillColor(sf::Color::Red);
    }

}

void Options::setStart() {

    for (auto &e: elements)
        e.setFillColor(sf::Color::Black);

    currentIndex = 0;
    elements[currentIndex].setFillColor(sf::Color::Red);

}

void Options::setToPrevious() {

    setSelectedLevel(previousSelectedLevel);
    setSelectedFont(previousSelectedFont);
    setSelectedSize(previousSelectedSize);

    for (auto &e: elements) {
        e.setFillColor(sf::Color::Black);
    }

    currentIndex = 0;
    elements[currentIndex].setFillColor(sf::Color::Red);

}

void Options::setPrevious(int level, int font, int size) {

    previousSelectedLevel = level;
    previousSelectedFont = font;
    previousSelectedSize = size;

}


//getters
int Options::getCurrentIndex() const {
    return currentIndex;
}

int Options::getSelectedLevel() const {
    return selectedLevel;
}

int Options::getSelectedFont() const {
    return selectedFont;
}

int Options::getSelectedSize() const {
    return selectedSize;
}




