#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include "Main_menu.h"

// Prints debug messages when set to true.
static const bool DEBUG = false;
using std::cout;
using std::endl;

// Text size is in pixels.
Main_menu::Main_menu() : text_size(56) {
	sf::VideoMode videomode = sf::VideoMode::getFullscreenModes()[0];
	window_width = videomode.width;
	window_height = videomode.height;

	// Each vector holds pairs of strings and bools. The bool says whether or
	// not the string is currently highlighted on screen.
	// Exactly one bool must be true in every vector at initialization.
	mode = new std::vector< std::pair<std::string, bool> >
			   {{"Song", true}, {"Pattern", false}, {"Tutorial", false},
			   {"Quit", false}};
   	songs = new std::vector< std::pair<std::string, bool> >
				{{"Victors", true}, {"Techno Jig", false},
				{"Axel F", false}, {"Back", false}};
	difficulty = new std::vector< std::pair<std::string, bool> >
				 	 {{"Easy", true}, {"Medium", false}, {"Hard", false},
				  	 {"Back", false}};
	
	// The capital L tells SFML to use wide literal strings so the
	// accented i should render correctly in the title bar (on macs, it does)
	window = new sf::RenderWindow(sf::VideoMode(window_width, window_height),
								  L"MelodiMemorí", sf::Style::Fullscreen);
	window->setMouseCursorVisible(false);

	// This is the first screen presented to the user
	render_mode();
	// Event loop that handles user input.
	sf::Event event;
	while(window->isOpen()) {
		window->setActive();
		while (window->waitEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window->close();
					break;
				case sf::Event::KeyPressed:
					key_event(event);
					break;
				default:
					break;
			}
		}
	}
}

Main_menu::~Main_menu() {
	delete mode;
	delete difficulty;
	delete songs;
	delete window;
	delete logo;
}

void Main_menu::key_event(sf::Event event) {
	if (DEBUG) std::cout << "key_event() called\n";
	switch (event.key.code) {
		case sf::Keyboard::Up:
		case sf::Keyboard::Left:
			if (mode_screen_active) {
				move(mode, UP);
			} else if (difficulty_screen_active) {
				move(difficulty, UP);
			} else if (song_screen_active) {
				move(songs, UP);
			}
			//move(mode_screen_active ? mode : difficulty, UP);
			break;
		case sf::Keyboard::Down:
		case sf::Keyboard::Right:
			//move(mode_screen_active ? mode : difficulty, DOWN);
			if (mode_screen_active) {
				move(mode, DOWN);
			} else if (difficulty_screen_active) {
				move(difficulty, DOWN);
			} else if (song_screen_active) {
				move(songs, DOWN);
			}
			break;
		case sf::Keyboard::Return:
			return_key();
			break;
		default:
			// do nothing if some other key is pressed
			break;
	}
}

void Main_menu::return_key() {
	if (DEBUG) std::cout << "return_key() called\n";
	// The last item in a vector is either the quit button
	// or the back button. Hence checking *->back().second
	if (mode_screen_active) {
		auto mode_itr = mode->begin();
		++mode_itr;
		++mode_itr;
		if (mode->back().second) { // if quit button selected
			window->close();
		} else if (mode->begin()->second) { // if song is highlighted
			render_songs();
		} else if (mode_itr->second) {
			render_instructions();
		} else { // if pattern is selected
			render_difficulty();
		}
	} else if (song_screen_active) {
		if (songs->back().second) { // if back button is selected
			render_mode(); // go back to the home screen
		} else {
			render_difficulty(); // if a song is selected, go to the difficulty screen
		}
	} else if (difficulty_screen_active) {
		if (difficulty->back().second) {
			render_mode();
		} else {
			window->close();
		}
	} else if (instructions_screen_active) {
		render_mode();
	}
}

void Main_menu::move(std::vector< std::pair<std::string, bool> > *menu_items,
					 Key_pressed direction) {
	if (DEBUG) std::cout << "move() called\n";
	if (menu_items->size() > 1) {
		for (auto i = menu_items->begin(); i != menu_items->end(); i++) {
			if (i->second == true) {
				i->second = false;
				if (direction == UP) {
					if (i != menu_items->begin()) {
						--i;
					} else {
						i = menu_items->end();
						i--;
					}
				} else if (direction == DOWN) {
					auto j = i;
					j++;
					if (j == menu_items->end()) {
						i = menu_items->begin();
					} else {
						++i;
					}
				}
				i->second = true;
				render(menu_items);
				break;
			}
		}
	}
}

Mode Main_menu::get_mode() {
	if (DEBUG) std::cout << "get_mode() called\n";
	for (auto i : *mode) {
		if (i.second) {
			if (i.first == "Pattern") {
				return PATTERN;
			}
			if (i.first == "Song") {
				return SONG;
			}
			if (i.first == "Quit") {
				std::cerr << "User ended program\n";
				exit(0);
			}
		}
	}
	std::cerr << "Warning, get_mode returned default value\n";
	return PATTERN;
}

