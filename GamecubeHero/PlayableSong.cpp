//
//  PlayableSong.cpp
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/29/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#include "PlayableSong.h"
#include <iostream>

PlayableSong::PlayableSong(smf::MidiFile& midifile, std::string songPath, int track, int endtrack, int tracklist[], int tracklength) {
    song.openFromFile(songPath);
    if(tracklist != nullptr) {
        track = 0;
    }
    else {
        tracklist[0] = track;
    }
    int tracks = midifile.getTrackCount();

    //TPQ
    Song song;
    song.tpq=midifile.getTicksPerQuarterNote();
    tpq=song.tpq;


    /*
    if(tracks>1) {
        track=1;
    }*/
    int firstcount=0;
    for(;track<tracklength; track++) {
        for(int event=0; event<midifile[tracklist[track]].size(); event++) {
            firstcount++;
            if(midifile[tracklist[track]][event].isNoteOn()) {
                //save tick because this thing's on fire
                //save duration and tick
                MidiNote note;
                note.tick=midifile[tracklist[track]][event].tick;
                //note.tickTime=sf::seconds(note.tick/midifile[track][event].getTempoTPS(song.tpq));
                note.tickTime=sf::seconds(midifile.getTimeInSeconds(tracklist[track], event));

                note.duration=midifile[tracklist[track]][event].getTickDuration();
                //note.durationTime=sf::seconds(note.duration/midifile[track][event].getTempoTPS(song.tpq));
                note.durationTime=sf::seconds(midifile[tracklist[track]][event].getDurationInSeconds());

                note.note=midifile[tracklist[track]][event][1];//get the note
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
            //song.notes.erase(song.notes.begin()+(i));
            //i--;
            //continue;
        }
    }

    /*for(int i=0;i<song.notes.size();i++) {
        std::cout<<song.notes[i].tick<<"\t"<<song.notes[i].duration<<"\t"<<(int)song.notes[i].note<<std::endl;
    }*/
    printf("TPQ: %d\n", song.tpq);
    printf("Initial: %d\n", firstcount);
    printf("Before: %d\nAfter: %d\n", before, (int)song.notes.size());

    std::cout<<"Spawn Time\tDuration\tBUTTON\t\tIsLong?"<<std::endl;
    PlayableSong::NoteSpawn t;
    t.tickSig = -1;
    for(int i=0;i<song.notes.size();i++) {
        //spawns.push_back(makeSpawn(song.notes[i]));
        //std::cout<<"error"<<std::endl;
        PlayableSong::NoteSpawn s = makeSpawn(song.notes[i]);
        if(t.tickSig != -1) {
            if(s.button == t.button) {
                if(s.spawnTime == t.spawnTime) {
                    //std::cout<<"error"<<std::endl;
                    continue;
                }
            }
        }
        spawns.push_back(s);
        t = s;


        //std::cout<<std::to_string(spawns[i].spawnTime.asSeconds())<<" \t"<<std::to_string(spawns[i].duration.asSeconds())<<"\t"<<NamedNotes::toString(spawns[i].button)<<"\t"<<(spawns[i].isLong ? "true" : "false")<<std::endl;
    }
}

PlayableSong::NoteSpawn PlayableSong::makeSpawn(MidiNote& note) {
    NoteSpawn spawn;
    //spawn.spawnTime=sf::seconds(note.tick/160.f);
    //spawn.duration=sf::seconds(note.duration/160.f);
    spawn.spawnTime=note.tickTime;// * (float)(0.98496240601);
    spawn.duration=note.durationTime;
    spawn.button=note_to_type(note.note);
    spawn.isLong=note.isLong;
    spawn.tickSig=note.tick;
    return spawn;
    //return {sf::seconds(note.tick/1600.f), sf::seconds(note.duration/1600.f), note_to_type(note.note), note.isLong};
}

PlayableSong::NoteSpawn PlayableSong::getFirstSpawn(smf::MidiFile& midifile, std::string songPath) {
song.openFromFile(songPath);
    int tracks = midifile.getTrackCount();
    int track = 0;
    //TPQ
    Song song;
    song.tpq=midifile.getTicksPerQuarterNote();
    tpq=song.tpq;

    int firstcount=0;
    for(;track<tracks; track++) {
        for(int event=0; event<midifile[track].size(); event++) {
            firstcount++;
            if(midifile[track][event].isNoteOn()) {
                //save tick because this thing's on fire
                //save duration and tick
                MidiNote note;
                note.tick=midifile[track][event].tick;
                //note.tickTime=sf::seconds(note.tick/midifile[track][event].getTempoTPS(song.tpq));
                note.tickTime=sf::seconds(midifile.getTimeInSeconds(track, event));


                note.duration=midifile[track][event].getTickDuration();
                //note.durationTime=sf::seconds(note.duration/midifile[track][event].getTempoTPS(song.tpq));
                note.durationTime=sf::seconds(midifile[track][event].getDurationInSeconds());

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

    /*for(int i=0;i<song.notes.size();i++) {
        std::cout<<song.notes[i].tick<<"\t"<<song.notes[i].duration<<"\t"<<(int)song.notes[i].note<<std::endl;
    }*/
    printf("TPQ: %d\n", song.tpq);
    printf("Initial: %d\n", firstcount);
    printf("Before: %d\nAfter: %d\n", before, (int)song.notes.size());

    std::cout<<"Spawn Time\tDuration\tBUTTON\t\tIsLong?"<<std::endl;
    for(int i=0;i<song.notes.size();i++) {
        spawns1.push_back(makeSpawn(song.notes[i]));
        //std::cout<<std::to_string(spawns[i].spawnTime.asSeconds())<<" \t"<<std::to_string(spawns[i].duration.asSeconds())<<"\t"<<NamedNotes::toString(spawns[i].button)<<"\t"<<(spawns[i].isLong ? "true" : "false")<<std::endl;
    }
    return spawns1[0];
}

std::vector<PlayableSong::NoteSpawn> PlayableSong::getSpawns(sf::Time curr, sf::Time prev) {
    std::vector<NoteSpawn> ans;
    for(int i=0;i<spawns.size();i++) {
        if(spawns[i].spawnTime>=prev&&spawns[i].spawnTime<curr) {
            ans.push_back(spawns[i]);
        }
    }
    return ans;
}

//inclusive in
inline bool in(int x, int a, int b) {
    return x >= a && x <=b;
}

NoteTypes PlayableSong::note_to_type(int note) {
    //Low notes
    if(in(note, 21, 26)) return L2;
    if(in(note, 27, 31)) return L1;
    if(in(note, 32, 37)) return LEFT;
    if(in(note, 38, 42)) return UP;
    if(in(note, 43, 48)) return DOWN;
    if(in(note, 49, 54)) return RIGHT;
    //Middle notes
    if(in(note, 55, 59)) return SQUARE;
    if(in(note, 60, 63)) return TRIANGLE;
    if(in(note, 64, 67)) return X;
    if(in(note, 68, 71)) return CIRCLE;
    if(in(note, 72, 75)) return R1;
    if(in(note, 76, 79)) return R2;
    //High notes
    if(in(note, 80, 84)) return SQUARE;
    if(in(note, 85, 89)) return TRIANGLE;
    if(in(note, 90, 94)) return X;
    if(in(note, 95, 99)) return CIRCLE;
    if(in(note, 100, 104)) return R1;
    if(in(note, 105, 108)) return R2;
    return COUNT;
    /*
    //Low notes
    if(note >= 21 && note <= 26) return L2;
    if(note >= 27 && note <= 31) return L1;
    if(note >= 32 && note <= 37) return LEFT;
    if(note >= 38 && note <= 42) return UP;
    if(note >= 43 && note <= 48) return DOWN;
    if(note >= 49 && note <= 54) return RIGHT;
    //Middle notes
    if(note >= 55 && note <= 59) return SQUARE;
    if(note >= 60 && note <= 63) return TRIANGLE;
    if(note >= 64 && note <= 67) return X;
    if(note >= 68 && note <= 71) return CIRCLE;
    if(note >= 72 && note <= 75) return R1;
    if(note >= 76 && note <= 79) return R2;
    //High notes
    if(note >= 80 && note <= 84) return SQUARE;
    if(note >= 85 && note <= 89) return TRIANGLE;
    if(note >= 90 && note <= 94) return X;
    if(note >= 95 && note <= 99) return CIRCLE;
    if(note >= 100 && note <= 104) return R1;
    if(note >= 105 && note <= 108) return R2;
    return COUNT;
     */
}
