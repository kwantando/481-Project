#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <string>

class Memory_handler;
class Game_board;
// Useful keyboard key constants.
enum keypads_e {KEYPAD1 = sf::Keyboard::Up,
				KEYPAD2 = sf::Keyboard::Left,
				KEYPAD3 = sf::Keyboard::Right,
				KEYPAD4 = sf::Keyboard::Down,
				KEYPAD5 = sf::Keyboard::Space,
				KEYPAD6 = sf::Keyboard::Num6};

// This class is designed as a main way to control the behavior of the game
// based on user inputs from the keyboard.  

class Controller {

public:
	// This constructor creates a game controller based on the given music_filename.
	// It will create a new song object that will be buffered from that filename.
    Controller(std::string music_filename, std::string data_filename,
               int argc, char* argv[]);

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
	
	// Pointer to memory_handler for the song sequences.
	Memory_handler* mem_hand;

	Game_board* g_board;

	// Pointer to event/output window for the game
	sf::RenderWindow* event_window;

	// Contains the sequence that is currently requested of the user.
	std::vector<keypads_e> sequence;
	std::vector<int> note_sequence;

	// Invariant: This int iterator always points to the next expected sequence
	// value, both in sequence and note_sequence.
	int seq_it;

	// Holds the lives that the user has left in this instance
	// of the game.
	int lives;

};

#endif
