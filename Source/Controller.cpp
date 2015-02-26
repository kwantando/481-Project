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

//returns the button_event equivalent of note and toggle
Button_Event get_button(int note, bool toggle);

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
                       int argc, char* argv[]) : qapp(argc, argv),
                       lives(start_lives_c) {

    //Song_info_parser sparser(data_filename);
    mem_hand = new Memory_handler();

    display.show();

    DEBUG_MSG("constructed successfully");
}

// Clears dynamic memory.
Controller::~Controller() {

    delete mem_hand;
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

        if (event_window.waitEvent(event)) {	// block for initial event
            Event tmp_ev;
            while (event_window.pollEvent(tmp_ev));	// discard events in queue
            // This essentially disables event stacking, which does not
            // work well with the game type we have.
            command_switch(event);
        }
        //event_window.pollEvent(event);

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
    note_sequence = mem_hand->get_current_sequence();
    sequence = convert_int_to_keypads(note_sequence);

    // Play pattern notes.
    int note = 0;
    int old_button = 0;
    while ((note = mem_hand->play_next_note()) != -1) {
        switch_off_button(old_button);
        switch_on_button(note);
        cout << "Just played " << note + 1 << " note!" << endl;
        old_button = note;
    }
    qdsleep(250);

    seq_it = 0;

}

Button_Event get_button(int note, bool toggle)
{
    if(toggle) {
        switch(note) {
            case 0:
                return Button_Event::LIGHT_TOP_LEFT;
            case 1:
                return Button_Event::LIGHT_TOP_MIDDLE;
            case 2:
                return Button_Event::LIGHT_TOP_RIGHT;
            case 3:
                return Button_Event::LIGHT_BOTTOM_LEFT;
            case 4:
                return Button_Event::LIGHT_BOTTOM_MIDDLE;
            case 5:
                return Button_Event::LIGHT_BOTTOM_RIGHT;
            default:
                throw runtime_error{"Unrecognized note found."};
        }
    }
    else {
        switch(note) {
            case 0:
                return Button_Event::CLEAR_TOP_LEFT;
            case 1:
                return Button_Event::CLEAR_TOP_MIDDLE;
            case 2:
                return Button_Event::CLEAR_TOP_RIGHT;
            case 3:
                return Button_Event::CLEAR_BOTTOM_LEFT;
            case 4:
                return Button_Event::CLEAR_BOTTOM_MIDDLE;
            case 5:
                return Button_Event::CLEAR_BOTTOM_RIGHT;
            default:
                throw runtime_error{"Unrecognized note found."};
        }
    }

}

void Controller::switch_off_button(int note)
{
    display.trigger(get_button(note, false));
}

void Controller::switch_on_button(int note)
{
    display.trigger(get_button(note, true));
}
