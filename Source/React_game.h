#ifndef REACT_GAME_H
#define REACT_GAME_H

#include "Game.h"
#include "Utility.h"
#include <string>
#include <memory>

class Game_board;
class Song;

// React_game is a Game that plays the given song in the background and
// requests the user to quickly press keypads as they light up in
// tandem with the song.

class React_game : public Game {

public:
	// Initializes the reaction game with a given game board,
	// difficulty, and song information.
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
	// Checks whether the user entered any unusual commands, whether the game is
	// won/lost, and then checks the user's input to see whether it is correct
	// according to what we are expecting right now.
	Command_response command_switch(const sf::Event&) override;
	// Reacts to successful input.
	void respond_to_correct_input() override;
	// Reacts to unsuccessful input.
	void respond_to_incorrect_input() override;

private:
	// This holds the song_handle that is responsible for music control
	// and note requests.
	std::shared_ptr<Song> song_handle;
	// This game mode uses a game_board.
	std::shared_ptr<Game_board> g_board;
	// Holds the next note that we want user to input.
	int next_note;
	// Lock to ensure that multiple presses of currently requested
	// note are penalized.
	bool already_responded;
	// These hold song information.
	std::string text_file_name;
	std::string song_file_name;

};

#endif