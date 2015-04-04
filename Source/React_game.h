#ifndef REACT_GAME_H
#define REACT_GAME_H

#include "Game.h"
#include "Utility.h"
#include <string>
#include <memory>

class Game_board;
class Song;

class React_game : public Game {

public:
	// Initializes the reaction game with a given game board.
	React_game(std::shared_ptr<Game_board> g_board, Difficulty diff,
		       std::string song_text_notes_fname,
			   std::string song_fname);
	// Starts playing the song.
	void init_game() override;
	// Tries to fetch the information on the next note, and
	// updates the requested note if new info is available.
	void mid_game_processing() override;
	// Resets the react_game mode
	void reset() override;
	// Processes events given to it -- looks for key events specifically.
	Command_response command_switch(const sf::Event&) override;
	// Reacts to successful input.
	void respond_to_correct_input() override;
	// Reacts to unsuccessful input.
	void respond_to_incorrect_input() override;

private:
	sf::Clock button_timer;
	std::shared_ptr<Song> song_handle;
	std::shared_ptr<Game_board> g_board;
	int next_note;
	bool already_responded;
	std::string text_file_name;
	std::string song_file_name;

};

#endif