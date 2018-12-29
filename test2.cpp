#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "MidiFile.h"
#include "Options.h"

struct MidiNote {
   //in ticks
   int tick;
   int duration;
   uint8_t note;
   bool isLong = false;
   bool operator==(const MidiNote& rhs) {
      return tick==rhs.tick && duration==rhs.duration && note==rhs.note;
   }
   struct Compare {
      bool operator()(MidiNote& lhs, MidiNote& rhs) {
         if(lhs.tick==rhs.tick) {
            if(lhs.duration==rhs.duration) {
               return lhs.note<rhs.note;
            }
            return lhs.duration<rhs.duration;
         }
         return lhs.tick<rhs.tick;
      }
   };
};

struct Song {
   int tpq;
   std::vector<MidiNote> notes;
   std::string filename;

};

class PlayableSong {
   //sf::Music song;
   struct NoteSpawns {
      //sf::Time spawn;
      //sf::Time duration;
      //NoteTypes button;

   };

public:

};
/*
NoteTypes note_to_type(int note) {
   if(note >= 21 && note <= 26) return L2;
   if(note >= 27 && note <= 31) return L1;
   if(note >= 32 && note <= 37) return UP;
   if(note >= 38 && note <= 42) return LEFT;
   if(note >= 43 && note <= 48) return DOWN;
   if(note >= 49 && note <= 54) return RIGHT;
   //
   if(note >= 55 && note <= 59) return SQUARE;
   if(note >= 60 && note <= 63) return X;
   if(note >= 64 && note <= 67) return CIRCLE;
   if(note >= 68 && note <= 71) return TRIANGLE;
   if(note >= 72 && note <= 75) return R1;
   if(note >= 76 && note <= 79) return R2;
   //
   if(note >= 80 && note <= 84) return SQUARE;
   if(note >= 85 && note <= 89) return X;
   if(note >= 90 && note <= 94) return CIRCLE;
   if(note >= 95 && note <= 99) return TRIANGLE;
   if(note >= 100 && note <= 104) return R1;
   if(note >= 105 && note <= 108) return R2;

}*/

int main(int argc, char** argv) {
   smf::Options options;
   options.process(argc, argv);
   smf::MidiFile midifile;
   if (options.getArgCount() == 0) {
      midifile.read(std::cin);
   }
   else midifile.read(options.getArg(1));
   midifile.doTimeAnalysis();
   midifile.linkNotePairs();

   int tracks = midifile.getTrackCount();

   //TPQ
   Song song;
   song.tpq=midifile.getTicksPerQuarterNote();

   int track=0;
   if(tracks>1) {
      track=1;
   }
   int firstcount=0;
   for(;track<tracks; track++) {
      for(int event=0; event<midifile[track].size(); event++) {
         firstcount++;
         if(midifile[track][event].isNoteOn()) {
            //save tick because this thing's on fire
            //save duration and tick
            MidiNote note;
            note.tick=midifile[track][event].tick;
            note.duration=midifile[track][event].getTickDuration();
            note.note=midifile[track][event][1];//get the note
            if(note.duration > song.tpq) note.isLong=true;
            song.notes.push_back(note);
         }
      }
   }
   int before = song.notes.size();
   MidiNote::Compare comp;
   std::sort(song.notes.begin(), song.notes.end(), comp);
   for(int i=1; i<song.notes.size(); i++) {
      if(song.notes[i]== song.notes[i-1]) {
         song.notes.erase(song.notes.begin()+i);
         i--;
         continue;
      }
      else if(song.notes[i].note==song.notes[i-1].note &&
         song.notes[i].tick==song.notes[i-1].tick) {
            song.notes.erase(song.notes.begin()+(i-1));
            i--;
            continue;
         }
      if(song.notes[i].duration < 24) {
         song.notes.erase(song.notes.begin()+(i));
         i--;
         continue;
      }
   }

   for(int i=0;i<song.notes.size();i++) {
      std::cout<<song.notes[i].tick<<"\t"<<song.notes[i].duration<<"\t"<<(int)song.notes[i].note<<std::endl;
   }
   printf("TPQ: %d\n", song.tpq);
   printf("Initial: %d\n", firstcount);
   printf("Before: %d\nAfter: ", before);

   std::cout<<song.notes.size()<<std::endl;

   return 0;
}
