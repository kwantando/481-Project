#include "Debug_msg.h"
#include "Controller.h"
#include "memory_handler.h"
#include "songinfoparser.h"
#include "Game_board.h"
#include "qdsleep.h"
#include "Game.h"
#include "Mem_game.h"
#include "React_game.h"
#include "Utility.h"
#include <stdexcept>
#include <string>

using namespace sf;
using namespace std;

// This constructor creates a game controller based on the given music_filename.
Controller::Controller(Mode game_mode, Difficulty difficulty, string song_text_fname /* = "" */, string song_filename /* = "" */) : 
g_board(new Game_board(event_window)){

	if (game_mode == PATTERN) {
		curr_game.reset(new Mem_game(g_board, difficulty));
	}
	else if (game_mode == SONG) {
		curr_game.reset(new React_game(g_board, difficulty, song_text_fname, song_filename));
	}

    DEBUG_MSG("constructed successfully");
}

// This function will do any preprocessing necessary before entering
// an infinite loop that reads and processes user's commands based on
// keyboard input.
void Controller::start_reading_input() {
	
	curr_game->init_game();

    Event event;
    while (true) {
		curr_game->mid_game_processing();
		if (event_window->pollEvent(event)) {
        //if (event_window->waitEvent(event)) {   // block for initial event
            //Event tmp_ev;
            //while (event_window->pollEvent(tmp_ev));    // discard events in queue
            // This essentially disables event stacking, which does not
            // work well with the game type we have.
			Game::Command_response rsp = curr_game->command_switch(event);
			if (rsp == Game::Command_response::EXIT) {
				return;
			}
			else if (rsp == Game::Command_response::RESET) {
				while (event_window->pollEvent(event));	// discard events in queue
			}
			
        }

    }

}