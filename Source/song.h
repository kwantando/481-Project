#ifndef SONG_H
#define SONG_H

#include <SFML/Audio.hpp>
#include <string>
#include <iosfwd>
#include <vector>
#include "songinfoparser.h"
#include "Note.h"

enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

const int not_new_note_c = -1;
const int song_over_c = -2;
/*
Song is a class which functionally serves as a wrapper
for the Music object in SFML, but also takes in
and uses information on notes that ought to be pressed.*/
class Song {
public:
    //creates the song by reading info from given file
    Song(const std::string& song_file_name, Song_info_parser& info,
        Difficulty difficulty);

    Song(const char* const song_file_name, Song_info_parser& info, Difficulty difficulty);

    sf::Time get_time() { return song_data.getPlayingOffset(); }

    int get_time_ms() { return song_data.getPlayingOffset().asMilliseconds(); }

    bool is_playing();
    //begins playing the song
    void play();
    //pauses the song
    void pause();
    //stops the song
    void stop();
    //returns the current pad that is expected to be played
    int get_expected_note();

private:
    int note_freq;
    sf::Clock timer;
    Difficulty diff;
    sf::Music song_data;
    int cur_note;
    std::vector<Note> notes;
    //initializes notes by including them with the given freq
    //ie. 2 means every other note
    void initialize_notes(Song_info_parser& info);
    //returns the expected frequency of notes for current difficulty
    //and the given raw bpm
    int determine_note_freq(int bpm);
    
};

#endif