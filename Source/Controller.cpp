#include "Debug_msg.h"
#include "Controller.h"
#include "memory_handler.h"
#include "beat_sequence.h"
#include "songinfoparser.h"
#include "Game_board.h"
#include "qdsleep.h"
#include <stdexcept>

using namespace sf;
using namespace std;

const int start_lives_c = 5;
const int max_notes_c = 6;

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
    g_board = new Game_board(event_window);

    DEBUG_MSG("constructed successfully");
}

// Clears dynamic memory.
Controller::~Controller() {

    delete mem_hand;
    delete g_board;
    DEBUG_MSG("destructed successfully");

}

// This function will do any preprocessing necessary before entering
// an infinite loop that reads and processes user's commands based on
// keyboard input.
void Controller::start_reading_input() {
    init_controller();

    Event event;
    while (true) {

        if (event_window->waitEvent(event)) {   // block for initial event
            Event tmp_ev;
            while (event_window->pollEvent(tmp_ev));    // discard events in queue
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

        if (event.key.code == Keyboard::R) {

            reset_controller();

        }

        else if (static_cast<keypads_e>(event.key.code) == sequence[seq_it]) {

            DEBUG_MSG("Correct input entered.");
            mem_hand->play_specified_note(seq_it, false, *g_board);
            ++seq_it;

            if (seq_it >= sequence.size()) {

                mem_hand->next_sequence(true);
                mem_hand->play_success_note();
                qdsleep(750);
                DEBUG_MSG("PATTERN SUCCESSFULLY REPEATED! Upping difficulty...");
                g_board->clear_buttons();
                init_controller();

            }

        }
        else {

            mem_hand->play_fail_note();
            g_board->clear_buttons();
            --lives;
            if (lives <= 0) {

                DEBUG_MSG("You lost!");
                reset_controller();

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
    int button = 0;
    while ((button = mem_hand->play_next_note(*g_board)) != -1) {
        cout << "Just played " << button + 1 << " note!" << endl;
    }
    g_board->clear_buttons();
    qdsleep(500);

    seq_it = 0;

}

void Controller::reset_controller() {

    delete mem_hand;
    mem_hand = new Memory_handler();
    DEBUG_MSG("Controller reset.");
    init_controller();


}