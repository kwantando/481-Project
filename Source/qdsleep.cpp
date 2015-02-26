#include "qdsleep.h"
#include <SFML/System.hpp>
//#include <SFML/Audio.hpp>

/*void qdsleep(int ms, std::shared_ptr<sf::Music> song)
{//holds until it has reached the # of ms or has run out of song to play
    while(song->getPlayingOffset().asMilliseconds() < ms
        && song->getStatus() == sf::SoundSource::Playing);
}*/

void qdsleep(int ms)
{
    sf::Clock stopwatch;
    while(stopwatch.getElapsedTime().asMilliseconds() < ms);
}
