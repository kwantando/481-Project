#include "Mem_game.h"
#include "memory_handler.h"
#include "Game_board.h"
#include "Utility.h"
#include "Debug_msg.h"
#include <memory>
#include <iostream>

using namespace std;
using namespace sf;

const int default_start_len_c = 20;

Mem_game::Mem_game(shared_ptr<Game_board> g_board_, Difficulty diff) :
Game(diff),
mem_handle(new Memory_handler(default_start_len_c)),
g_board(g_board_)
{

}

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

void Mem_game::reset() {

	reset_lives();
	reset_score();
	mem_handle.reset(new Memory_handler());
	DEBUG_MSG("Controller reset.");
	init_game();

}

Game::Command_response Mem_game::command_switch(const Event& event) {

	Command_response rsp = Game::command_switch(event);

	if (rsp == Command_response::RESET || rsp == Command_response::EXIT) {
		return rsp;
	}

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

void Mem_game::respond_to_correct_input() {

	DEBUG_MSG("Correct input entered.");
	mem_handle->play_specified_note(seq_it, false, *g_board);
	++seq_it;

	if (seq_it >= sequence.size()) {

		inc_score();
		mem_handle->next_sequence(true);
		mem_handle->alert_success_note();
		Clock waiter_clock;
		while (waiter_clock.getElapsedTime() < milliseconds(750));
		cout << "Score now: " << get_score() << endl;
		DEBUG_MSG("PATTERN SUCCESSFULLY REPEATED! Upping difficulty...");
		g_board->clear_buttons();
		init_game();

	}

}

void Mem_game::respond_to_incorrect_input() {

	mem_handle->alert_fail_note();
	g_board->clear_buttons();
	dec_lives();
	dec_score();
	if (get_lives() <= 0) {

		DEBUG_MSG("You lost!");
		reset();

	}
	else {

		mem_handle->next_sequence(false);
		DEBUG_MSG("WRONG PATTERN INPUT! Resetting...");
		init_game();
		
	}

}