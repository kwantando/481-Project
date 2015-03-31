#include "song.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

using std::ifstream;
using std::string;
using std::vector;
using std::runtime_error;

const int easy_note_freq_c = 6;
const int med_note_freq_c = 4;
const int hard_note_freq_c = 2;
//Constructs the Song object by opening the song file from the song file name given,
//Accessing the info Song_info_parser already gathered vis-a-vis this song,
//and then initializing internal data structures based on the difficulty given.
Song::Song(const std::string& song_file_name, Song_info_parser& info, Difficulty difficulty) :
diff(difficulty), cur_note(0)
{
    if(!song_data.openFromFile(song_file_name)) {
        throw runtime_error{"Can't open file: " + song_file_name};
    }
    note_freq = determine_note_freq(info.get_bpm());
    initialize_notes(info);
}

Song::Song(const char* const song_file_name, Song_info_parser& info, Difficulty difficulty) :
Song(string{song_file_name}, info, difficulty)
{

}

bool Song::is_playing()
{
    return song_data.getStatus() == sf::SoundSource::Status::Playing;
}

void Song::play()
{
    song_data.play();
}

void Song::pause()
{
    song_data.pause();
}

void Song::stop()
{
    song_data.stop();
}

void Song::initialize_notes(Song_info_parser& info)
{
    vector<Note>& raw_notes = info.get_notes();
    int window = -1 * note_freq;//make it so initial guard is just 0
    //(yes this is a workaround, shut up :()
    for(size_t i = 0; i < raw_notes.size(); i++) {
        if(raw_notes[i].timestamp >= (note_freq + window)) {
            notes.push_back(raw_notes[i]);
            window = raw_notes[i].timestamp;
        } 
    }
}

int Song::get_expected_note()
{
    if(!is_playing()) return song_over_c;
    if(notes[cur_note].timestamp <= get_time_ms()) {
        int val_to_return = notes[cur_note].pad;
        ++cur_note;
        return val_to_return;
    } else {
        return not_new_note_c;
    }
}

int Song::determine_note_freq(int bpm) 
{
    double beat_freq = bpm / 60.0;//f.e., 120 bpm = 2 beats/sec
    beat_freq = 1000 / beat_freq;
    switch(diff)  {
        case Difficulty::EASY:
            return beat_freq * easy_note_freq_c;
        case Difficulty::MEDIUM:
            return beat_freq * med_note_freq_c;
        case Difficulty::HARD:
            return beat_freq * hard_note_freq_c;
        default:
            throw runtime_error{"Unrecognized enum given to Song."};
            break;
    }
}
