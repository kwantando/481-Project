#include "memory_handler.h"
#include "qdsleep.h"
#include <SFML/System.hpp>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cctype>
#include <utility>

using std::runtime_error;
using std::stringstream;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::move;

const char* const notes_dir_c = "Notes/";
const char* const default_note_filetype_c = ".ogg";
const int num_notes_c = 6;

//constructs the handler by reading in the song data from filename
//and then loading the chords for the song
Memory_handler::Memory_handler(const string& filename, vector<Beat_sequence> seq_in)
 : sequences(move(seq_in))
{
    if(!song_data.openFromFile(filename)) {
        throw runtime_error{"Could not open: " + filename};
    }
    notes.resize(num_notes_c);
    //initialize notes:
    for(int i = 0; i < num_notes_c; i++) {
        stringstream note_location;
        note_location << notes_dir_c << "Note" 
            << i+1 << default_note_filetype_c;
        notes[i] = std::make_shared<sf::Music>();
        if(!notes[i]->openFromFile(note_location.str())) {
            throw runtime_error{"Could not open: " + note_location.str()};
        }
    }
}
//runs the memory handler demo by running each beat sequence,
//pausing for input, displaying "Right!\n" for each correct beat, 
//"Wrong!\n" for each wrong beat.
//When a sequence plays, displays the accompanying beats
//(or beat equivalents)
void Memory_handler::run()
{
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
        successes += run_sequence(*x);
    }
    cout << "Congratulations! You got " << successes << " out of " << total << " correct!\n";
}

//runs the given sequence;
//returns the number of beats the user gets correct
int Memory_handler::run_sequence(const Beat_sequence& seq)
{
    int seq_len = int(seq.played_beats.size());
    vector<int> beat_locations;
    for(int i = 0; i < seq_len; i++) {
        //each beat location is equal to length of seq * i / num_beats
        beat_locations.push_back((i * ((seq.end_time - seq.start_time) / seq_len) + seq.start_time));
    }
    int seq_num = 0;
    if(song_data.getStatus() == sf::SoundSource::Status::Stopped) {
        song_data.play();
    }
    else {
        song_data.setPlayingOffset(sf::milliseconds(seq.start_time));
        song_data.play();
    }
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
}