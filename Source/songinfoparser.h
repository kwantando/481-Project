#ifndef SONG_INFO_PARSER_H
#define SONG_INFO_PARSER_H
#include <string>
#include <iosfwd>
#include "beat_sequence.h"


//song info parser is a class which simply serves to
//encapsulate the reading of a song's information into
//an object, with the information held in the file then
//retrievable. 
class Song_info_parser {

public:
    Song_info_parser(const std::string& filename);

    std::vector<Beat_sequence> get_beat_seq()
    { return beat_sequences; }


private:

    //reads the number of beat sequences in the program
    int read_beat_seqs(std::ifstream& input);

    //skips any lines beginning with '#' until the first line
    //which doesn't. 
    void skip_comments(std::ifstream& input);

    std::vector<Beat_sequence> beat_sequences;
};
#endif
