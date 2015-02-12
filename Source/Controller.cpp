#include "Debug_msg.h"
#include "Controller.h"

using namespace sf;

// Useful keyboard key constants.
const auto keypad1_c = Keyboard::Q;
const auto keypad2_c = Keyboard::W;
const auto keypad3_c = Keyboard::E;
const auto keypad4_c = Keyboard::R;
const auto keypad5_c = Keyboard::T;
const auto keypad6_c = Keyboard::Y;

bool Controller::was_pressed = false;

// This function will do any preprocessing necessary before entering
// an infinite loop that reads and processes user's commands based on
// keyboard input.
void Controller::start_reading_input() {

	// Any preprocessing should go here.
	Window event_window(VideoMode(5,5), "Event_Handler_Window");

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

		switch (event.key.code) {

		case keypad1_c:
			DEBUG_MSG("keypad1 pressed.");
			break;
		case keypad2_c:
			DEBUG_MSG("keypad2 pressed.");
			break;
		case keypad3_c:
			DEBUG_MSG("keypad3 pressed.");
			break;
		case keypad4_c:
			DEBUG_MSG("keypad4 pressed.");
			break;
		case keypad5_c:
			DEBUG_MSG("keypad5 pressed.");
			break;
		case keypad6_c:
			DEBUG_MSG("keypad6 pressed.");
			break;
		default:

			break;

		}

		was_pressed = true;

	}

}