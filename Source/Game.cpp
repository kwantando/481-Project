#include "Game.h"
#include "Utility.h"
#include "SFML/Graphics.hpp"

using namespace sf;

using std::shared_ptr;

const int init_lives = 5;

// Creates a new game with the given difficulty.
Game::Game(shared_ptr<Game_board> g_board_, Difficulty diff_) : lives(init_lives), score(0), diff(diff_)
,
g_board(g_board_) {}


// This function holds the game logic and how it relates to
// user inputs (that are received as a sf::Event.)
// In this class, it is responsible for key locking/unlocking,
// and interpreting when a quit or reset has been entered.
// Returns a Command_response, which can be checked by the
// client to modify the flow of control.
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

void Game::dec_lives()
{
	lives--;
	g_board->modify_lives(lives);
}

void Game::reset_lives()
{
	lives = init_lives;
	g_board->modify_lives(lives);
}

void Game::inc_score()
{
	score++;
	g_board->modify_score(score);
}

void Game::dec_score()
{
	score--;
	g_board->modify_score(score);
}

void Game::reset_score()
{
	score = 0;
	g_board->modify_score(score);
}
