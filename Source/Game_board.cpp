#include "Game_board.h"
#include <stdexcept>
#include <sstream>
#include <string>
#include "Utility.h"

using sf::Color;
using sf::Vector2f;
using std::ostringstream;
using std::string;

const char* const score_txt_c = "Score: ";
const char* const lives_txt_c = "Lives: ";
const int starting_lives_c = 5;
const int starting_score_c = 0;
const int lives_ind_c = 0;
const int score_ind_c = 1;
const int font_size_c = 70;

#ifndef _WIN32
const char* const port_name = "/dev/tty.usbmodem1421";
#else
const char* const port_name = "COM4";
#endif

Game_board::Game_board(sf::RenderWindow*& event_ptr): light_controller(port_name)
{
	sf::VideoMode videomode = sf::VideoMode::getFullscreenModes()[0];
	win_width = videomode.width;
	win_height = videomode.height;
	event_ptr = event_window = new sf::RenderWindow(sf::VideoMode(win_width, win_height),
			                            "MelodiMemori",
			                            sf::Style::Fullscreen);
	ostringstream score_stream;
	score_stream << score_txt_c << starting_score_c;//start with 0 score
	ostringstream lives_stream;
	lives_stream << lives_txt_c << starting_lives_c;
	string lives_str{lives_stream.str()};
	string score_str{score_stream.str()};
	if (!font.loadFromFile("Phosphate.ttc")) {
		throw std::runtime_error("Failed to load font: Phosphate.ttc");
	}
	sf::Text lives{lives_str, font, (unsigned int)font_size_c};
	sf::Text score{ score_str, font, (unsigned int)font_size_c };
	lives_width = lives.getLocalBounds().width;
	score_width = score.getLocalBounds().width;
	lives.setPosition(sf::Vector2f(7 * win_width / 8,  3 * win_height/16));
	score.setPosition(sf::Vector2f(7 * win_width / 8, 11 * win_height / 16));
	text_items.push_back(lives);
	text_items.push_back(score);
	for(sf::Text& text: text_items) {
		text.setColor(text_color_c);
	}
	init_buttons();
	redraw_window();
}

Game_board::~Game_board() 
{
	delete event_window;
}

//adjust buttons by 1 for light controller
void Game_board::switch_off_button(int button)
{
	button_sprites[button].setFillColor(Color::White);
	light_controller.deactivate(button + 1);
	redraw_window();
}

void Game_board::switch_on_button(int button)
{
	button_sprites[button].setFillColor(note_colors[button]);
	light_controller.activate(button + 1);
	redraw_window();
}

void Game_board::clear_buttons()
{	
	for (int i = 0; i < 6; ++i) {
		button_sprites[i].setFillColor(Color::White);
		light_controller.deactivate(i + 1);
	}
	redraw_window();
}

void Game_board::init_buttons() 
{
	if (!button_texture.loadFromFile("button300.png",
			                             sf::IntRect(0, 0, win_width/4, win_width/4))) {
		throw std::runtime_error("Failed to load the texture");
	}
	for (int i = 0; i < 6; ++i) {
		button_sprites.push_back(sf::CircleShape(win_width / 8));
		button_sprites[i].setTexture(&button_texture);
		switch (i) {
		case 0:
			button_sprites[i].setPosition(Vector2f(0, 0));
			note_colors.push_back(Color(255, 128, 0));
			break;
		case 1:
			button_sprites[i].setPosition(Vector2f(win_width / 4, 0));
			note_colors.push_back(Color::Green);
			break;
		case 2:
			button_sprites[i].setPosition(Vector2f(win_width / 2, 0));
			note_colors.push_back(Color::Blue);
			break;
		case 3:
			button_sprites[i].setPosition(Vector2f(0, win_height / 2));
			note_colors.push_back(Color(137, 0, 255));
			break;
		case 4:
			button_sprites[i].setPosition(Vector2f(win_width / 4, win_height / 2));
			note_colors.push_back(Color::Red);
			break;
		case 5:
			button_sprites[i].setPosition(Vector2f(win_width / 2, win_height / 2));
			note_colors.push_back(Color::Yellow);
			break;
		default:
			break;
		}
	}
}


// Redraws the window based on the sprite vector/their positions/colors.
void Game_board::redraw_window() 
{

	event_window->clear(bg_color_c);

	for (sf::CircleShape& spr : button_sprites) {

		event_window->draw(spr);

	}
	for(sf::Text& text : text_items) {
		event_window->draw(text);
	}
	event_window->display();
	
}

void Game_board::modify_score(int val)
{
	modify_value(score_txt_c, val, text_items[score_ind_c]);
}

void Game_board::modify_lives(int val)
{
	modify_value(lives_txt_c, val, text_items[lives_ind_c]);
}

void Game_board::modify_value(const string &prefix, int val, sf::Text &text)
{
	ostringstream new_text_stream;
	new_text_stream << prefix << val;
	string new_text{new_text_stream.str()};
	text.setString(new_text);
	event_window->draw(text);
}

