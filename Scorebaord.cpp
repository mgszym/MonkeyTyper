#include "Scoreboard.h"


Scoreboard::Scoreboard(float width, float height) : width(width), height(height) {

    if (!font.loadFromFile(R"(..\Assets\prstartk.ttf)")) {
        fmt::println("Error font scoreboard");
    }

    title = sf::Text("SCOREBOARD", font, 60);
    title.setFillColor(sf::Color::Black);
    title.setPosition(width / 3, height / 11 * 1);

    back = sf::Text("Back", font, 60);
    back.setFillColor(sf::Color::Red);
    back.setPosition(width / 3, height / 11 * 10);
}

auto Scoreboard::loadScores() -> void {

    auto file = std::fstream(R"(..\Assets\Scoreboard.txt)");

    if (!file.is_open()) {
        fmt::println("Error file is open -> Scoreboard.txt");
        return;
    }

    scores.clear();
    auto name = std::string();
    auto score = int();

    while (file >> name >> score) {
        scores.insert(std::pair<int, std::string>(score, name));
    }

    updateScore();

}

auto Scoreboard::updateScore() -> void {


    auto i = 0;
    for (auto const &[score, name]: scores) {

        if (i >= 8) break;

        auto s = std::string(std::to_string(i + 1) + ". " + name + " -> " + std::to_string(score));

        scoreTexts[i].setString(s);
        scoreTexts[i].setFont(font);
        scoreTexts[i].setCharacterSize(40);
        scoreTexts[i].setFillColor(sf::Color::Black);
        scoreTexts[i].setPosition(width / 3, height / 11 * (i + 2));


        i++;
    }


}

auto Scoreboard::draw(sf::RenderWindow &window) -> void {

    window.draw(title);
    window.draw(back);

    for (int i = 0; i < scoreTexts.size(); ++i) {
        window.draw(scoreTexts[i]);
    }

}

