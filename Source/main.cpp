#include "Controller.h"
#include "main_menu.h"
#include "Utility.h"

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	while (true) {
		Main_menu menu;
		Mode game_mode = menu.get_mode();
		Difficulty game_difficulty = menu.get_difficulty();
		string song_text_fname = "bhc.txt";
		string song_fname = "beverlyhillscop.wav";
		Controller main_ctrl(game_mode, game_difficulty, song_text_fname, song_fname);
		main_ctrl.start_reading_input();
	}

    return EXIT_SUCCESS;

}