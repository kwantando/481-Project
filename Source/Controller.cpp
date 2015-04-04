#include "Debug_msg.h"
#include "Controller.h"
#include "memory_handler.h"
#include "songinfoparser.h"
#include "Game_board.h"
#include "qdsleep.h"
#include "Game.h"
#include "Mem_game.h"
#include "React_game.h"
#include <stdexcept>
#include <string>

using namespace sf;
using namespace std;

// This constructor creates a game controller based on the given music_filename.
Controller::Controller(string game_mode, string song_text_fname /* = "" */, string song_filename /* = "" */) : 
g_board(new Game_board(event_window)){

	if (game_mode == "memory") {
		curr_game.reset(new Mem_game(g_board));
	}
	else if (game_mode == "reaction") {
		curr_game.reset(new React_game(g_board, song_text_fname, song_filename));
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
			if (curr_game->command_switch(event) == Game::Command_response::EXIT) {

				return;

			}
        }

    }

}