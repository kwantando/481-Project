#include "song.h"
#include "Controller.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <memory>

const char* const default_library_file_c = "filedata.txt";

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
    cout << "Please pick song 1-3.\n";
    cin >> read_data;
    int song_num = atoi(read_data);
    cout << "Okay. Please pick (E)asy(0.5x), (M)edium(1.0x), or (H)ard(1.5x).\n";
    while(true) {
        cin >> read_data;
        if(read_data == 'E') {
            songs[song_num].adjust_bpm(0.5);
        }
        else if(read_data == 'M') {
            songs[song_num].adjust_bpm(1.0);
        }
        else if(read_data == 'H') {
            songs[song_num].adjust_bpm(1.5);
        }
        else {
            cout << "Please select either Easy, Medium, or Hard with E, M, or H.\n";
            continue;
        }
        break;
    }
    int beats_frequency = songs[song_num].get_bpm() / 60;
    int success_beats = 0, failure_beats = 0;
    songs[song_num].play();
    while(songs[song_num].is_playing()) {
        if(int(songs[song_num].get_time().asSeconds()) % beats_frequency == 0) {

        }
    }
    return 0;
}
