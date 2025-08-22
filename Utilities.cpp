#include "Utilities.h"

auto generateWordsList(int size) -> std::vector<std::string> {

    auto file = std::fstream(R"(..\Assets\ListOfWords.txt)");
    auto words = std::vector<std::string>();
    auto word = std::string();

    while (file >> word) {
        if (word.size() <= size)
            words.push_back(word);
    }

    return words;
}

auto generateWord(int size, const std::string& s,sf::Font &font, float yPosition, float xPosition, float delay) -> sf::Text {

    auto result = sf::Text();
    result.setString(s);
    result.setFont(font);
    result.setCharacterSize(size);
    result.setFillColor(sf::Color::Black);
    result.setPosition(xPosition + delay, yPosition);

    return result;
}

auto checkAndUpdateWord(sf::Text &word, sf::Text &box) -> bool {

    auto wordString = word.getString();
    auto boxString = box.getString();

    bool isMatching = (wordString == boxString);

    if (isMatching) {
        box.setString("");
    }

    return isMatching;
}

auto checkCollision(sf::Text &word, float width) -> bool {

    auto [x, y] = word.getPosition();

    if (x < 1350) word.setFillColor({0, 0, 0});
    if (x > 1350) word.setFillColor({255, 165, 0});
    if (x > 1600) word.setFillColor({255, 0, 0});

    if (x > width) {
        return true;
    }

    return false;
}
