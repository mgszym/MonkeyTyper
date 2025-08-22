#include "End.h"

End::End(float width, float height) {

    if (!font.loadFromFile(R"(..\Assets\prstartk.ttf)")) {
        fmt::println("Error font end");
    }

    //lost
    lost = sf::Text("YOU LOST", font, 100);
    lost.setFillColor(sf::Color(255, 0, 0));
    lost.setPosition(width / 5, height / 6 * 1);

    //score
    auto scoreString = std::string("Your score: " + std::to_string(scoreCount));
    score = sf::Text(scoreString, font, 50);
    score.setFillColor(sf::Color(0, 0, 0));
    score.setPosition(width / 5, height / 6 * 2);

    //namespace
    nameLabel.setSize(sf::Vector2f(650, 70));
    nameLabel.setFillColor(sf::Color::White);
    nameLabel.setOutlineColor(sf::Color::Black);
    nameLabel.setOutlineThickness(5);
    nameLabel.setPosition(width / 5, height / 6 * 3);

    nameString = std::string("");
    nameBox = sf::Text(nameString, font, 30);
    nameBox.setFillColor(sf::Color::Black);
    nameBox.setPosition(width / 5 + 20, height / 6 * 3 +20);

    //elements
    elements[0].setString("SAVE");
    elements[0].setCharacterSize(50);
    elements[0].setFillColor(sf::Color::Red);
    elements[0].setFont(font);
    elements[0].setPosition(width / 5, height / 6 * 4);

    elements[1].setString("MENU");
    elements[1].setCharacterSize(50);
    elements[1].setFillColor(sf::Color::Black);
    elements[1].setFont(font);
    elements[1].setPosition(width / 5, height / 6 * 5);

}

auto End::draw(sf::RenderWindow &window) -> void {

    window.draw(nameLabel);
    window.draw(nameBox);
    window.draw(lost);
    window.draw(score);

    for (const auto &element: elements) {
        window.draw(element);
    }

}

auto End::up() -> void {

    if (currentIndex - 1 >= 0) {
        elements[currentIndex].setFillColor(sf::Color::Black);
        currentIndex -= 1;
        elements[currentIndex].setFillColor(sf::Color::Red);
    }

}

auto End::down() -> void {

    if (currentIndex + 1 < elements.size()) {
        elements[currentIndex].setFillColor(sf::Color::Black);
        currentIndex += 1;
        elements[currentIndex].setFillColor(sf::Color::Red);
    }

}

auto End::typing(int unicode) -> void {

    auto charT = (unicode);

    if (charT == 8 && !nameString.empty()) {
        nameString.pop_back();
    } else if (nameString.size() != 20 && charT != 13) {
        nameString.push_back(static_cast<char>(charT));
    }

    nameBox.setString(nameString);
}

void End::setScoreCount(int scoreCount) {

    End::scoreCount = scoreCount;
    auto scoreString = std::string("Your score: " + std::to_string(scoreCount));
    score.setString(scoreString);

}

int End::getCurrentIndex() const {
    return currentIndex;
}


const std::string &End::getNameString() const {
    return nameString;
}

int End::getScoreCount() const {
    return scoreCount;
}

void End::setNameString(const std::string &nameString) {
    End::nameString = nameString;
    nameBox.setString(nameString);
}

