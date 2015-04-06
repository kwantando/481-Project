#include "React_game.h"
#include "Game_board.h"
#include "Songinfoparser.h"
#include "Song.h"
#include "Utility.h"
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// Simply converts an integer note to the corresponding keypad.
static keypads_e note_to_keypad(int note) {

	switch (note) {
	case 0:
		return KEYPAD1;
	case 1:
		return KEYPAD2;
	case 2:
		return KEYPAD3;
	case 3:
		return KEYPAD4;
	case 4:
		return KEYPAD5;
	case 5:
		return KEYPAD6;
	default:
		throw runtime_error{"cant convert"};
	}

}

// Initializes the reaction game with a given game board,
// difficulty, and song information.
React_game::React_game(shared_ptr<Game_board> g_board_, Difficulty diff,
string song_notes_text_fname, string song_fname) :
Game(diff),
g_board(g_board_), next_note(0), already_responded(true), text_file_name(song_notes_text_fname),
song_file_name(song_fname)
{
	Song_info_parser parser{song_notes_text_fname};
	song_handle = make_shared<Song>(song_fname, parser, diff);
}

// Starts playing the song.
void React_game::init_game() {

	song_handle->play();

}

// Tries to fetch the information on the next note, and
// updates the requested note if new info is available.
void React_game::mid_game_processing() {

	int next_note_val = song_handle->get_expected_note();

	if (next_note_val == song_over_c) {
		next_note = song_over_c;
		return;
	}

	if (next_note_val != not_new_note_c) {
		//next_note_val = rand() % 6;
		if (!already_responded) {
			cout << "You missed a note!" << endl;
			dec_score();
			dec_lives();
			cout << "New lives = " << get_lives() << endl;
			cout << "New score = " << get_score() << endl;
			g_board->switch_off_button(next_note);
		}
		g_board->switch_on_button(next_note_val);
		next_note = next_note_val;
		cout << "Next note = " << next_note + 1 << endl;
		already_responded = false;
	}

}

// Resets the react_game mode
void React_game::reset() {

	song_handle->stop();
	Song_info_parser parser{ text_file_name };
	song_handle = make_shared<Song>(song_file_name, parser, get_difficulty());
	cout << "Resetting!" << endl;
	reset_lives();
	reset_score();
	already_responded = true;
	Clock reset_timer;
	while (reset_timer.getElapsedTime() < milliseconds(500));
	init_game();

}

// Checks whether the user entered any unusual commands, whether the game is
// won/lost, and then checks the user's input to see whether it is correct
// according to what we are expecting right now.
Game::Command_response React_game::command_switch(const Event& event) {

	Command_response rsp = Game::command_switch(event);

	if (rsp == Command_response::RESET || rsp == Command_response::EXIT) {
		return rsp;
	}

	if (get_lives() > 0 && next_note == song_over_c) {
		play_success_note();
		cout << "You won!\nFinal Score: " << get_score() << endl;
		Clock success_note_timer;
		while (success_note_timer.getElapsedTime() < milliseconds(500));
		return Command_response::EXIT;
	}
	else if (get_lives() <= 0) {
		song_handle->stop();
		play_fail_note();
		cout << "You lost!\nFinal Score: " << get_score() << endl;
		Clock fail_timer;
		while (fail_timer.getElapsedTime() < milliseconds(500));
		return Command_response::EXIT;
	}

	if ((event.type == Event::KeyPressed) && !was_pressed()) {

		keypads_e next_keypad = note_to_keypad(next_note);
		keypads_e keypad_pressed = static_cast<keypads_e>(event.key.code);

		if (next_keypad == keypad_pressed) {
			respond_to_correct_input();
		}
		else {
			respond_to_incorrect_input();
		}
		cout << "Your score now: " << get_score() << endl;

		set_pressed(true);
	}

	return Command_response::NO_RESPONSE;

}

// Responds to correct input.
void React_game::respond_to_correct_input() {

	// If the user already responded to this request, then this is actuall
	// an incorrect input. Treat it accordingly.
	if (already_responded) {
		respond_to_incorrect_input();
		return;
	}

	cout << "Entered correct note!" << endl;
	inc_score();
	already_responded = true;
	g_board->switch_off_button(next_note);
	
}

// Responds to incorrect input.
void React_game::respond_to_incorrect_input() {

	dec_score();
	dec_lives();
	cout << "Entered bad note!" << endl;
	cout << "Lives = " << get_lives() << endl;
	play_fail_note();

}
