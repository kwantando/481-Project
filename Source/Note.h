#ifndef NOTE_H
#define NOTE_H
struct Note {
    int timestamp;
    int pad; //pad should be a number 0-5
    Note(int ts, int pad_ = -1) : timestamp(ts), pad(pad_){ }
};

#endif