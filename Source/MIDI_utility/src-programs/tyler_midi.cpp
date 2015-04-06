#include "MidiFile.h"
#include "MidiMessage.h"
#include "Options.h"
#include "stdio.h"
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <map>

static const bool DEBUG = false;

using namespace std;

struct Note {
   int on_time;
   int note_num;
};

string debug(int note_num);
void process_notes(vector<Note> note_list);

int main(int argc, char** argv) {
   Options options;
   options.process(argc, argv);
   if (options.getArgCount() != 2) {
      cerr << "Input format is <filename> <track_number>\n";
      exit(1);
   }
   MidiFile midifile;
   midifile.read(options.getArg(1));
   if (!midifile.status()) {
      cerr << "Error reading MIDI file " << options.getArg(1) << endl;
      exit(1);
   }

   int track = atoi(argv[2]);
   midifile.absoluteTicks();
   midifile.doTimeAnalysis();

   bool tempo = false;
   vector<Note> note_list;
   for (int i = 0; i < midifile.getEventCount(track); i++) {
      // At the first tempo event, print the tempo.
      if (!tempo && midifile[track][i].isTempo()) {
         cout << midifile[track][i].getTempoBPM() << endl;
         tempo = true;
      }
      // midifile[0][i][2] is attack velocity
      if (midifile[track][i].isNoteOn() && midifile[track][i][2] != 0) {
         int note = (int)(midifile[track][i][1] + 0.5);
         int current_time = round(1000 * midifile.getTimeInSeconds(midifile[track][i].tick));
         int size = note_list.size();
         note_list.push_back({current_time, note});
         if (note_list.size() <= size) {
            cerr << "nothing inserted\n";
            exit(2);
         }
      }
   }
   if (!note_list.size()) {
      cerr << "******** empty note list\n";
      exit(0);
   } else {
      process_notes(note_list);
   }
   return 0;
}

void process_notes(vector<Note> note_list) {
   for (int i = 0; i < note_list.size(); i++) {
      if (i > 0 && note_list[i-1].note_num != note_list[i].note_num) {
         cout << note_list[i].on_time << '\t'
              << note_list[i].note_num << '\t';
              DEBUG ? cout << debug(note_list[i].note_num) << endl :
              cout << endl;
      } else if (i == 0) {
         cout << note_list[i].on_time << '\t'
              << note_list[i].note_num << '\t';
              DEBUG ? cout << debug(note_list[i].note_num) << endl :
              cout << endl;
     }
   }
}

string debug(int note_num) {
   switch(note_num % 12) {
      case 0:
         return "C";
      case 1:
         return "C#";
      case 2:
         return "D";
      case 3:
         return "D#";
      case 4:
         return "E";
      case 5:
         return "F";
      case 6:
         return "F#";
      case 7:
         return "G";
      case 8:
         return "G#";
      case 9:
         return "A";
      case 10:
         return "A#";
      case 11:
         return "B";
      default:
         return "Not a note";
   }
}
