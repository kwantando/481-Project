#include "Songinfoparser.h"
#include <fstream>
#include <stdexcept>
#include <utility>
#include <sstream>

using std::string;
using std::ifstream;
using std::runtime_error;
using std::vector;
using std::move;
using std::istringstream;
using std::map;

const char* const note_info_file_c = "note_info.txt";
const char* const midi_file_note_info_c = "midi_info.txt";


Song_info_parser::Song_info_parser(const string& filename)
{
    initialize_midi_to_note_map();
    ifstream parser{filename};
    if(!parser) {
        throw runtime_error{"Could not open file: " + filename};
    }
    int bpm;
    parser >> bpm; 
    if(!parser) {
        throw runtime_error{"First line not integer for bpm. Aborting.\n"};
    }
    int note, ts;
    while(parser >> ts >> note) {
        notes.push_back(Note(ts, midi_to_note[note]));
    }
}

void Song_info_parser::initialize_midi_to_note_map()
{
    ifstream parser{note_info_file_c};
    map<string, int> note_to_val;
    string parser_line;
    while(getline(parser, parser_line)) {
        istringstream input_line{parser_line};
        string note;
        int val;
        input_line >> note >> val;
        note_to_val[note] = val;
    }
    parser.close();
    map<string, vector<int>> str_to_note;
    parser.open(midi_file_note_info_c);
    while(getline(parser, parser_line)) {
        istringstream input_line{parser_line};
        string note;
        input_line >> note;
        int val;
        vector<int> notes;
        while(input_line >> val) {
            notes.push_back(val);
        }
        str_to_note[note] = notes;
    }
    for(auto iter = str_to_note.begin(); iter != str_to_note.end(); iter++) {
        for(int note: iter->second) {
            midi_to_note[note] = note_to_val[iter->first];
        }
    }
}
