#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class Memory_handler;
class Game_board;
class Game;

// This class is used as a way to query and dispatch events to the game
// logic classes.

class Controller {

public:
	// This constructor creates a game controller
	// based on the given music_filename.
    Controller(Mode game_mode, Difficulty difficulty,
		std::string song_text_fname = "", std::string song_fname = "");

	// This function will do any preprocessing necessary and then will enter
	// an infinite loop that reads and processes user's commands based on
	// keyboard input. Will return if the user inputs a 
	// command that is interpreted
	// as an exit.
	void start_reading_input();

private:
	
	// Pointer to the game board.
	std::shared_ptr<Game_board> g_board;

	// Pointer to event/output window for the game
	sf::RenderWindow* event_window;

	// Pointer to the current game that the controller is overseeing.
	std::shared_ptr<Game> curr_game;

};

#endif
