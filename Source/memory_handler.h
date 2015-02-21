#ifndef MEMORY_HANDLER_H
#define MEMORY_HANDLER_H
#include "beat_sequence.h"
#include <SFML/Audio.hpp>
#include <string>
#include <memory>

class Memory_handler {

public:
    //constructs the handler by reading in the song data from filename
    //and then loading the chords for the song
    Memory_handler(std::vector<Beat_sequence> seq_in);

    //runs the memory handler demo by running each beat sequence,
    //pausing for input, displaying "Right!\n" for each correct beat, 
    //"Wrong!\n" for each wrong beat.
    //When a sequence plays, displays the accompanying beats
    //(or beat equivalents)
    void run();
    //sets current sequence to the next one; increments seq
    void next_sequence() { cur_seq++;}

    //returns the next sequence in line
    Beat_sequence get_current_sequence() { return sequences[cur_seq];}

    //plays the next note waiting in the sequence
    int play_next_note();

    //runs the next sequence waiting
    void run_next_sequence() { run_sequence(sequences[cur_seq]);}

    //plays the note as a "correct" note
    void play_specified_note(int note);

private:
    //runs the given sequence;
    //returns the number of beats the user gets correct
    void run_sequence(const Beat_sequence& seq);

    int cur_seq;
    int cur_note;

    std::vector<Beat_sequence> sequences;
    std::vector<int> beat_locations;
    sf::Music song_data;
};

#endif
