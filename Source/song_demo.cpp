#include "song.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <memory>

const char* const default_library_file_c = "filedata.txt";

using namespace std;

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
    while(cin >> read_data) {
        switch(read_data) {
            case '1': 
            songs[1]->pause();
            songs[2]->pause();
            songs[0]->play();
            break;
            case '2':
            songs[0]->pause();
            songs[2]->pause();
            songs[1]->play();
            break;
            case '3':
            songs[0]->pause();
            songs[1]->pause();
            songs[2]->play();
            break;
            case 'q':
            return 0;
            default:
            cout << "Sorry, I don't know what command " << read_data << "is.\n";
        }
    }
    return 0;
}
