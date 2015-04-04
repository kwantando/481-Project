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
	// Create a controller for a game defined by game_mode 
	// ("reaction" or "memory")
	// Optionally takes the song's text file name and song file name,
	// which are needed for the reaction game mode.
    Controller(std::string game_mode,
		std::string song_text_fname = "", std::string song_fname = "");

	// This function will do any preprocessing necessary before entering
	// an infinite loop that reads and processes user's commands based on
	// keyboard input.
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
