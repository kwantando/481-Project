#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Graphics.hpp>
#include <vector>

enum keypads_e {
	KEYPAD1 = sf::Keyboard::Num1,
	KEYPAD2 = sf::Keyboard::Num2,
	KEYPAD3 = sf::Keyboard::Num3,
	KEYPAD4 = sf::Keyboard::Num4,
	KEYPAD5 = sf::Keyboard::Num5,
	KEYPAD6 = sf::Keyboard::Num6
};

enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

enum Mode {
	SONG,
	PATTERN
};

std::vector<keypads_e> convert_int_to_keypads(const std::vector<int>& vc);


#endif