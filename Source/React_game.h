#ifndef REACT_GAME_H
#define REACT_GAME_H

#include "Game.h"
#include "Utility.h"
#include <memory>

class Game_board;
class Song;

class React_game : public Game {

public:
	// Initializes the reaction game with a given game board.
	React_game(Game_board* g_board);
	// Starts playing the song.
	void init_game() override;
	// Tries to fetch the information on the next note, and
	// updates the requested note if new info is available.
	void mid_game_processing() override;
	// Resets the react_game mode
	void reset() override;
	// Processes events given to it -- looks for key events specifically.
	void command_switch(const sf::Event&) override;
	// Reacts to successful input.
	void respond_to_correct_input() override;
	// Reacts to unsuccessful input.
	void respond_to_incorrect_input() override;

	~React_game();

private:
	sf::Clock button_timer;
	std::shared_ptr<Song> song_handle;
	Game_board* g_board;
	int next_note;
	bool already_responded;

};

#endif