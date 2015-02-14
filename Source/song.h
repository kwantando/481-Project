#include <SFML/Audio.hpp>
#include <string>
#include <iosfwd>
/*
Song is a class which functionally serves as a wrapper
for the Music object in SFML. It provides most of the same
functionality, but is "smart" enough to load itself,
including the additional data we use for the project.*/
class Song {
public:
    //creates the song by reading info from given file
    Song(std::ifstream& input);

    void pause() { song_data.pause(); }

    void play() { song_data.play(); }

    void stop() { song_data.stop(); }

    sf::Time getTime() { return song_data.getPlayingOffset(); }
    
private:
    sf::Music song_data;
    std::string title;
    double bpm;
};