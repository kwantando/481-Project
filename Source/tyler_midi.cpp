#include "MidiFile.h"
#include "Options.h"
#include "stdio.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

string debug(int note_num);

static const bool DEBUG = true;

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
   int track_count = midifile.getTrackCount();
   //cout << "Input file has " << track_count << " tracks\n";

   int track = atoi(argv[2]);
   if (track == 1) track = 0;
   if (track >1) track = track-1;
   if (track < 0) cerr << "negative track number\n";


   // remove all other tracks
   for (int i = 0; i < track_count; i++) {
      if (i != track) {
         midifile.deleteTrack(i);
      }
   }

   midifile.joinTracks();
   midifile.absoluteTicks();
   midifile.doTimeAnalysis();

   int previous_note = 0;
   for (int i = 0; i < midifile.getNumEvents(0); i++) {
      // midifile[0][i][2] is attack velocity
      if (midifile[0][i].isNoteOn() && midifile[0][i][2] != 0) {
         // adding 0.5 converts hex chunk to human readable MIDI note number
         int current_note = (int)(midifile[0][i][1] + 0.5);
         // will print superfluous information for notes that are held
         // for a long time without this check
         if (current_note != previous_note) {
            int time_in_ms = round(1000 * midifile.getTimeInSeconds(midifile[0][i].tick));
               cout << time_in_ms << '\t' << current_note;
               if (DEBUG) cout << '\t' << debug(current_note);
               cout << endl;
         }
         previous_note = current_note;
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
         return "F"; // why no E#?
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
