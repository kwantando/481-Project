#include "Controller.h"

//#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Qapplication>
#include "board_widget.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Board_Widget w;
    w.show();

	sf::Music mus;
	std::cout << mus.openFromFile("Victors.wav") << std::endl;
    #if defined _WIN32 || defined _WIN64
	Controller main_ctrl{ "Victors.wav",
                          "C:\\Users\\oleks\\Dropbox\\eecs481\\Project\\MainProjectRepo\\Source\\victors.txt" ,
                        argc, argv};
    #elif defined TARGET_OS_MAC || defined __linux__
    Controller main_ctrl{"Victors.wav", "victors.txt",
                        argc, argv};
    #endif
	main_ctrl.start_reading_input();

    return EXIT_SUCCESS;

}
