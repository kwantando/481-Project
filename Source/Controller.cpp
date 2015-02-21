#include "Debug_msg.h"
#include "Controller.h"

using namespace sf;
using namespace std;

// Useful keyboard key constants.
enum keypads_e {KEYPAD1 = Keyboard::Q,
				KEYPAD2 = Keyboard::W,
				KEYPAD3 = Keyboard::E,
				KEYPAD4 = Keyboard::R,
				KEYPAD5 = Keyboard::T,
				KEYPAD6 = Keyboard::Y};

bool Controller::was_pressed = false;

// This constructor creates a game controller based on the given music_filename.
// It will create a new song object that will be buffered from that filename.
Controller::Controller(std::string music_filename){

	sequence.push_back(KEYPAD1);
	sequence.push_back(KEYPAD2);
	sequence.push_back(KEYPAD6);
	sequence.push_back(KEYPAD2);
	sequence.push_back(KEYPAD1);

	DEBUG_MSG("constructed successfully");
}

// Clears dynamic memory.
Controller::~Controller() {

	DEBUG_MSG("destructed successfully");
}

// This function will do any preprocessing necessary before entering
// an infinite loop that reads and processes user's commands based on
// keyboard input.
void Controller::start_reading_input() {

	Window event_window(VideoMode(5,5), "Event_Handler_Window");

	init_controller();

	Event event;
	while (true) {
		
		event_window.pollEvent(event);
		command_switch(event);

	}

}

// This is the switch used to process various keyboard events. It is meant
// to be called from the main while loop in start_reading_input() function.
void Controller::command_switch(const sf::Event& event) {

	if (event.type == Event::KeyReleased) {

		was_pressed = false;

	}

	else if ((event.type == Event::KeyPressed) && !was_pressed) {

		if (event.key.code == *seq_it) {

			DEBUG_MSG("Correct input entered.");
			++seq_it;

			if (seq_it == sequence.end()) {

				DEBUG_MSG("PATTERN SUCCESSFULLY REPEATED! Resetting...");
				init_controller();

			}

		}
		else {

			DEBUG_MSG("WRONG PATTERN INPUT! Resetting...");
			init_controller();

		}

		/*
		switch (event.key.code) {

		case KEYPAD1:
			DEBUG_MSG("keypad1 pressed.");
			break;
		case KEYPAD2:
			DEBUG_MSG("keypad2 pressed.");
			break;
		case KEYPAD3:
			DEBUG_MSG("keypad3 pressed.");
			break;
		case KEYPAD4:
			DEBUG_MSG("keypad4 pressed.");
			break;
		case KEYPAD5:
			DEBUG_MSG("keypad5 pressed.");
			break;
		case KEYPAD6:
			DEBUG_MSG("keypad6 pressed.");
			break;
		default:

			break;

		}
		*/

		was_pressed = true;

	}

}

void Controller::init_controller() {


	// Generate pattern and place it into the member vector.
	//...

	// Play pattern notes and block.
	//...

	seq_it = sequence.begin();

}
