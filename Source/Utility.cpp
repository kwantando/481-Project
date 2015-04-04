#include "Utility.h"
#include "Debug_msg.h"
#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
using namespace std;

const char* const fail_file_name_c = "fail";
const char* const success_file_name_c = "success";

vector<keypads_e> convert_int_to_keypads(const vector<int>& vc) {

	vector<keypads_e> retvec;

	for (const int& val : vc) {

		keypads_e key_val;

		switch (val) {

		case 0:
			key_val = KEYPAD1;
			break;
		case 1:
			key_val = KEYPAD2;
			break;
		case 2:
			key_val = KEYPAD3;
			break;
		case 3:
			key_val = KEYPAD4;
			break;
		case 4:
			key_val = KEYPAD5;
			break;
		case 5:
			key_val = KEYPAD6;
			break;
		default:
			DEBUG_MSG("ERROR. Incorrect value found in sequence.");

		}

		retvec.push_back(key_val);

	}

	return retvec;
}

void play_success_note()
{
    static shared_ptr<sf::Music> success_note;
    if(success_note == nullptr) {
    	success_note = make_shared<sf::Music>();
	   	stringstream success_note_loc;
	    success_note_loc << notes_dir_c << success_file_name_c
	        << ".wav";
	    if(!success_note->openFromFile(success_note_loc.str())) {
	        throw runtime_error{"Could not open: " + success_note_loc.str()};
	    }
    }
    success_note->play();
    qdsleep(default_note_wait_c);
}

void play_fail_note()
{
    static shared_ptr<sf::Music> fail_note;
    if(fail_note == nullptr) {
    	fail_note = make_shared<sf::Music>();
	   	stringstream success_note_loc;
	    fail_note_loc << notes_dir_c << fail_file_name_c
	        << ".wav";
	    if(!fail_note->openFromFile(fail_note_loc.str())) {
	        throw runtime_error{"Could not open: " + fail_note_loc.str()};
	    }
    }
    fail_note->play();
    qdsleep(default_note_wait_c);
}

void qdsleep(int ms)
{
    sf::Clock stopwatch;
    while(stopwatch.getElapsedTime().asMilliseconds() < ms);
}
