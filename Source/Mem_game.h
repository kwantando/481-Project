#ifndef MEM_GAME_H
#define MEM_GAME_H

#include "Game.h"
#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Memory_handler;
class Game_board;

class Mem_game : public Game {

public:
	Mem_game(std::shared_ptr<Game_board> g_board_);
	void init_game() override;
	void mid_game_processing() override {}
	void reset() override;
	Command_response command_switch(const sf::Event&) override;
	void respond_to_correct_input() override;
	void respond_to_incorrect_input() override;

private:
	std::shared_ptr<Memory_handler> mem_handle;

	std::vector<keypads_e> sequence;
	std::vector<int> note_sequence;
	std::shared_ptr<Game_board> g_board;

	int seq_it;
};

#endif