#ifndef MEM_GAME_H
#define MEM_GAME_H

#include "Game.h"
#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Memory_handler;
class Game_board;

// Mem_game is a Game that gives the user a pattern that he has to repeat.
// Pattern's length increases with time.

class Mem_game : public Game {

public:
	// Creates a memory game using the specified game board and difficulty.
	// Difficulty controls the maximum pattern length.
	Mem_game(std::shared_ptr<Game_board> g_board_, Difficulty diff);
	// Initializes the game by grabbing the current sequence,
	// playing it out, and setting up internal logic to be ready to handle
	// user's input according to the pattern requested.
	void init_game() override;
	// Does nothing for this type of Game.
	void mid_game_processing() override {}
	// Resets the game by resetting lives/score, and restarting a new pattern
	// at the smallest length.
	void reset() override;
	// Calls Game's command_switch and then verifies that
	// the game is still valid (ie. user still alive, user hasn't won it yet)
	// If so, it processes the event if it is valid and modifies the state of
	// the game accordingly.
	Command_response command_switch(const sf::Event&) override;
	// Responds to correct input by playing the correct note and setting
	// internal logic to expect the next note pattern from the user. 
	// If current pattern is exhausted, the game will request a new, longer
	// one and reinitialize the game based on it. It will also
	// play a success note.
	void respond_to_correct_input() override;
	// Responds to incorrect input by decreasing lives and score,
	// playing the fail note, and, if the user is still alive after all that,
	// reinitializing the game without increasing the length of pattern.
	void respond_to_incorrect_input() override;

private:
	// Handle to the memory_handler, which is responsible for generating and
	// providing the patterns for this game mode.
	std::shared_ptr<Memory_handler> mem_handle;

	// Holds the sequence we want in keypads.
	std::vector<keypads_e> sequence;
	// Holds the pattern in note (ints) representation.
	std::vector<int> note_sequence;

	int seq_it;		// Points to the current place in the sequence.
	int game_length;// Signifies the max length of the pattern.
};

#endif