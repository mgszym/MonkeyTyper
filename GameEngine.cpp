#include "Menu.h"
#include "Scoreboard.h"
#include "Options.h"
#include "Game.h"
#include "End.h"
#include <SFML/Graphics.hpp>

#define startX (-75)
#define width 1920
#define height 1080
/*
 * ctrl + s - save game (game state)
 * ctrl + p - options in game state
 */


class GameEngine {

private:

    enum class State {
        MENU, SCOREBOARD, OPTIONS, GAME, END
    };

    State currentState;
    State previousState;
    sf::RenderWindow window;
    sf::Font font;
    Menu menu;
    Scoreboard scoreboard;
    Options options;
    Game game;
    End end;


    auto handleEvents() -> void {

        auto event = sf::Event();

        while (window.pollEvent(event)) {

            switch (event.type) {
                case sf::Event::Closed:

                    if (currentState == State::GAME) {
                        game.saveGame(options.getSelectedLevel(), options.getSelectedSize(), options.getSelectedFont());
                    }

                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    handleKeyPress(event.key.code);
                    break;
                case sf::Event::TextEntered:
                    handleTextEntered(event.text.unicode);
                    break;
            }

        }

    }

    auto handleKeyPress(sf::Keyboard::Key key) -> void {

        //Menu keys control
        if (currentState == State::MENU) {

            switch (key) {
                case sf::Keyboard::Up:
                    menu.up();
                    break;
                case sf::Keyboard::Down:
                    menu.down();
                    break;
                case sf::Keyboard::Return:
                    switch (menu.getCurrentIndex()) {
                        case 0:
                            game.startClock();
                            currentState = State::GAME;
                            break;
                        case 1: {
                            auto vec = game.loadGame();
                            options.setSelectedLevel(vec[0]);
                            options.setSelectedSize(vec[1]);
                            options.setSelectedFont(vec[2]);

                            currentState = State::GAME;
                            break;
                        }
                        case 2:
                            scoreboard.loadScores();
                            currentState = State::SCOREBOARD;
                            break;
                        case 3:
                            previousState = State::MENU;
                            currentState = State::OPTIONS;
                            break;
                        case 4:
                            window.close();
                            break;
                    }
                    break;

            }
        }

            //Game keys control
        else if (currentState == State::GAME) {

            //Options in game
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                previousState = State::GAME;
                currentState = State::OPTIONS;
            }

            //Save game
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                game.saveGame(options.getSelectedLevel(), options.getSelectedSize(), options.getSelectedFont());
                game.reset();
                currentState = State::MENU;
            }

            //Rage Quit
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                game.saveGame(options.getSelectedLevel(), options.getSelectedSize(), options.getSelectedFont());
                game.reset();
                window.close();
            }

        }

            //Options keys control
        else if (currentState == State::OPTIONS) {
            switch (key) {
                case sf::Keyboard::Up:
                    options.up();
                    break;

                case sf::Keyboard::Down:
                    options.down();
                    break;

                case sf::Keyboard::Return:

                    if (options.getCurrentIndex() == 0) {
                        options.setToPrevious();

                        currentState = previousState;
                    } else if (options.getCurrentIndex() == 4) {

                        game.setLevel(options.getSelectedLevel());
                        game.setSize(options.getSelectedSize());
                        game.setFont(options.getSelectedFont());

                        options.setPrevious(options.getSelectedLevel(), options.getSelectedFont(),
                                            options.getSelectedSize());
                        options.setStart();

                        currentState = previousState;
                    } else {
                        options.select();
                    }
                    break;

            }
        }

            //End keys control
        else if (currentState == State::END) {

            switch (key) {

                case sf::Keyboard::Up:
                    end.up();
                    break;
                case sf::Keyboard::Down:
                    end.down();
                    break;
                case sf::Keyboard::Return:
                    switch (end.getCurrentIndex()) {
                        case 0: {
                            std::fstream scoreboardFile(R"(..\Assets\Scoreboard.txt)",
                                                        std::ios::app);
                            if (scoreboardFile.is_open()) {
                                scoreboardFile << end.getNameString() << " " << end.getScoreCount() << '\n';
                                scoreboardFile.close();
                            } else {
                                fmt::println("Scoreboard file error");
                            }
                            end.setNameString("");
                            currentState = State::MENU;
                            break;
                        }
                        case 1:
                            end.setNameString("");
                            currentState = State::MENU;
                            break;
                    }

            }

        }

            //Scoreboard keys control
        else if (currentState == State::SCOREBOARD) {

            switch (key) {
                case sf::Keyboard::Return:
                    currentState = State::MENU;
            }

        }

    }

    auto handleTextEntered(int unicode) -> void {

        //typing in game
        if (currentState == State::GAME) {

            game.typing(unicode);

        }

        //typing to give name
        if (currentState == State::END) {

            end.typing(unicode);

        }

    }

    auto update() -> void {

        if (currentState == State::GAME) {

            auto misses = game.getMissCounter();

            game.renderWords(startX, width);

            if (misses >= 10) {
                end.setScoreCount(game.getScoreCounter());
                game.reset();
                currentState = State::END;
            }

        }

    }

    auto render() -> void {

        window.clear(sf::Color::White);

        if (currentState == State::MENU) {
            menu.draw(window);
        }

        if (currentState == State::SCOREBOARD) {
            scoreboard.draw(window);
        }

        if (currentState == State::OPTIONS) {
            options.draw(window);
        }

        if (currentState == State::GAME) {
            game.draw(window);
        }

        if (currentState == State::END) {
            end.draw(window);
        }

        window.display();
    }


public:

        GameEngine() : window(sf::VideoMode(width, height), "SpeedTyper", sf::Style::Fullscreen,
                          sf::ContextSettings(0, 0, 8)),
                   menu(width, height), game(width, height), options(width, height), end(width, height),
                   scoreboard(width, height) {

        if (!font.loadFromFile(R"(..\Assets\prstartk.ttf)")) {
            fmt::println("Error font GameEngine");
        }


        currentState = State::MENU;
        previousState = State::MENU;
    }

    auto run() -> void {

        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }

    }


};


auto main() -> int {

    GameEngine game;
    game.run();

}