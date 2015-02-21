#ifndef BEAT_SEQUENCE_H
#define BEAT_SEQUENCE_H
#include <vector>

struct Beat_sequence {
    int start_time;
    int end_time;
    std::vector<int> played_beats; 
};
#endif