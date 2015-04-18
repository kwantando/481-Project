#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include "Utility.h"

// The relevant keystrokes processed by Main_menu.
enum Key_pressed {
	UP,
	DOWN,
	RETURN
};

// This class displays the setup screen for the user to select
// the mode and difficulty they prefer

class Main_menu {
public: 
	Main_menu();
	~Main_menu();
	// Getters used by main.cpp to run the game with the user selected
	// mode and difficulty
	Mode get_mode();
	Difficulty get_difficulty();
	std::pair<std::string, std::string> get_song();
private:
	// A GUI window
	sf::RenderWindow *window;
	// The melodiMemori logo
	sf::Texture *logo;
	// Window's dimensions
	int window_height;
	int window_width;
	// Each is a separate screen that the user will
	// interface with
	std::vector< std::pair<std::string, bool> > *mode;
	std::vector< std::pair<std::string, bool> > *difficulty;
	std::vector< std::pair<std::string, bool> > *songs;

	int text_size;
	// Which screen is currently being displayed
	bool mode_screen_active;
	bool difficulty_screen_active;
	bool song_screen_active;
	// Allows menus with any number of user selectable options to be added
	// to the window, automatically looping to the top or bottom if necessary.
	void move(std::vector< std::pair<std::string, bool> > *menu_items,
			  Key_pressed direction);
	// Calls move() when the user hits an arrow key, calls return_key()
	// when the User hits the return key.
	void key_event(sf::Event event);
	// Switches between screens by calling render_mode() or
	// render_difficulty(). Closes the window if the user quits or makes
	// their selection on render_difficulty.
	void return_key();
	// These three functions set the appropriate *_screen_active bools before
	// calling render().
	void render_mode();
	void render_difficulty();
	void render_songs();
	// Changes the colors of the menu_items. Spaces each menu item
	// in an easy to read format. 
	void render(std::vector< std::pair<std::string, bool> > *menu_items);
	// Positions the logo nicely.
	void show_logo();
};