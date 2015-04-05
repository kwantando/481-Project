#include "memory_handler.h"
#include "Game_board.h"
#include "Utility.h"
#include <SFML/System.hpp>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cctype>
#include <utility>
#include <cstdlib>
#include <time.h>
#include <functional>

using std::runtime_error;
using std::stringstream;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::move;
using std::make_shared;
using std::mem_fn;
using std::shared_ptr;

const int done_playing_c = -1;
const int num_notes_c = 6;
const char* const default_note_filetype_c = ".ogg";
const char* const note_file_name_c = "n";//n + number, of course


//constructs the handler by reading in the song data from filename
//and then loading the chords for the song
Memory_handler::Memory_handler(int length)
 : cur_seq_length(2), cur_note(0)
{
    srand(time(NULL));
    full_sequence.resize(length);
    for(int i = 0; i < length; i++) {
        full_sequence[i] = rand() % num_notes_c;
    }
    notes.resize(num_notes_c);
    for(int i = 0; i < num_notes_c; i++) {
        stringstream note_location;
        note_location << notes_dir_c << note_file_name_c 
            << i+1 << default_note_filetype_c;
        notes[i] = make_shared<sf::Music>();
        if(!notes[i]->openFromFile(note_location.str())) {
            throw runtime_error{"Could not open: " + note_location.str()};
        }
    }
    gen_sequence(cur_seq_length);
}

//plays the next note in the sequence, returning the note that was played(1-6)
//returns -1 if the sequence is over
int Memory_handler::play_next_note(Game_board& gb)
{
    if(cur_note >= cur_sequence.size()) {
        notes[cur_sequence[cur_note - 1]]->stop();
        return done_playing_c;
    }
    //if the next note is out of sequence size, means we've played out this sequence
    play_specified_note(cur_note, true, gb);
    return cur_sequence[cur_note++];
}
//plays the note passed to it in the -currently loaded- sequence
//undefined behavior if no sequence is currently loaded
void Memory_handler::play_specified_note(int cur, bool block, Game_board& gb)
{
    //if(note < 0 || note >= num_notes_c) {
    //    throw runtime_error{"play_correct_note passed note out of range"};
    //}
    stop_notes();//ensure no notes are running before starting new one
    int cur_note = cur_sequence[cur];
    notes[cur_note]->play();
    if(cur > 0)
        gb.switch_off_button(cur_sequence[cur-1]);

	qdsleep(200);
    gb.switch_on_button(cur_note);
	if (block) { qdsleep(default_note_wait_c); }
    //stop_notes();

}

void Memory_handler::gen_sequence(int len)
{
    if(!cur_sequence.empty()) cur_sequence.clear();
    cur_sequence.resize(len);
    for(int i = 0; i < len && i < full_sequence.size(); i++) {
        cur_sequence[i] = full_sequence[i];
    }
}
//prepares the next sequence to play
void Memory_handler::next_sequence(bool move_up)
{
	if (move_up) {
		cur_seq_length++;
	}
    cur_note = 0;
    gen_sequence(cur_seq_length);
}

//stops all other notes and plays the failure-boop.
void Memory_handler::alert_fail_note()
{
    stop_notes();
    play_fail_note();
}

void Memory_handler::stop_notes()
{
    for_each(notes.begin(), notes.end(), [](shared_ptr<sf::Music> note){
        note->stop();
    });
}

void Memory_handler::alert_success_note()
{
    stop_notes();
    play_success_note();
}
