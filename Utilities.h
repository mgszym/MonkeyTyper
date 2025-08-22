#pragma once

#include <iostream>
#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <regex>
#include <fstream>

//Vector of random strings
auto generateWordsList(int size) -> std::vector<std::string>;

//Generator od sf::Texts
auto generateWord(int size, const std::string& s, sf::Font &font, float yPosition, float xPosition, float delay = 0.0f) -> sf::Text;

//Checking if word match with this in box
auto checkAndUpdateWord(sf::Text &word, sf::Text &box) -> bool;

//Checking if word crossed end line
auto checkCollision(sf::Text &word, float width) -> bool;