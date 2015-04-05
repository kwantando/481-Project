#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include "main_menu.h"

// Prints debug messages when set to true.
static const bool DEBUG = true;

// You can change the window size here in initialization section, along with
// the text size. Text may or may not be appropriately spaced after changing
// window_height, window_width and text_size. It looks best at 600*800 with
// a text size of 56. All units in the initialization section are pizels.
Main_menu::Main_menu() : window_height(600), window_width(800), text_size(56) {
	// Each vector holds pairs of strings and bools. The bool says whether or
	// not the string is currently highlighted on screen.
	// Exactly one bool must be true in every vector at initialization.
	mode = new std::vector< std::pair<std::string, bool> >
				 {{"Song", true}, {"Pattern", false}, {"Quit", false}};
	difficulty = new std::vector< std::pair<std::string, bool> >
				 {{"Easy", true}, {"Medium", false}, {"Hard", false},
				  {"Back", false}};
	
	// The capital L tells SFML to use wide literal strings so the
	// accented i should render correctly in the title bar (on macs, it does)
	window = new sf::RenderWindow(sf::VideoMode(window_width, window_height),
								  L"MelodiMemorí");
	
	// This is the first screen presented to the user
	render_mode();

	// Event loop that handles user input.
	sf::Event event;
	while(window->isOpen()) {
		while (window->pollEvent(event)) {
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
	delete window;
}

void Main_menu::key_event(sf::Event event) {
	if (DEBUG) std::cout << "key_event() called\n";
	switch (event.key.code) {
		case sf::Keyboard::Up:
		case sf::Keyboard::Left:
			move(mode_screen_active ? mode : difficulty, UP);
			break;
		case sf::Keyboard::Down:
		case sf::Keyboard::Right:
			move(mode_screen_active ? mode : difficulty, DOWN);
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
		if (mode->back().second) {
			window->close();
		} else {
			render_difficulty();
		}
	} else if (difficulty_screen_active) {
		if (difficulty->back().second) {
			render_mode();
		} else {
			window->close();
		}
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
			} if (i.first == "Back") {
				render_mode();
			}
		}
	}
	std::cerr << "Warning, get_difficulty returned default value\n";
	return EASY;
}

void Main_menu::render_difficulty() {
	if (DEBUG) std::cout << "render_difficulty() called\n";
	mode_screen_active = false;
	difficulty_screen_active = true;
	render(difficulty);
}

void Main_menu::render_mode() {
	if (DEBUG) std::cout << "render_mode() called\n";
	mode_screen_active = true;
	difficulty_screen_active = false;
	render(mode);
}

void Main_menu::render(std::vector< std::pair<std::string, bool> > *menu_items) {
	if (DEBUG) std::cout << "render() called\n";

	window->clear(sf::Color::Black);
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
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
			txt.setColor(sf::Color::Red);
			txt.setStyle(sf::Text::Underlined | sf::Text::Bold);
		} else {
			txt.setColor(sf::Color(122, 122, 122));
			txt.setStyle(sf::Text::Bold);
		}
		txt.setPosition( {(float)(window_width/3), (float)(border_inc)} );
		window->draw(txt);
		border_inc += text_size*2;
	}
	window->display();
}

