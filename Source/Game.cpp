#include "Game.h"
#include "SFML/Graphics.hpp"

using namespace sf;

const int init_lives = 5;

Game::Game() : lives(init_lives), score(0) {


}

void Game::reset_lives() {
	lives = init_lives;
}

void Game::command_switch(const Event& event) {

	if (event.type == Event::KeyReleased) {

		pressed_lock = false;

	}

}
