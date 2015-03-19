#ifndef SONG_INFO_PARSER_H
#define SONG_INFO_PARSER_H
#include <string>
#include <iosfwd>
#include <vector>
#include <map>


//song info parser is a class which simply serves to
//encapsulate the reading of a song's information into
//an object, with the information held in the file then
//retrievable. 
class Song_info_parser {
    struct Note;

public:
    Song_info_parser(const std::string& filename);

    std::vector<Note>& get_notes() { return notes; }


private:

    //initializes midi_to_note with the values MIDI files have to play notes,
    // and what their values in context of game are
    void initialize_midi_to_note_map();

    struct Note {
        int timestamp;
        int pad; //pad should be a number 0-5, 6-11, or 12-17.
        Note(int ts, int pad_) : timestamp(ts), pad(pad_){}
        Note(int ts) : timestamp(ts), pad(-1){}
    };
    std::map<int, int> midi_to_note;
    std::vector<Note> notes;
};

#endif
