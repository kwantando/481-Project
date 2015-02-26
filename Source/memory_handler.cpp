#include "memory_handler.h"
#include "qdsleep.h"
#include "Game_board.h"
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
const int default_note_wait_c = 300;
const char* const notes_dir_c = "Notes/";
const char* const default_note_filetype_c = ".ogg";
const char* const note_file_name_c = "n";//n + number, of course
const char* const fail_file_name_c = "fail";
const char* const success_file_name_c = "success";


//constructs the handler by reading in the song data from filename
//and then loading the chords for the song
Memory_handler::Memory_handler(int length)
 : cur_seq_length(5), cur_note(0)
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
    fail_note = make_shared<sf::Music>();
    stringstream fail_note_loc;
    fail_note_loc << notes_dir_c << fail_file_name_c 
        << default_note_filetype_c;
    if(!fail_note->openFromFile(fail_note_loc.str())) {
        throw runtime_error{"Could not open: " + fail_note_loc.str()};
    }
    success_note = make_shared<sf::Music>();
    stringstream success_note_loc;
    success_note_loc << notes_dir_c << success_file_name_c
        << ".wav";
    if(!success_note->openFromFile(success_note_loc.str())) {
        throw runtime_error{"Could not open: " + success_note_loc.str()};
    }
    gen_sequence(cur_seq_length);
}
//runs the memory handler demo by running each beat sequence,
//pausing for input, displaying "Right!\n" for each correct beat, 
//"Wrong!\n" for each wrong beat.
//When a sequence plays, displays the accompanying beats
//(or beat equivalents)
void Memory_handler::run()
{/*does nothing for now
    cout << "Welcome to Memory Demo!\n";
    cout << "Are you ready? Y/N\n";
    while(char ready = cin.get()) {
        ready = tolower(ready);
        if(ready == 'n') {
            cout << "What? Really? Okay..\n";
            return;
        }
        else if(ready == 'y') {
            cout << "Alright, starting!\n";
            break;
        }
        else 
            cout << "Huh?\n";
    }
    int total = 0, successes = 0;
    for(auto x = sequences.begin(); x != sequences.end(); x++) {
        total += x->played_beats.size();
        run_sequence(*x);
    }
    cout << "Congratulations! You got " << successes << " out of " << total << " correct!\n";
    */
}

//runs the given sequence;
//returns the number of beats the user gets correct
void Memory_handler::run_sequence(const Beat_sequence& seq)
{/*
    int seq_len = int(seq.played_beats.size());
    if(!beat_locations.empty()) beat_locations.clear();
    for(int i = 0; i < seq_len; i++) {
        //each beat location is equal to length of seq * i / num_beats
        beat_locations.push_back((i * ((seq.end_time - seq.start_time) / seq_len) + seq.start_time));
    }
    cur_note = 0;
    
    if(song_data.getStatus() == sf::SoundSource::Status::Stopped) {
        song_data.play();
    }
    else {
        song_data.setPlayingOffset(sf::milliseconds(seq.start_time));
        song_data.play();
    }
    */
    /*
    sf::Time end_time = sf::milliseconds(seq.end_time);
    sf::Time cur_time;
    while((cur_time = song_data.getPlayingOffset()) < end_time) {
        if(seq_num >= seq_len) continue;
        if(cur_time.asMilliseconds() > beat_locations[seq_num]) {
            cout << seq.played_beats[seq_num] << "!\n";
            seq_num++;
        }
    }
    song_data.pause();//pause as soon as end of seq
    cout << "Replay the beat!\n";
    vector<int> user_input;
    for(int i = 0; i < seq_len; i++) {
        int input; 
        cin >> input;
        while(!cin || input < 1 || input > 6) {
            cout << "Error: Please enter the beat # from 1 to 6.\n";
            cin.clear();
            cin >> input;
        }
        notes[input-1]->play();
        user_input.push_back(input);
        if(user_input[i] == seq.played_beats[i]) {
            cout << "Correct!" << endl;//clear buffer
        }
        else {
            cout << "Wrong note.." << endl;
        }
        while(notes[input-1]->getStatus() == sf::SoundSource::Status::Playing);
        //loop until it's done playing the note
    }
    int successes = 0;
    for(int i = 0; i < seq_len; i++) {
        if(user_input[i] == seq.played_beats[i])
            successes++;
    }
    cout << "You got " << successes << " out of " << seq_len << " right!\n";
    qdsleep(2500);
    return successes;
    */
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
    int cur_note = cur_sequence[cur];
    notes[cur_note]->play();
    if(cur > 0)
        gb.switch_off_button(cur_sequence[cur-1]);

	qdsleep(150);
    gb.switch_on_button(cur_note);
	if (block) { qdsleep(default_note_wait_c); }
    stop_notes();

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
void Memory_handler::play_fail_note()
{
    stop_notes();
    fail_note->play();
    qdsleep(default_note_wait_c);
    fail_note->stop();
}

void Memory_handler::stop_notes()
{
    for_each(notes.begin(), notes.end(), [](shared_ptr<sf::Music> note){
        note->stop();
    });
}

void Memory_handler::play_success_note()
{
    stop_notes();
    success_note->play();
    qdsleep(default_note_wait_c);
    success_note->stop();
}
