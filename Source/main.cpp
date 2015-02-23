#include "Controller.h"

//#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{

	sf::Music mus;
	std::cout << mus.openFromFile("Victors.wav") << std::endl;

	Controller main_ctrl{ "Victors.wav",
						  "C:\\Users\\oleks\\Dropbox\\eecs481\\Project\\MainProjectRepo\\Source\\victors.txt" };
	main_ctrl.start_reading_input();

    return EXIT_SUCCESS;

}
