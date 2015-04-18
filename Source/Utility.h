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
//plays the note to indicate a correct sequence was entered
void play_success_note();
//plays the note to indicate an incorrect sequence was entered
void play_fail_note();
//holds until ms millisecs have elapsed
void qdsleep(int ms);

std::vector<keypads_e> convert_int_to_keypads(const std::vector<int>& vc);
const int default_note_wait_c = 300;
const char* const notes_dir_c = "Notes/";

const sf::Color bg_color_c(14, 26, 97);
const sf::Color text_color_c(222, 199, 29);
const sf::Color unselected_text_color_c(122, 122, 122);

#endif