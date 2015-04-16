#ifndef GAME_BOARD_H
#define GAME_BOARD_H

//#include "Light_cont.h"
#include <SFML/Graphics.hpp>

class Game_board {
public:
	Game_board(sf::RenderWindow*& event);
	~Game_board();

	//switches the button to no color
    void switch_off_button(int button);

    //switches the button to color
    void switch_on_button(int button);

    //clear all button colors
	void clear_buttons();
private:
	// Pointer to event/output window for the game.
	sf::RenderWindow* event_window;

	// Textures
	sf::Texture button_texture;

	// Sprite container
	std::vector<sf::CircleShape> button_sprites;

	// Note color container
	std::vector<sf::Color> note_colors;

	// This controls the lights on the game board.
	//Light_cont light_controller;

	// Sets up buttons in correct places.
	void init_buttons();
	
	// Redraws the window based on the sprite vector/their positions/colors.
	void redraw_window();

	int win_width;
	int win_height;
};

#endif
