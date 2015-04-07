#include "Controller.h"
#include "Main_menu.h"
#include "Utility.h"

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	// Creates a menu window, and then start the game based on user inputs.
	while (true) {
		Main_menu menu;
		Mode game_mode = menu.get_mode();
		Difficulty game_difficulty = menu.get_difficulty();
		string song_fname = menu.get_song().first;
		string song_text_fname = menu.get_song().second;
		Controller main_ctrl(game_mode, game_difficulty,
			song_text_fname, song_fname);
		main_ctrl.start_reading_input();
	}

    return EXIT_SUCCESS;

}
