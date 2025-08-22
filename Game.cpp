#include "Game.h"

Game::Game(float width, float height) : wordDelay(1.25f), wordSpeed(0.25f), wordSize(25) {

    if (!font.loadFromFile(R"(..\Assets\prstartk.ttf)")) {
        fmt::println("Error font game");
    }

    if (!wordsFont.loadFromFile(R"(..\Assets\prstartk.ttf)")) {
        fmt::println("Error words-font game");
    }

    wordsList = generateWordsList(6);

    //input
    inputBox.setSize(sf::Vector2f(650, 70));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(5);
    inputBox.setPosition(50, 940);

    inputString = std::string("");
    box = sf::Text(inputString, font, 30);
    box.setFillColor(sf::Color::Black);
    box.setPosition(70, 960);

    //score
    scoreCounter = 0;
    score = sf::Text("Score: " + std::to_string(scoreCounter), font, 30);
    score.setFillColor(sf::Color::Black);
    score.setPosition(800, 960);

    //misses
    missCounter = 0;
    misses = sf::Text("Misses: " + std::to_string(missCounter) + "/10", font, 30);
    misses.setFillColor(sf::Color::Black);
    misses.setPosition(1150, 960);

    //timer
    timer = sf::Text("Time: 0", font, 30);
    timer.setFillColor(sf::Color::Black);
    timer.setPosition(1550, 960);

    line.setSize(sf::Vector2f(width, 5));
    line.setFillColor(sf::Color::Black);
    line.setPosition(0, 900);

}

auto Game::draw(sf::RenderWindow &window) -> void {

    for (auto &word: words) window.draw(word);

    window.draw(inputBox);
    window.draw(box);
    window.draw(score);
    window.draw(misses);
    window.draw(timer);
    window.draw(line);

}

auto Game::typing(int unicode) -> void {

    auto charT = (unicode);
    auto isAlpha = std::isalpha(static_cast<char>(charT));


    if (charT == BACKSPACE_KEY && !inputString.empty()) {
        inputString.pop_back();
    } else if (inputString.size() != 20 && isAlpha) {
        inputString.push_back(static_cast<char>(charT));
    } else if (charT == ENTER_KEY){
        inputString.clear();
    }

    box.setString(inputString);
}

auto Game::renderWords(float xPosition, float width) -> void {

    //Formatted timer
    auto elapsed = clock.getElapsedTime() + loadTime;
    int totalSeconds = static_cast<int>(elapsed.asSeconds());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::string timeString = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                             (seconds < 10 ? "0" : "") + std::to_string(seconds);

    timer.setString("Time: " + timeString);

    //Words creating
    if (gameClock.getElapsedTime().asSeconds() >= wordDelay) {

        auto yPosition = int();

        do {
            yPosition = (std::rand() % 8) + 1;
        } while (yPosition == lastYPosition);

        lastYPosition = yPosition;
        auto randomIndex = (std::rand() % wordsList.size());

        auto word = generateWord(wordSize, wordsList[randomIndex], wordsFont, 100 * yPosition, xPosition, wordDelay);
        words.push_back(word);

        gameClock.restart();
    }

    //Logic of the game
    for (auto it = words.begin(); it != words.end();) {

        it->move(wordSpeed, 0);

        if (checkCollision(*it, width)) {
            words.erase(it);
            missCounter += 1;
            misses.setString("Misses: " + std::to_string(missCounter) + "/10");
        } else if (checkAndUpdateWord(*it, box)) {
            words.erase(it);
            inputString.clear();
            scoreCounter += 1;
            score.setString("Score: " + std::to_string(scoreCounter));
        } else {
            it++;
        }

    }

}

auto Game::saveGame(int level, int size, int font) -> void {

    auto file = std::fstream(R"(..\Assets\SavedGame.txt)", std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        fmt::println("Saved Game error");
        return;
    }

    file << "score " << scoreCounter << '\n';
    file << "miss " << missCounter << '\n';
    file << "time " << clock.getElapsedTime().asSeconds() << '\n';
    file << "level " << level << '\n';
    file << "size " << size << '\n';
    file << "font " << font << '\n';


    for (auto const &word: words) {
        file << "word " << word.getString().toAnsiString() << " " << word.getPosition().x << " " << word.getPosition().y
             << '\n';
    }

}

auto Game::loadGame() -> std::vector<int> {

    auto file = std::fstream(R"(..\Assets\SavedGame.txt)");
    auto vec = std::vector<int>();

    if (!file.is_open()) {
        fmt::println("Load Game error");
    }

    auto line = std::string();

    while (std::getline(file, line)) {

        auto ss = std::stringstream(line);
        auto key = std::string();
        ss >> key;

        if (key == "score") {
            ss >> scoreCounter;
            score.setString("Score: " + std::to_string(scoreCounter));
        }

        if (key == "miss") {
            ss >> missCounter;
            misses.setString("Misses: " + std::to_string(missCounter) + "/10");
        }

        if (key == "time") {
            float savedTime;
            ss >> savedTime;

            int totalSeconds = static_cast<int>(savedTime);
            int minutes = totalSeconds / 60;
            int seconds = totalSeconds % 60;

            auto timeString = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                              (seconds < 10 ? "0" : "") + std::to_string(seconds);

            timer.setString("Time: " + timeString);

            clock.restart();
            loadTime = sf::seconds(savedTime);
        }

        if (key == "level"){
            auto index = int();
            ss >> index;
            vec.push_back(index);

            setLevel(index);
        }

        if (key == "size"){
            auto index = int();
            ss >> index;
            vec.push_back(index);

            setSize(index);
        }

        if (key == "font"){
            auto index = int();
            ss >> index;
            vec.push_back(index);

            setFont(index);
        }

        if (key == "word") {
            auto text = std::string();
            auto x = float();
            auto y = float();

            ss >> text >> x >> y;
            sf::Text word(text, wordsFont, wordSize);
            word.setPosition(x, y);
            words.push_back(word);
        }


    }

    return vec;
}

auto Game::reset() -> void {

    scoreCounter = 0;
    missCounter = 0;
    inputString.clear();
    words.clear();
    clock.restart();

    box.setString(inputString);
    score.setString("Score: " + std::to_string(scoreCounter));
    misses.setString("Misses: " + std::to_string(missCounter));

}

auto Game::startClock() -> void {
    clock = sf::Clock();
    gameClock = sf::Clock();
}


//Getters
int Game::getMissCounter() const {
    return missCounter;
}

int Game::getScoreCounter() const {
    return scoreCounter;
}


//Setters
void Game::setLevel(int index) {

    switch (index) {
        case 0: //easy
            wordSpeed = 0.15f;
            wordDelay = 1.5f;
            break;
        case 1: //medium
            wordSpeed = 0.25f;
            wordDelay = 1.25f;
            break;
        case 2: //hard
            wordSpeed = 0.40f;
            wordDelay = 1.f;
            break;
    }

}

void Game::setSize(int index) {

    switch (index) {
        case 0: //6
            wordsList = generateWordsList(6);
            break;
        case 1: //9
            wordsList = generateWordsList(9);
            break;
        case 2: //12
            wordsList = generateWordsList(12);
            break;
    }

}

void Game::setFont(int index) {

    switch (index) {
        case 0:
            wordsFont.loadFromFile(R"(..\Assets\arial.ttf)");
            break;
        case 1:
            wordsFont.loadFromFile(R"(..\Assets\prstartk.ttf)");
            break;
    }

}







