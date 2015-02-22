#ifndef MEMORY_HANDLER_H
#define MEMORY_HANDLER_H
#include "beat_sequence.h"
#include <SFML/Audio.hpp>
#include <string>
#include <memory>

static const int default_game_len_c = 20;

class Memory_handler {

public:
    //constructs the handler by reading in the song data from filename
    //and then loading the chords for the song
    Memory_handler(int length = default_game_len_c);

    //runs the memory handler demo by running each beat sequence,
    //pausing for input, displaying "Right!\n" for each correct beat, 
    //"Wrong!\n" for each wrong beat.
    //When a sequence plays, displays the accompanying beats
    //(or beat equivalents)
    void run();
    //sets current sequence to the next one; increments seq
    void next_sequence();

    //returns the next sequence in line
    std::vector<int> get_current_sequence() { return cur_sequence; }

    //plays the next note waiting in the sequence
    int play_next_note();

    //plays the note as a "correct" note
    void play_specified_note(int note);

private:
    //runs the given sequence;
    //returns the number of beats the user gets correct
    void run_sequence(const Beat_sequence& seq);
    //generates the cur_sequence to the given length
    //or to the size of full_sequence, whichever is less
    void gen_sequence(int len);

    int cur_seq_length;
    int cur_note;

    std::vector<int> full_sequence; 
    std::vector<int> cur_sequence;
    std::vector<std::shared_ptr<sf::Music>> notes;
    sf::Music song_data;
};

#endif
