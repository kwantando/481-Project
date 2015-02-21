#include "song.h"
#include "Controller.h"
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <utility>
#include <memory>
#include <cstdlib>
#include <exception>
#include <cctype>


const char* const default_song_data_file_c = "victors.txt";
const char* const default_song_file_c = "victors.wav";
const char easy_difficulty_c = 'E';
const char med_difficulty_c = 'M';
const char hard_difficulty_c = 'H';

using namespace std;
//
int main()
{
    ifstream songreader {default_library_file_c};
    int num_songs;
    vector<std::shared_ptr<Song>> songs;
    songreader >> num_songs; 
    songs.resize(num_songs);
    for(int i = 0; i < num_songs; i++) {
        songs[i] = shared_ptr<Song>(new Song{songreader});
    }
    //the following isn't done maintainable, but this is meant
    //as a proof of concept
    char read_data;
    int song_num;
    cout << "Please pick song 1-3.\n";
    cin >> song_num;
    song_num -= 1;
    if(!cin) {
        throw runtime_error{"Error: Please give song in int format."};
    }
    cout << "Okay. Please pick (E)asy, (M)edium, or (H)ard.\n";
    while(true) {
        cin >> read_data;
        read_data = toupper(read_data);
        if(read_data == easy_difficulty_c) {
            songs[song_num]->adjust_bpm(0.125);
        }
        else if(read_data == med_difficulty_c) {
            songs[song_num]->adjust_bpm(0.25);
        }
        else if(read_data == hard_difficulty_c) {
            songs[song_num]->adjust_bpm(0.5);
        }
        else {
            cout << "Please select either Easy, Medium, or Hard with E, M, or H.\n";
            continue;
        }
        break;
    }
    double beats_period = 1.0/ (songs[song_num]->get_bpm() / 60);
    double next_beat = beats_period;
    int success_beats = 0, failure_beats = 0;
    songs[song_num]->play();
    while(songs[song_num]->is_playing()) {
        double cur_time = songs[song_num]->get_time().asSeconds();
        if(cur_time >= next_beat) {
            cerr << "boop: " << cur_time << "\n";
            next_beat += beats_period;
        }
        //if(cin.get() == 'q')
        //    return 0;
    }
    cout << "Song is over.\n";
    return 0;
}
