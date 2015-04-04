#include "React_game.h"
#include "Game_board.h"
#include "songinfoparser.h"
#include "song.h"
#include "Utility.h"
#include "qdsleep.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

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

React_game::React_game(Game_board* g_board_) :
g_board(g_board_), next_note(0), already_responded(false)
{
	Song_info_parser parser{"bhc.txt"};
	song_handle = make_shared<Song>("beverlyhillscop.wav", parser, MEDIUM);
}

void React_game::init_game() {

	song_handle->play();

}
void React_game::mid_game_processing() {

	int next_note_val = song_handle->get_expected_note();

	if (next_note_val == song_over_c) {
		return;
	}

	if (button_timer.getElapsedTime() > milliseconds(500)) {
		g_board->switch_off_button(next_note);
	}

	if (next_note_val != not_new_note_c) {
		g_board->switch_on_button(next_note_val);
		button_timer.restart();
		next_note = next_note_val;
		cout << "Next note = " << next_note + 1 << endl;
		already_responded = false;
	}

}
void React_game::reset() {


}
void React_game::command_switch(const Event& event) {

	Game::command_switch(event);

	if ((event.type == Event::KeyPressed) && !was_pressed()) {
		keypads_e next_keypad = note_to_keypad(next_note);
		keypads_e keypad_pressed = static_cast<keypads_e>(event.key.code);
		//cout << "Pressed: " << keypad_pressed << endl;
		//cout << "Wanted : " << next_keypad << endl;
		if (next_keypad == keypad_pressed) {
			respond_to_correct_input();
		}
		else {
			respond_to_incorrect_input();
		}

		cout << "Your score now: " << get_score() << endl;

		set_pressed(true);
	}

}
void React_game::respond_to_correct_input() {

	if (already_responded) {
		respond_to_incorrect_input();
		return;
	}

	cout << "Entered correct note!" << endl;
	inc_score();
	already_responded = true;

}
void React_game::respond_to_incorrect_input() {

	dec_score();
	cout << "Entered bad note!" << endl;

}

React_game::~React_game() {


}