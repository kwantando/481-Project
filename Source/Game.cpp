#include "Game.h"
#include "SFML/Graphics.hpp"

using namespace sf;

const int init_lives = 5;

Game::Game() : lives(init_lives), score(0) {}

void Game::reset_lives() {
	lives = init_lives;
}

Game::Command_response Game::command_switch(const Event& event) {

	if (event.type == Event::KeyReleased) {
		pressed_lock = false;
	}
	else if (event.type == Event::KeyPressed) {
		pressed_lock = true;
		if (event.key.code == Keyboard::Q) {
			return Command_response::EXIT;
		}
		else if (event.key.code == Keyboard::R) {
			reset();	// calls most derived function.
			return Command_response::RESET;
		}
	}
	return Command_response::NO_RESPONSE;
}
