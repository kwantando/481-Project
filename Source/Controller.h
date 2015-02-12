#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
// This class is designed as a main way to control the behavior of the game
// based on user inputs from the keyboard.

class Controller {

public:
	// This function will do any preprocessing necessary before entering
	// an infinite loop that reads and processes user's commands based on
	// keyboard input.
	void start_reading_input();

private:
	// This is a latch variable that ensures each key press only produces 
	// one execution of the corresponding action.
	static bool was_pressed;

	// This is the switch used to process various keyboard events. It is meant
	// to be called from the main while loop in start_reading_input() function.
	void command_switch(const sf::Event&);
};

#endif