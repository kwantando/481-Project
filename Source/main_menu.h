#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include "Utility.h"

enum key_pressed {
	UP,
	DOWN,
	RETURN
};

class Main_menu {
public: 
	Main_menu();
	~Main_menu();
	Mode get_mode();
	Difficulty get_difficulty();
private:
	sf::RenderWindow *window;
	std::vector< std::pair<std::string, bool> > *mode;
	std::vector< std::pair<std::string, bool> > *difficulty;
	int window_height;
	int window_width;
	int text_size;
	bool mode_screen_active;
	bool difficulty_screen_active;
	void move(std::vector< std::pair<std::string, bool> > *menu_items,
			  key_pressed direction);
	void key_event(sf::Event event);
	void render_mode();
	void render_difficulty();
	void render(std::vector< std::pair<std::string, bool> > *menu_items);
	Difficulty translate_difficulty(std::string difficulty);
	Mode translate_mode(std::string mode);
};