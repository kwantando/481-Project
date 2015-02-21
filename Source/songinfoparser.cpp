#include "Songinfoparser.h"
#include <fstream>
#include <stdexcept>
#include <utility>

using std::string;
using std::ifstream;
using std::runtime_error;
using std::vector;
using std::move;

const char* const error_message_c = "Unexpected input found in file.";

Song_info_parser::Song_info_parser(const string& filename)
{
    ifstream parser{filename};
    if(!parser) {
        throw runtime_error{"Could not open file: " + filename};
    }
    int num_beat_seqs = read_beat_seqs(parser);
    beat_sequences.resize(num_beat_seqs);
    for(int i = 0; i < num_beat_seqs; ++i) {
        skip_comments(parser);
        Beat_sequence new_seq;
        parser >> new_seq.start_time;
        parser >> new_seq.end_time;
        int num_beats;
        parser >> num_beats;
        vector<int> beats;
        beats.resize(num_beats);
        for(int i = 0; i < num_beats; ++i){
            parser >> beats[i];
        }
        new_seq.played_beats = move(beats);//thank god for move semantics
        beat_sequences[i] = move(new_seq);//otherwise inefficiencies everywhere
        if(!parser) {
            throw runtime_error{error_message_c};
        }
    }
}
//reads in the number of beatsequences in the program
//skips any lines beginning with '#'
int Song_info_parser::read_beat_seqs(ifstream& input)
{
    skip_comments(input);
    int num_beat_seqs;
    input >> num_beat_seqs;
    if(!input)
        throw runtime_error{error_message_c};
    return num_beat_seqs;
}

//skips liens until it finds one that doesn't begin with #
void Song_info_parser::skip_comments(ifstream& input)
{
    //starts with new line:
    while(input.peek() == '#' || input.peek() == '\n')//skips until new line:
        while(input.get() != '\n');

}
