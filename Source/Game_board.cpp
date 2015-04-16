#include "Game_board.h"
//#include "Light_cont.h"
#include <stdexcept>

using sf::Color;
using sf::Vector2f;

const int margin_size_c = 10;
const int border_size_c = 10;
const int sprite_size_c = 300;

Game_board::Game_board(sf::RenderWindow*& event_ptr):
win_width(1024), win_height(768)
//light_controller("/dev/tty.usbmodem1421")
{
	event_ptr = event_window = new sf::RenderWindow(sf::VideoMode(win_width, win_height),
			                            "MelodiMemori",
			                            sf::Style::Fullscreen);

	if (!button_texture.loadFromFile("button300.png",
			                             sf::IntRect(0, 0, sprite_size_c, sprite_size_c))) {
		throw std::runtime_error("Failed to load the texture");
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
			button_sprites[i].setPosition(Vector2f(sprite_size_c + margin_size_c + border_size_c, border_size_c));
			note_colors.push_back(Color::Green);
			break;
		case 2:
			button_sprites[i].setPosition(Vector2f((2 * sprite_size_c) + margin_size_c + (2 * border_size_c), border_size_c));
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

	event_window->display();
	
}