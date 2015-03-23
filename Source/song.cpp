#include "song.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

using std::ifstream;
using std::string;
using std::vector;

const int easy_note_freq_c = 5;
const int med_note_freq_c = 3;
const int hard_note_freq_c = 2;

Song::Song(const std::string& song_file_name, Song_info_parser& info, Difficulty difficulty) :
diff(difficulty), cur_note(0)
{
    if(!song_data.openFromFile(song_file_name)) {
        throw std::runtime_error{"Can't open file: " + song_file_name};
    }
    switch(diff)  {
        case Difficulty::EASY:
            initialize_notes(info, easy_note_freq_c);
            break;
        case Difficulty::MEDIUM:
            initialize_notes(info, med_note_freq_c);
            break;
        case Difficulty::HARD:
            initialize_notes(info, hard_note_freq_c);
            break;
        default:
            throw std::runtime_error{"Unrecognized enum in Song ctor."};
            break;
    }
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

void Song::initialize_notes(Song_info_parser& info, int freq)
{
    vector<Note>& raw_notes = info.get_notes();
    for(size_t i = 0; i < raw_notes.size(); i++) {
        if(i%freq == 0) {
            notes.push_back(raw_notes[i]);
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

