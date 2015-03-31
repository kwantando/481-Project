#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class Memory_handler;
class Game_board;
class Game;

// This class is designed as a main way to control the behavior of the game
// based on user inputs from the keyboard.  

class Controller {

public:
	// This constructor creates a game controller based on the given music_filename.
	// It will create a new song object that will be buffered from that filename.
    Controller(std::string game_mode);

	// Clears dynamic memory.
	~Controller();

	// This function will do any preprocessing necessary before entering
	// an infinite loop that reads and processes user's commands based on
	// keyboard input.
	void start_reading_input();

private:
	
	// Pointer to the game board.
	Game_board* g_board;

	// Pointer to event/output window for the game
	sf::RenderWindow* event_window;

	// Pointer to the current game that the controller is overseeing.
	std::shared_ptr<Game> curr_game;

};

#endif
