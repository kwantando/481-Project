#include "memory_handler.h"
#include "songinfoparser.h"
#include <SFML/System.hpp>
#include <iostream>

using namespace std;

const char* const demo_info_file_c = "victors.txt";
const char* const demo_song_file_c = "Victors.wav";

int main()
{
    string demo_info_file{demo_info_file_c};
    string demo_song_file{demo_song_file_c};
    //I know it seems redundant, but compiler will complain^^
    Song_info_parser song_parser{demo_info_file};
    Memory_handler game_handler{demo_song_file, song_parser.get_beat_seq()};
    game_handler.run();
    return 0;
}