Difficulty Main_menu::get_difficulty() {
	for (auto i : *difficulty) {
		if (i.second) {
			if (i.first == "Easy") {
				return EASY;
			} if (i.first == "Medium") {
				return MEDIUM;
			} if (i.first == "Hard") {
				return HARD;
			}
		}
	}
	std::cerr << "Warning, get_difficulty returned default value\n";
	return EASY;
}

std::pair<std::string, std::string> Main_menu::get_song() {
	for (auto i : *songs) {
		if (i.second) {
			if (i.first == "Victors") {
				return std::pair<std::string, std::string> {"Victors.ogg",
															"Victors.txt"};
			} else if (i.first == "Techno Jig") {
				return std::pair<std::string, std::string> {"Techno_jig.ogg",
															"Techno_jig.txt"};
			} else if (i.first == "Axel F") {
				return std::pair<std::string, std::string> {"beverlyhillscop.ogg",
															"bhc_more_notes.txt"};
			}
		}
	}
	std::cerr << "Warning, get_song returned default value\n";
	return std::pair<std::string, std::string> {"Victors.ogg", "Victors.txt"};
}

void Main_menu::render_songs() {
	if (DEBUG) std::cout << "render_songs() called\n";
	mode_screen_active = false;
	difficulty_screen_active = false;
	song_screen_active = true;
	instructions_screen_active = false;
	render(songs);
}

void Main_menu::render_difficulty() {
	if (DEBUG) std::cout << "render_difficulty() called\n";
	mode_screen_active = false;
	difficulty_screen_active = true;
	song_screen_active = false;
	instructions_screen_active = false;
	render(difficulty);
}

void Main_menu::render_mode() {
	if (DEBUG) std::cout << "render_mode() called\n";
	mode_screen_active = true;
	difficulty_screen_active = false;
	song_screen_active = false;
	instructions_screen_active = false;
	render(mode);
}

void Main_menu::render_instructions()
{
	window->clear(bg_color_c);
	sf::Font font;
	if(!font.loadFromFile("Arial.ttf")) {
		std::cerr << "Unable to load Arial font" << endl;
	}
	sf::Text text;
	text.setFont(font);
	text.setString("The instructions for running this program can be found at InstructionVideo.ogg,\nin the same folder you found this program. Enjoy!\nPress enter to return to the menu.");
	text.setCharacterSize(30);
	text.setColor(text_color_c);
	text.setStyle(sf::Text::Bold);
	text.setPosition({float(window_width/4), float(window_height / 2)});
	window->draw(text);
	instructions_screen_active = true;
	mode_screen_active = false;
	difficulty_screen_active = false;
	song_screen_active = false;
	window->display();
}

void Main_menu::render(std::vector< std::pair<std::string, bool> > *menu_items) {
	if (DEBUG) std::cout << "render() called\n";
	window->clear(bg_color_c);
	
	// *************************** options list ***************************
	sf::Font font;
	if (!font.loadFromFile("Phosphate.ttc")) {
		std::cerr << "could not load font\n";
	}
	// the empty space between top and bottom of options list
	int border_size = window_height - (text_size * menu_items->size());
	if(menu_items->size() > 1) border_size -= (text_size * menu_items->size()-1);
	border_size /= 2;
	// the space between options
	int border_inc = border_size;
	for (auto i = menu_items->begin(); i != menu_items->end(); i++) {
		sf::Text txt;
		txt.setFont(font);
		txt.setString(i->first);
		txt.setCharacterSize(text_size);
		if (i->second) {
			txt.setColor(text_color_c);
			txt.setStyle(sf::Text::Underlined | sf::Text::Bold);
		} else {
			txt.setColor(unselected_text_color_c);
			txt.setStyle(sf::Text::Bold);
		}
		// the horizontal position of the text
		txt.setPosition( {(float)(window_width/2), (float)(border_inc)} );
		window->draw(txt);
		border_inc += text_size*2;
	}

	// *************************** logo ***************************
	logo = new sf::Texture;
	if (!logo->loadFromFile("MelodiMemori_logo_with_alpha.png")) {
		std::cerr << "Could not load logo texture\n";
	}
	logo->setSmooth(true);
	sf::Sprite logo_sprite;
	logo_sprite.setTexture(*logo);
	
	double logo_width = window_width/2;
	logo_width -= window_width/8; // to give some space on the sides 

	// 612.0/792.0 is the width divided by the height of the original logo
	// texture. It is used to keep the constraints of the image when scaling.
	double logo_height = ((612.0/792.0)*logo_width);

	// The coordinates of the top left corner of the sprite.
	double logo_x_pos = window_width/16; // "space on the sides" divisor * 2
	double logo_y_pos = (window_height - logo_height)/2;

	logo_sprite.setPosition(logo_x_pos, logo_y_pos);

	// Dividing the new logo height and width by their original values gives
	// you a scale factor, which is the only way to resize sprites.
	logo_sprite.scale((logo_width/792.0), (logo_height/612.0));
	window->draw(logo_sprite);
	window->display();
}

