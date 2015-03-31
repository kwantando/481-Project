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
	virtual void command_switch(const sf::Event&);
	virtual void respond_to_correct_input() = 0;
	virtual void respond_to_incorrect_input() = 0;

	virtual ~Game() = 0;

protected:
	bool was_pressed() { return pressed_lock; }
	void set_pressed(bool val) { pressed_lock = val; }
	int get_lives() { return lives; }
	void dec_lives() { --lives; }
	void reset_lives();

private:
	bool pressed_lock;
	int lives;
};

#endif