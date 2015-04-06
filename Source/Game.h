#ifndef GAME_H
#define GAME_H

#include "Utility.h"
#include <SFML/Graphics.hpp>

class Game_board;

// A game is a class that is responsible for interpreting user
// input according to a set of game rules defined in the design document.
// It is an abstract interface meant to be used by concrete games.

class Game {

public:

	// Creates a new game with the given difficulty.
	Game(Difficulty diff_);
	// Does everything required to initiate a game.
	virtual void init_game() = 0;
	// Performs any mid-game processing (every game "step")
	virtual void mid_game_processing() = 0;
	// Resets the game to some initial state.
	virtual void reset() = 0;
	// Represents values that can be returned as a response to a command.
	enum class Command_response {
		NO_RESPONSE,
		RESET,
		EXIT
	};
	// This function holds the game logic and how it relates to
	// user inputs (that are received as a sf::Event.)
	// In this class, it is responsible for key locking/unlocking,
	// and interpreting when a quit or reset has been entered.
	// Returns a Command_response, which can be checked by the
	// client to modify the flow of control.
	virtual Command_response command_switch(const sf::Event&);
	// Responds to a correct input of the user.
	virtual void respond_to_correct_input() = 0;
	// Responds to an incorrect input of the user.
	virtual void respond_to_incorrect_input() = 0;

	virtual ~Game() { }

protected:
	// Setter/getter for keyboard locking.
	bool was_pressed() { return pressed_lock; }
	void set_pressed(bool val) { pressed_lock = val; }

	// Lives manipulation.
	int get_lives() { return lives; }
	void dec_lives() { --lives; }
	void reset_lives();

	// Score manipulation
	int get_score() { return score; }
	void inc_score() { ++score; }
	void dec_score() { --score; }
	void reset_score() { score = 0; }
	
	Difficulty get_difficulty() { return diff; }

private:
	bool pressed_lock;	// signifies that the user has not released
						// a keyboard key yet.
	int lives;			// Lives that the user currently has.
	int score;			// Score...
	Difficulty diff;	// Difficulty of a game.
};

#endif