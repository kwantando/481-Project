#include "Controller.h"
#include "Memory_handler.h"
#include "Songinfoparser.h"
#include "Game_board.h"
#include "Game.h"
#include "Mem_game.h"
#include "React_game.h"
#include "Utility.h"
#include <stdexcept>
#include <string>

using namespace sf;
using namespace std;

// This constructor creates a game controller based on the given music_filename.
Controller::Controller(Mode game_mode, Difficulty difficulty,
	string song_text_fname /* = "" */, string song_filename /* = "" */) : 
g_board(new Game_board(event_window)){

	if (game_mode == PATTERN) {
		curr_game.reset(new Mem_game(g_board, difficulty));
	}
	else if (game_mode == SONG) {
		curr_game.reset(new React_game(g_board, difficulty,
			song_text_fname, song_filename));
	}

}

// This function will do any preprocessing necessary and then will enter
// an infinite loop that reads and processes user's commands based on
// keyboard input. Will return if the user inputs a command that is interpreted
// as an exit.
void Controller::start_reading_input() {
	
	curr_game->init_game();

    while (true) {

		Event event;
		curr_game->mid_game_processing();
		event_window->pollEvent(event);	// if no interesting event is caught
										// the command_switch wont act on it.
		Game::Command_response rsp = curr_game->command_switch(event);
		if (rsp == Game::Command_response::EXIT) {
			return;
		}
		else if (rsp == Game::Command_response::RESET) {
			while (event_window->pollEvent(event));	// discard events in queue
		}

    }

}

