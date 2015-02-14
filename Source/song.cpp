#include "song.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

using std::ifstream;
using std::string;

Song::Song(ifstream& input)
{
    string name, bpm_str, path;
    char char_parser;
    input >> char_parser;//remove starting bracket.
    char_parser = input.get();
    while(char_parser != '}') {
        name.push_back(char_parser);
        char_parser = input.get();
    }
    title = name;
    input >> bpm_str >> path;
    bpm_str = bpm_str.substr(1, bpm_str.length() - 2);
    bpm = atoi(bpm_str.c_str());
    path = path.substr(1, path.length() - 2);
    if(!song_data.openFromFile(path)) { 
        throw std::runtime_error{"File not found: " + path};
    }
}
