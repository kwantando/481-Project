#include "Controller.h"

//#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{

	string game_mode;
	cin >> game_mode;
    Controller main_ctrl(game_mode);
    main_ctrl.start_reading_input();

    return EXIT_SUCCESS;

}