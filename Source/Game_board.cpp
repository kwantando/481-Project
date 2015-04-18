#include "Game_board.h"
//#include "Light_cont.h"
#include <stdexcept>
#include <sstream>
#include <string>
#include "Utility.h"

using sf::Color;
using sf::Vector2f;
using std::ostringstream;
using std::string;

const int margin_size_c = 30;
const int border_size_c = 10;
const int sprite_size_c = 300;
const char* const score_txt_c = "Score: ";
const char* const lives_txt_c = "Lives: ";
const int starting_lives_c = 5;
const int starting_score_c = 0;
const int lives_ind_c = 0;
const int score_ind_c = 1;


Game_board::Game_board(sf::RenderWindow*& event_ptr):
win_width(win_width_c), win_height(win_height_c)
//light_controller("/dev/tty.usbmodem1421")
{
	event_ptr = event_window = new sf::RenderWindow(sf::VideoMode(win_width, win_height),
			                            "MelodiMemori",
			                            sf::Style::Fullscreen);

	if (!button_texture.loadFromFile("button300.png",
			                             sf::IntRect(0, 0, sprite_size_c, sprite_size_c))) {
		throw std::runtime_error("Failed to load the texture");
	}
	ostringstream score_stream;
	score_stream << score_txt_c << starting_score_c;//start with 0 score
	ostringstream lives_stream;
	lives_stream << lives_txt_c << starting_lives_c;
	string lives_str{lives_stream.str()};
	string score_str{score_stream.str()};
	if (!font.loadFromFile("arial.ttf")) {
		throw std::runtime_error("Failed to load font: arial.ttf");
	}
	sf::Text lives{lives_str, font};
	sf::Text score{score_str, font};
	score.setPosition(Vector2f(0, 0));
	lives.setPosition(Vector2f(win_width - sprite_size_c, 0));
	text_items.push_back(lives);
	text_items.push_back(score);
	for(sf::Text& text: text_items) {
		text.setColor(sf::Color::Red);
	}
	init_buttons();
	redraw_window();
}

Game_board::~Game_board() 
{
	delete event_window;
}


void Game_board::switch_off_button(int button)
{
	button_sprites[button].setFillColor(Color::White);
	//light_controller.deactivate(button);
	redraw_window();
}

void Game_board::switch_on_button(int button)
{
	button_sprites[button].setFillColor(note_colors[button]);
	//light_controller.activate(button);
	redraw_window();
}

void Game_board::clear_buttons()
{	
	for (int i = 0; i < 6; ++i) {
		button_sprites[i].setFillColor(Color::White);
		//light_controller.deactivate(i);
	}
	redraw_window();
}

void Game_board::init_buttons() 
{
	for (int i = 0; i < 6; ++i) {
		button_sprites.push_back(sf::CircleShape(sprite_size_c/2.0));///2 for rad
		button_sprites[i].setTexture(&button_texture);
		switch (i) {
		case 0:
			button_sprites[i].setPosition(Vector2f(margin_size_c, margin_size_c));
			note_colors.push_back(Color::Red);
			break;
		case 1:
			button_sprites[i].setPosition(Vector2f(sprite_size_c + margin_size_c + border_size_c, margin_size_c));
			note_colors.push_back(Color::Green);
			break;
		case 2:
			button_sprites[i].setPosition(Vector2f((2 * sprite_size_c) + margin_size_c + (2 * border_size_c), margin_size_c));
			note_colors.push_back(Color::Blue);
			break;
		case 3:
			button_sprites[i].setPosition(Vector2f(margin_size_c, sprite_size_c + margin_size_c + border_size_c));
			note_colors.push_back(Color::Yellow);
			break;
		case 4:
			button_sprites[i].setPosition(Vector2f(sprite_size_c + margin_size_c + border_size_c, sprite_size_c + margin_size_c + border_size_c));
			note_colors.push_back(Color::Magenta);
			break;
		case 5:
			button_sprites[i].setPosition(Vector2f((2 * sprite_size_c) + margin_size_c + (2 * border_size_c), sprite_size_c + margin_size_c + border_size_c));
			note_colors.push_back(Color::Cyan);
			break;
		default:
			break;
		}
	}
}


// Redraws the window based on the sprite vector/their positions/colors.
void Game_board::redraw_window() 
{

	event_window->clear();

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

