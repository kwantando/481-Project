#ifndef NOTE_H
#define NOTE_H
struct Note {
    int timestamp;
    int pad; //pad should be a number 0-5
    Note(int ts, int pad_) : timestamp(ts), pad(pad_){}
    Note(int ts) : timestamp(ts), pad(-1){}
};

#endif