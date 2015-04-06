#ifndef SONG_INFO_PARSER_H
#define SONG_INFO_PARSER_H
#include <string>
#include <iosfwd>
#include <vector>
#include <map>
#include "Note.h"


//song info parser is a class which simply serves to
//encapsulate the reading of a song's information into
//an object, with the information held in the file then
//retrievable. 
class Song_info_parser {

public:
    Song_info_parser(const std::string& filename);

    std::vector<Note>& get_notes() { return notes; }

    int get_bpm() { return bpm; }


private:

    //initializes midi_to_note with the values MIDI files have to play notes,
    // and what their values in context of game are
    void initialize_midi_to_note_map();
    std::map<int, int> midi_to_note;
    std::vector<Note> notes;
    int bpm;
};

#endif
