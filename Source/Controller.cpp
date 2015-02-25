#include "Debug_msg.h"
#include "Controller.h"
#include "memory_handler.h"
#include "beat_sequence.h"
#include "songinfoparser.h"
#include "qdsleep.h"
#include <stdexcept>

using namespace sf;
using namespace std;

const int start_lives_c = 5;

bool Controller::was_pressed = false;

static vector<keypads_e> convert_int_to_keypads(const vector<int>& vc);



static vector<keypads_e> convert_int_to_keypads(const vector<int>& vc) {

	vector<keypads_e> retvec;

	for (const int& val : vc) {

		keypads_e key_val;

		switch (val) {

		case 0:
			key_val = KEYPAD1;
			break;
		case 1:
			key_val = KEYPAD2;
			break;
		case 2:
			key_val = KEYPAD3;
			break;
		case 3:
			key_val = KEYPAD4;
			break;
		case 4:
			key_val = KEYPAD5;
			break;
		case 5:
			key_val = KEYPAD6;
			break;
		default:
			DEBUG_MSG("ERROR. Incorrect value found in sequence.");

		}

		retvec.push_back(key_val);

	}

	return retvec;
}

// This constructor creates a game controller based on the given music_filename.
// It will create a new song object that will be buffered from that filename.
Controller::Controller(std::string music_filename, std::string data_filename,
                       int argc, char* argv[]) : 
					   lives(start_lives_c) {

	mem_hand = new Memory_handler();
	event_window = new RenderWindow(VideoMode(150, 100),
		                            "Event_Handler_Window");

	if (!button_texture.loadFromFile("../Resources/button.png",
		                             IntRect(0, 0, 100, 100))) {

		throw exception("Failed to load the texture");

	}

	for (int i = 0; i < 6; ++i) {

		button_sprites.push_back(Sprite(button_texture));

		switch (i) {
		case 0:
			button_sprites[i].setPosition(Vector2f(0, 0));
			note_colors.push_back(Color::Red);
			break;
		case 1:
			button_sprites[i].setPosition(Vector2f(50, 0));
			note_colors.push_back(Color::Green);
			break;
		case 2:
			button_sprites[i].setPosition(Vector2f(100, 0));
			note_colors.push_back(Color::Blue);
			break;
		case 3:
			button_sprites[i].setPosition(Vector2f(0, 50));
			note_colors.push_back(Color::Yellow);
			break;
		case 4:
			button_sprites[i].setPosition(Vector2f(50, 50));
			note_colors.push_back(Color::Magenta);
			break;
		case 5:
			button_sprites[i].setPosition(Vector2f(100, 50));
			note_colors.push_back(Color::Cyan);
			break;
		default:
			break;
		}


	}


	DEBUG_MSG("constructed successfully");
}

// Clears dynamic memory.
Controller::~Controller() {

	delete mem_hand;
	delete event_window;
	DEBUG_MSG("destructed successfully");

}

// This function will do any preprocessing necessary before entering
// an infinite loop that reads and processes user's commands based on
// keyboard input.
void Controller::start_reading_input() {

//	ball6.setColor(sf::Color(0, 255, 0)); // green
//	event_window->display();
	redraw_window();

	init_controller();

	Event event;
	while (true) {

		if (event_window->waitEvent(event)) {	// block for initial event
			Event tmp_ev;
			while (event_window->pollEvent(tmp_ev));	// discard events in queue
			// This essentially disables event stacking, which does not
			// work well with the game type we have.
			command_switch(event);
		}

	}

}

// This is the switch used to process various keyboard events. It is meant
// to be called from the main while loop in start_reading_input() function.
void Controller::command_switch(const sf::Event& event) {

	if (event.type == Event::KeyReleased) {

		was_pressed = false;

	}

	else if ((event.type == Event::KeyPressed) && !was_pressed) {

		if (static_cast<keypads_e>(event.key.code) == sequence[seq_it]) {

			DEBUG_MSG("Correct input entered.");
			mem_hand->play_specified_note(seq_it, false);
			++seq_it;

			if (seq_it >= sequence.size()) {

				mem_hand->next_sequence(true);
				DEBUG_MSG("PATTERN SUCCESSFULLY REPEATED! Upping difficulty...");
				init_controller();

			}

		}
		else {

			--lives;
			if (lives <= 0) {

				mem_hand->play_fail_note();
				DEBUG_MSG("You lost!");
				exit(0);

			}

			mem_hand->next_sequence(false);
			DEBUG_MSG("WRONG PATTERN INPUT! Resetting...");
			init_controller();

		}

		was_pressed = true;

	}

}

void Controller::init_controller() {


	// Generate pattern and place it into the member vector.
	note_sequence = mem_hand->get_current_sequence();
	sequence = convert_int_to_keypads(note_sequence);

	// Play pattern notes.
	int note = 0;
    int old_button = 0;
	while ((note = mem_hand->play_next_note()) != -1) {
		button_sprites[note].setColor(note_colors[note]);
		button_sprites[old_button].setColor(Color::White);
		redraw_window();
        cout << "Just played " << note + 1 << " note!" << endl;
        old_button = note;
	}
	button_sprites[old_button].setColor(Color::White);
	redraw_window();
	qdsleep(250);

	seq_it = 0;

}

// Redraws the window based on the sprite vector/their positions/colors.
void Controller::redraw_window() {

	event_window->clear();

	for (Sprite& spr : button_sprites) {

		event_window->draw(spr);

	}

	event_window->display();
	
}