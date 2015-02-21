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
    Memory_handler(const std::string &filename, std::vector<Beat_sequence> seq_in);

    //runs the memory handler demo by running each beat sequence,
    //pausing for input, displaying "Right!\n" for each correct beat, 
    //"Wrong!\n" for each wrong beat.
    //When a sequence plays, displays the accompanying beats
    //(or beat equivalents)
    void run();

private:
    //runs the given sequence;
    //returns the number of beats the user gets correct
    int run_sequence(const Beat_sequence& seq);

    std::vector<Beat_sequence> sequences;
    std::vector<std::shared_ptr<sf::Music>> notes;
    sf::Music song_data;
};

#endif
