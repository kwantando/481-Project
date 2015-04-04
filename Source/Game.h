#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game_board;

class Game {

public:
	Game();
	virtual void init_game() = 0;
	virtual void mid_game_processing() = 0;
	virtual void reset() = 0;
	enum class Command_response {
		NO_RESPONSE,
		RESET,
		EXIT
	};
	virtual Command_response command_switch(const sf::Event&);
	virtual void respond_to_correct_input() = 0;
	virtual void respond_to_incorrect_input() = 0;

	virtual ~Game() { }

protected:
	bool was_pressed() { return pressed_lock; }
	void set_pressed(bool val) { pressed_lock = val; }

	int get_lives() { return lives; }
	void dec_lives() { --lives; }
	void reset_lives();

	int get_score() { return score; }
	void inc_score() { ++score; }
	void dec_score() { --score; }
	void reset_score() { score = 0; }

private:
	bool pressed_lock;
	int lives;
	int score;
};

#endif