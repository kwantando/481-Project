#ifndef MEMORY_HANDLER_H
#define MEMORY_HANDLER_H
#include <SFML/Audio.hpp>
#include <string>
#include <memory>

static const int default_game_len_c = 20;

class Game_board;

class Memory_handler {

public:
    //constructs the handler by reading in the song data from filename
    //and then loading the chords for the song
    Memory_handler(int length = default_game_len_c);

    //returns the next sequence in line
    std::vector<int> get_current_sequence() { return cur_sequence; }

    //plays the next note waiting in the sequence
    int play_next_note(Game_board& gb);

    //plays the note as a "correct" note
    void play_specified_note(int note, bool block, Game_board& gb);

	void stop_notes();

    void next_sequence(bool move_up);

    //stops all other notes and plays the failure-boop. 
    void play_fail_note();
    //stops all other notes and plays the success-boop.
    void play_success_note();

    ~Memory_handler() { stop_notes(); }

    Memory_handler(const Memory_handler&) = delete;

private:
    //generates the cur_sequence to the given length
    //or to the size of full_sequence, whichever is less
    void gen_sequence(int len);

    int cur_seq_length;
    int cur_note;

    std::vector<int> full_sequence; 
    std::vector<int> cur_sequence;
    std::vector<std::shared_ptr<sf::Music>> notes;
    //sf::Music song_data;
};

#endif
