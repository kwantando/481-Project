#include "Game.h"
#include "Utility.h"
#include "SFML/Graphics.hpp"

using namespace sf;

const int init_lives = 5;

Game::Game(Difficulty diff_) : lives(init_lives), score(0), diff(diff_) {}

void Game::reset_lives() {
	lives = init_lives;
}

Game::Command_response Game::command_switch(const Event& event) {

	if (event.type == Event::KeyReleased) {
		pressed_lock = false;
	}
	else if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Q) {
			pressed_lock = true;
			return Command_response::EXIT;
		}
		else if (event.key.code == Keyboard::R) {
			pressed_lock = true;
			reset();	// calls most derived function.
			return Command_response::RESET;
		}
	}
	return Command_response::NO_RESPONSE;
}
