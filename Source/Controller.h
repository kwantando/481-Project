#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <string>

enum keypads_e;

// This class is designed as a main way to control the behavior of the game
// based on user inputs from the keyboard.
  
class Controller {

public:
	// This constructor creates a game controller based on the given music_filename.
	// It will create a new song object that will be buffered from that filename.
	Controller(std::string music_filename);

	// Clears dynamic memory.
	~Controller();

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

	// This function initializes or reinitializes the
	// controller to some basic state.
	void init_controller();

	// Contains the sequence that is currently requested of the user.
	std::vector<keypads_e> sequence;

	// Invariant: This iterator always points to the next expected sequence
	// value.
	std::vector<keypads_e>::iterator seq_it;

};

#endif