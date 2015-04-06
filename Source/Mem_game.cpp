#include "Mem_game.h"
#include "Memory_handler.h"
#include "Game_board.h"
#include "Utility.h"
#include <memory>
#include <iostream>

using namespace std;
using namespace sf;

// Creates a memory game using the specified game board and difficulty.
// Difficulty controls the maximum pattern length.
Mem_game::Mem_game(shared_ptr<Game_board> g_board_, Difficulty diff) :
Game(diff),
g_board(g_board_)
{
	if (get_difficulty() == EASY) {
		game_length = 10;
	}
	else if (get_difficulty() == MEDIUM) {
		game_length = 20;
	}
	else if (get_difficulty() == HARD) {
		game_length = 30;
	}
	mem_handle = make_shared<Memory_handler>(game_length);
}

// Initializes the game by grabbing the current sequence,
// playing it out, and setting up internal logic to be ready to handle
// user's input according to the pattern requested.
void Mem_game::init_game() {

	// Generate pattern and place it into the member vector.
	note_sequence = mem_handle->get_current_sequence();
	sequence = convert_int_to_keypads(note_sequence);

	// Play pattern notes.
	int button = 0;
	while ((button = mem_handle->play_next_note(*g_board)) != -1) {
		cout << "Just played " << button + 1 << " note!" << endl;
	}
	g_board->clear_buttons();
	Clock waiter_clock;
	while (waiter_clock.getElapsedTime() < milliseconds(500));

	seq_it = 0;

}

// Resets the game by resetting lives/score, and restarting a new pattern
// at the smallest length.
void Mem_game::reset() {

	reset_lives();
	reset_score();
	mem_handle.reset(new Memory_handler(game_length));
	init_game();

}

// Calls Game's command_switch and then verifies that
// the game is still valid (ie. user still alive, user hasn't won it yet)
// If so, it processes the event if it is valid and modifies the state of
// the game accordingly.
Game::Command_response Mem_game::command_switch(const Event& event) {

	Command_response rsp = Game::command_switch(event);

	if (rsp == Command_response::RESET || rsp == Command_response::EXIT) {
		return rsp;
	}

	// Has the game been lost?
	if (get_lives() <= 0) {
		mem_handle->alert_fail_note();
		cout << "You lost!" << endl;
		return Command_response::EXIT;
	}

	// Has the game been won?
	if (game_length <= seq_it) {
		mem_handle->alert_success_note();
		cout << "You won!" << endl;
		return Command_response::EXIT;
	}

	// User entered some key. Check if it is the one we expected for the pattrn.
	if ((event.type == Event::KeyPressed) && !was_pressed()) {

		if (static_cast<keypads_e>(event.key.code) == sequence[seq_it]) {
			respond_to_correct_input();
		}
		else {
			respond_to_incorrect_input();
			rsp = Command_response::RESET;
		}

		set_pressed(true);
	}

	return rsp;

}

// Responds to correct input by playing the correct note and setting
// internal logic to expect the next note pattern from the user. 
// If current pattern is exhausted, the game will request a new, longer
// one and reinitialize the game based on it.
void Mem_game::respond_to_correct_input() {

	mem_handle->play_specified_note(seq_it, false, *g_board);
	++seq_it;

	if (seq_it >= sequence.size()) {

		inc_score();
		mem_handle->next_sequence(true);
		mem_handle->alert_success_note();
		Clock waiter_clock;
		while (waiter_clock.getElapsedTime() < milliseconds(750));
		cout << "Score now: " << get_score() << endl;
		g_board->clear_buttons();
		init_game();

	}

}

// Responds to incorrect input by decreasing lives and score,
// playing the fail note, and, if the user is still alive after all that,
// reinitializing the game without increasing the length of pattern.
void Mem_game::respond_to_incorrect_input() {

	mem_handle->alert_fail_note();
	g_board->clear_buttons();
	dec_lives();
	dec_score();

	if (get_lives() > 0) {

		mem_handle->next_sequence(false);
		init_game();
		
	}

}
